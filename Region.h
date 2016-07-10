/*
 * Region.h
 *
 *  Created on: May 4, 2013
 *      Author: roque
 */

#ifndef REGION_H_
#define REGION_H_
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Region{
	string name;
	string color;
	vector<Region> neighborRegions; //Lista das regiões vizinhas.
	map<string,bool> possibleColors; //Para MVR

public:
	Region();
	Region(string name);
	void setNeighbor(Region region);
	void setColor(string colorName);
	void removeColor();
	void updatePossibleColors(bool flag, string colorName);
	vector<Region> getNeighbors();
	string getName();
	string getColor();
	int getPossibleColors();
	bool hasColor();
};
#endif /* REGION_H_ */

