
/*
 * ps4-5.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: alecadair
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <sstream>

const unsigned int MAX = 2147483647;

class City{
public:
	std::string name;
	unsigned int vertIndex;
	unsigned int toll;
	bool operator()(City* lhs,City* rhs)
	{
	  return lhs->toll >= rhs->toll;
	}
};

class Map{
public:
	std::map<std::string,std::set<City*> > adjList;
	std::map<std::string,City*> legend;
	//std::list<City> list;
	unsigned int numCities;
};

Map* CreateMapFromInput(){
	Map* roadMap = new Map;
	std::string numCities;
	//First Create Cities
	getline(std::cin,numCities);
	roadMap->numCities = stoi(numCities);
	for(unsigned int i = 0; i < roadMap->numCities; i ++){
		std::set<City*> cities;
		City* city = new City;
		std::string cityName;
		getline(std::cin, cityName);
		std::stringstream stream(cityName);
		unsigned int toll = 0;
		for(unsigned int j = 0; j < 2; j++){
			std::string name;
			if(j == 0){
				stream >> name;
				city->name = name;
			}else{
				stream >> toll;
				city->toll = toll;
			}
		}
		city->vertIndex = i;
		roadMap->adjList[city->name] = cities;
		roadMap->legend[city->name] = city;

	}

	std::string numRoads;
	getline(std::cin,numRoads);
	unsigned int numHighways = stoi(numRoads);
	for(unsigned int i = 0; i < numHighways; i ++){
		std::string city;
		getline(std::cin,city);
		std::stringstream ss(city);
		std::string city1, city2;
		for(unsigned int j = 0; j < 2; j++){
			if(j == 0){
				ss >> city1;
			}
			else{
				ss >> city2;
			}
		}
		roadMap->adjList[city1].insert(roadMap->legend[city2]);
	}
	return roadMap;
}

unsigned int Dijkstra(Map* roadMap,std::string city1, std::string city2){
	City* city1Ptr = roadMap->legend[city1];
	City* city2Ptr = roadMap->legend[city2];
	std::priority_queue<City*,std::vector<City*>, City> queue;
	unsigned int distances[roadMap->numCities];
	City* previousCities[roadMap->numCities];
	for(int i = 0; i < roadMap->numCities; i++){
		distances[i] = MAX;
		previousCities[i] = 0;
	}
	queue.push(city1Ptr);
	distances[city1Ptr->vertIndex] = 0;
	while(!queue.empty()){
		City* cityPtr = queue.top();
		queue.pop();
		std::set<City*>::iterator i;
		std::set<City*> list = roadMap->adjList[cityPtr->name];
		for(i = list.begin(); i != list.end(); i++){
			unsigned int neighborVertInd = (*i)->vertIndex;
			std::string neighborName = (*i)->name;
			unsigned int neighborToll = (*i)->toll;
			//unsigned int total = distances.at(neighborVertInd);
			unsigned int neighborDistance = distances[cityPtr->vertIndex]+ neighborToll;
			if(distances[neighborVertInd] > neighborDistance){
				distances[neighborVertInd] = neighborDistance;
				previousCities[neighborVertInd] = cityPtr;
				queue.push(*i);
			}
		}
	}

	return distances[city2Ptr->vertIndex];
}
unsigned int CalculateTrip(Map* roadMap,std::string city1, std::string city2){
	//std::cout << "CITY1 " << roadMap->legend[city1]->name <<" CITY2 "<<roadMap->legend[city2]->name<<std::endl;
	unsigned int result = 0;
	return result;
}

int main (int argc, char** argv){
	Map* roadMap = CreateMapFromInput();
//	for(std::map<std::string,std::set<City*> >::iterator it = roadMap->adjList.begin(); it != roadMap->adjList.end(); it++){
//		for(std::set<City*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
//			City* city = *it2;
//		}
//	}
	unsigned int numTrips = 0;
	std::string trips;
	getline(std::cin,trips);
	numTrips = stoi(trips);
	for(unsigned int i = 0; i < numTrips; i++){
		std::string city1, city2;
		std::string line;
		getline(std::cin,line);
		std::stringstream str(line);
		for(unsigned int j = 0; j < 2; j++){
			if(j == 0){
				str >> city1;
			} else{
				str >> city2;
			}
		}
		unsigned int cost = Dijkstra(roadMap,city1,city2);
		if(cost == MAX){
			std::cout << "NO" << std::endl;
		}else{
			std::cout << cost << std::endl;
		}
	}
	return 0;
}
