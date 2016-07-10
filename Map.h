/*
 * Map.h
 *
 *  Created on: May 4, 2013
 *      Author: roque
 */

#ifndef MAP_H_
#define MAP_H_
#include "Region.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Map {
	vector<Region> regionList; //Lista das regiões.
	vector<string> colors; //Lista com os cores Azul, Amarelo, Verde e Vermelho (domínio do problema).

public:

	Map();
	bool readInputs(string pathFile);
	void doGraph(vector<string>);
	void printMap();
	void updateNeighbors(int variable, bool flag, string colorName);
	int backtracking(int assignments);
	int backtrackingFC(int assignments);
	int backtrackingMVR(int assignments);
	int backtrackingMVRDegree(int assignments);
	int findRegion(string regionName);
	int selectVariable();
	int selectVariableMVR();
	int selectVariableMVRDegree();
	int getConstraints(int variable);
	vector<string>split(string s);
	bool hasConstraint(int variable, string colorName);
	bool forwardChecking(int variable);
};

#endif /* MAP_H_ */
