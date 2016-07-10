/*
 * Map.cpp
 *
 *  Created on: May 4, 2013
 *      Author: roque
 */

#include "Map.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#define SUCCESS 1
int steps = 0;

//Esta classe representa um mapa
Map::Map() {
	colors.push_back("Azul");
	colors.push_back("Amarelo");
	colors.push_back("Verde");
	colors.push_back("Vermelho");
}

//Backtracking simples, sem poda
int Map::backtracking(int assignments){
	if (assignments == regionList.size())
		return SUCCESS;
	int variable = selectVariable();
	for (int i = 0; i < colors.size(); i++){
		if(!hasConstraint(variable, colors[i])){
			regionList[variable].setColor(colors[i]);
			assignments += 1;
			steps += 1;
			int result = backtracking(assignments);
			if (result == SUCCESS)
				return result;
			regionList[variable].removeColor();
			assignments -= 1;
		}
	}
	return 0;
}

//Backtracking com verificação adiante
int Map::backtrackingFC(int assignments){
	if (assignments == regionList.size())
		return SUCCESS;
	int variable = selectVariable();
	for (int i = 0; i < colors.size(); i++){
		if(!hasConstraint(variable, colors[i])){
			regionList[variable].setColor(colors[i]);
			updateNeighbors(variable, false, colors[i]);
			assignments += 1;
			steps += 1;
			if(forwardChecking(variable)){//Faz a verificação adiante
				int result = backtrackingFC(assignments);
				if (result == SUCCESS)
					return result;
			}
			regionList[variable].removeColor();
			updateNeighbors(variable, true, colors[i]);
			assignments -= 1;
		}
	}
	return 0;
}

//Backtracking com verificação adiante e MVR
int Map::backtrackingMVR(int assignments){
	if (assignments == regionList.size())
		return SUCCESS;
	int variable = selectVariableMVR();//escolhe a região com MVR
	for (int i = 0; i < colors.size(); i++){
		if(!hasConstraint(variable, colors[i])){
			regionList[variable].setColor(colors[i]);
			updateNeighbors(variable, false, colors[i]);
			assignments += 1;
			steps += 1;
			if(forwardChecking(variable)){//Faz a verificação adiante
				int result = backtrackingMVR(assignments);
				if (result == SUCCESS)
					return result;
			}
			regionList[variable].removeColor();
			updateNeighbors(variable, true, colors[i]);
			assignments -= 1;
		}
	}
	return 0;
}

//Backtracking com verificação adiante, MVR e grau
int Map::backtrackingMVRDegree(int assignments){
	if (assignments == regionList.size())
		return SUCCESS;
	int variable = selectVariableMVRDegree();
	for (int i = 0; i < colors.size(); i++){
		if(!hasConstraint(variable, colors[i])){
			regionList[variable].setColor(colors[i]);
			updateNeighbors(variable, false, colors[i]);
			assignments += 1;
			steps += 1;
			if(forwardChecking(variable)){
				int result = backtrackingMVRDegree(assignments);
				if (result == SUCCESS)
					return result;
			}
			regionList[variable].removeColor();
			updateNeighbors(variable, true, colors[i]);
			assignments -= 1;
		}
	}
	return 0;
}

//Escolhe uma região que não têm cor
int Map::selectVariable(){
	for (int i = 0; i < regionList.size(); i++){
		if(!regionList[i].hasColor())
			return i;
	}
}

//Escolhe a região com menor número de cores possíveis
int Map::selectVariableMVR(){
	int mrv = colors.size() + 1;
	int variable = 0;
	for (int i = 0; i < regionList.size(); i++){
		if(!regionList[i].hasColor()){
			if(regionList[i].getPossibleColors() < mrv){
				variable = i;
				mrv = regionList[i].getPossibleColors();
			}
		}
	}
	return variable;
}

