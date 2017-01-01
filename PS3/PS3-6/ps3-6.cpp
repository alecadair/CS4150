/*
 * ps3-6.cpp
 *
 *  Created on: Sep 17, 2016
 *      Author: adair
 */
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <math.h>
#include <vector>

class Point{
public:
	long  x, y;
};

class Galaxy{
public:
	long radius;
	Point location;
	long starCount;
};

class  UniverseTreeNode{
public:
  Galaxy* galaxy;
  UniverseTreeNode* left;
  UniverseTreeNode* right;
};

UniverseTreeNode* AddGalaxy(Galaxy* galaxy, UniverseTreeNode* rootNode){
	if(rootNode == 0){
		rootNode = new UniverseTreeNode;
		rootNode->galaxy = galaxy;
		rootNode->left = 0;
		rootNode->right = 0;
		return rootNode;
	}
	else{
		UniverseTreeNode* currentNode = rootNode;
		while(currentNode != 0){
			long galaxyValue =(long) galaxy->location.x*galaxy->location.x +(long) galaxy->location.y*galaxy->location.y;
			long nodeValue = (long) currentNode->galaxy->location.x*currentNode->galaxy->location.x + (long)currentNode->galaxy->location.y*currentNode->galaxy->location.y;
			if(galaxyValue <= nodeValue){
				if(currentNode->left == 0){
					currentNode->left = new UniverseTreeNode;
					currentNode->left->galaxy = galaxy;
				//	currentNode->left->galaxy->
					currentNode->left->left = 0;
					currentNode->left->right = 0;
					currentNode = 0;
				}
				else{
					currentNode = currentNode->left;
				}
			}
			else{
				if(currentNode->right == 0){
					currentNode->right = new UniverseTreeNode;
					currentNode->right->galaxy = galaxy;
					currentNode->right->right = 0;
					currentNode->right->left = 0;
					currentNode = 0;
				}
				else{
					currentNode = currentNode->right;
				}
			}
		}
		return rootNode;
	}
}

std::vector<Point> GetInput(long numStars){
	std::vector<Point> coords;
	for(long i = 0; i <numStars; i++){
		Point p;
		std::string coordS;
		std::getline(std::cin,coordS);
		std::stringstream stream2(coordS);
		long coord;
		long s = 0;
		while(stream2 >> coord){
			if(s == 0){
				p.x = coord;
				s++;
			}else{
				p.y = coord;
				s = 0;
			}
		}
		coords.push_back(p);
	}
	return coords;
}

Galaxy* FindGalaxy(Point p ,UniverseTreeNode* rootNode, long d){
	long galaxyHash =(long) p.x*p.x +(long) p.y*p.y;
	UniverseTreeNode* currentNode = rootNode;
	while(currentNode != 0){
		long x = currentNode->galaxy->location.x;
		long y = currentNode->galaxy->location.y;
		long nodeHash = (long) x*x + y*y;
		long currentDistance =sqrt(((p.x - currentNode->galaxy->location.x)*(p.x - currentNode->galaxy->location.x) +((p.y - currentNode->galaxy->location.y))*((p.y - currentNode->galaxy->location.y))));
		if(currentDistance <=d){
			return currentNode->galaxy;
		}else{
			if(galaxyHash <= nodeHash){
				currentNode = currentNode->left;
			}
			else{
				currentNode = currentNode->right;
			}
		}
	}
	return 0;
}

int main(int argc, char**argv){
	std::string line;
	std::getline(std::cin,line);
	std::stringstream stream (line);
	long streamHolder;
	long  d;
	long numStars;
	bool first = true;
	while(stream >> streamHolder){
		if(first){
			d = streamHolder;
			first = false;
		}else{
			numStars = streamHolder;
		}
	}
	std::vector<Point> points = GetInput(numStars);
    UniverseTreeNode* treeNode = 0;
	for(long i = 0; i < points.size(); i++){
		Point point = points.at(i);
		long pointHash = (long)point.x*point.x + (long)point.y*point.y;
		Galaxy* galaxy = FindGalaxy(point,treeNode,numStars);
		if(galaxy != 0){
			galaxy->starCount += 1;
			if(galaxy->starCount >(long) points.size()/2){
				std::cout << galaxy->starCount << std::endl;
				return 0;
			}
		}else{
			galaxy = new Galaxy;
			galaxy->starCount = 1;
			galaxy->location = point;
			treeNode = AddGalaxy(galaxy, treeNode);
		}
	}
	std::cout << "NO" << std::endl;
	return 0;
}


