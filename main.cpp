/*
 * main.cpp
 *
 *  Created on: May 4, 2013
 *      Author: roque
 */

#include "Map.h"

int main(){
	char filePath[100];
	int option;
	while(true){
		printf(" Selecione uma opção\n");
		printf("  1 Backtracking simples\n");
		printf("  2 Backtracking simplesBacktracking com verificação adiante\n");
		printf("  3 Backtracking com verificação adiante e MVR\n");
		printf("  4 Backtracking com verificação adiante, MVR e grau\n");
		printf("  0 Sair\n");
		scanf ("%d",&option);
        if(option  == 0)
			return 0;

		printf(" Selecione a direção do arquivo de entrada\n");
		scanf ("%s",filePath);

		Map map;

		if(map.readInputs(filePath) == false)
			return 0;
		if(option == 1){
			map.backtracking(0);
			map.printMap();
		}
		else if(option  == 2){
			map.backtrackingFC(0);
			map.printMap();
		}
		else if(option  == 3){
			map.backtrackingMVR(0);
			map.printMap();
		}
		else if(option  == 4){
			map.backtrackingMVRDegree(0);
			map.printMap();
		}
	}
}


