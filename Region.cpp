/*
 * Region.cpp
 *
 *  Created on: May 4, 2013
 *      Author: roque
 */

#include "Region.h"
#define WITHOUT_COLOR "NoColor"

//A classe Region representa a uma cidade

Region::Region(string name_){
	name = name_; // O nome da região.
	color = WITHOUT_COLOR; // O cor asignado á região, inicialmente sem cor
	//Inicialmente todas as cores estão disponíveis para esta região
	possibleColors["Azul"] = true;
	possibleColors["Amarelo"] = true;
	possibleColors["Verde"] = true;
	possibleColors["Vermelho"] = true;
}

Region::Region(){}

void Region::setNeighbor(Region region){
	neighborRegions.push_back(region);
}

void Region::setColor(string colorName){
	color = colorName;
}

string Region::getName(){
	return name;
}

string Region::getColor(){
	return color;
}

vector<Region> Region::getNeighbors(){
	return neighborRegions;
}

void Region::removeColor(){
	color = WITHOUT_COLOR;
}

bool Region::hasColor(){
	if (color == WITHOUT_COLOR)
		return false;
	return true;
}

void Region::updatePossibleColors(bool flag, string colorName){
	possibleColors[colorName] = flag;
}

// Retorna a quantidade de cores disponíveis para esta região
int Region::getPossibleColors(){
	int cont = 0;
	for (map<string,bool>::iterator it=possibleColors.begin(); it!=possibleColors.end(); ++it){
		if(it->second)
			cont += 1;
	}
	return cont;
}