//Escolhe a região com MVR, em caso de empate Grau escolhe a região com o maior número de vizinhos
int Map::selectVariableMVRDegree(){
	int mrv = colors.size() + 1;
	int variable = 0;
	for (int i = 0; i < regionList.size(); i++){
		if(!regionList[i].hasColor()){
			if(regionList[i].getPossibleColors() < mrv){
				variable = i;
				mrv = regionList[i].getPossibleColors();
			}
			else if(regionList[i].getPossibleColors() == mrv){
				int constraintsV = getConstraints(variable);
				int constraintsI = getConstraints(i);
				if(constraintsI > constraintsV){
					variable = i;
					mrv = regionList[i].getPossibleColors();
				}
			}
		}
	}
	return variable;
}

//Retorna o número de restrições de uma região
int  Map::getConstraints(int variable){
	int cont = 0;
	vector<Region> neighbors = regionList[variable].getNeighbors();
	for(int i = 0;i < neighbors.size(); i++){
		if(!regionList[findRegion(neighbors[i].getName())].hasColor())
			cont += 1;
	}
	return cont;
}

//Verificação adiante, verifica se um vizinho não tem cores disponíveis
bool Map::forwardChecking(int variable){
	vector<Region> neighbors = regionList[variable].getNeighbors();
	for(int i = 0;i < neighbors.size(); i++){
		if(regionList[findRegion(neighbors[i].getName())].getPossibleColors()==0)
			return false;
	}
	return true;
}

//Verifica se um vizinho já têm atribuído esse cor
bool Map::hasConstraint(int variable, string colorName){
	vector<Region> neighbors = regionList[variable].getNeighbors();
	for (int i = 0; i < neighbors.size(); i++){
		if (regionList[findRegion(neighbors[i].getName())].getColor().compare(colorName) == 0)
			return true;
	}
	return false;
}

//Atualiza as cores disponíveis para seus vizinhos
void Map::updateNeighbors(int variable, bool flag, string colorName){
	vector<Region> neighbors = regionList[variable].getNeighbors();
	for (int i = 0; i < neighbors.size(); i++){
		regionList[findRegion(neighbors[i].getName())].updatePossibleColors(flag, colorName);
	}
}

//Lê os dados de entrada
bool Map::readInputs(string pathFile){
	ifstream iFile(pathFile.c_str());
	string line;
	getline(iFile, line);
	int n = atoi(line.c_str());
	if(0 < n && n < 101){
		while(getline(iFile, line)){
			doGraph(split(line));
		}
		iFile.close();
		return true;
	}
	else{
		printf("O valor de N debe ser 0 < N < 101\n");
		iFile.close();
		return false;
	}
}

//Constrói o grafo
void Map::doGraph(vector<string> regions){
	string regionName1 = regions[0];
	int index1 = findRegion(regionName1);
	if (index1 < 0){
		Region obj(regionName1);
		regionList.push_back(obj);
		index1 = regionList.size()-1;
	}
	string regionName;
	int index;
	for (int i = 1; i < regions.size(); i++){
		regionName = regions[i];
		index = findRegion(regionName);
		if (index < 0){
			Region neighbor(regionName);
			regionList.push_back(neighbor);
			index = regionList.size()-1;
		}
		regionList[index1].setNeighbor(regionList[index]);
	}
}

//Imprime o mapa com as cidades e suas cores
void Map::printMap(){
	ofstream myfile ("OUTPUT");
	for (int i = 0; i < regionList.size(); i++){
		myfile << regionList[i].getName() << ": "<< regionList[i].getColor() << ".\n";
		printf("%s: %s.\n", regionList[i].getName().c_str(),regionList[i].getColor().c_str());
	}
	printf("Atribuições = %d\n",steps);
	printf("Arquivo OUTPUT gerado\n");
	steps = 0;
	myfile.close();
}

vector<string> Map::split(string line){
	vector<string> words;
	string buf = "";
	int i = 0;
	while (i < line.length()){
		if (line[i] != ':' && line[i] != ',' && line[i] != '.')
			buf += line[i];
		else if (buf.length() > 0) {
			if(isspace(buf[0])) buf = buf.substr(1);
			words.push_back(buf);
			buf = "";
		}
		i++;
	}
	return words;
}

int Map::findRegion(string regionName){
	for (int i = 0; i < regionList.size(); i++){
		if(regionList[i].getName() == regionName)
			return i;
	}
	return -1;
}
