/*
 * ps6-6.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: alecadair
 */
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <iostream>
#include <queue>

const int max = 100000000;

class Edge{
public:
	int source;
	int dest;
	int weight;
	Edge(int _source, int _dest, int _weight){
		source = _source;
		dest = _dest;
		weight = _weight;
	}

};
class Node{
public:
	int index;
	std::vector<Edge> edges;

};
class Graph{
public:
	std::vector<Node> nodes;
};
void Dijkstra(Graph* graph, int source, int* distances){
	int i;
	std::priority_queue<int, std::vector<int>,std::greater<int> > pq;
	pq.push(source);
	distances[source] = 0;
	while(!pq.empty()){
		int currentNode = pq.top();
		pq.pop();
		int numChildren = graph->nodes.at(currentNode).edges.size();
		for(i = 0; i < numChildren; i++){
			Edge edge  = graph->nodes.at(currentNode).edges.at(i);
			int dist = distances[currentNode] + edge.weight;
			if(dist < distances[edge.dest]){
				distances[edge.dest] = dist;
				pq.push(edge.dest);
			}
		}
	}
	return;
}

int main(){
	int i;
	int numNodes;
	int numEdges;
	int numQueries;
	int startNodeIndex;
	while(1){
		scanf("%d %d %d %d",&numNodes,&numEdges,&numQueries,&startNodeIndex);
		if(numNodes == 0){
			return 0;
		}
		else{
			std::cout << std::endl;
		}
		Graph graph;
		for(i = 0; i < numNodes; i++){
			Node node;
			node.index = i;
			graph.nodes.push_back(node);
		}
		for(i = 0; i < numEdges; i ++){
			int u, v, w;
			scanf("%d %d %d",&u,&v,&w);
			Edge edge(u,v,w);
			graph.nodes.at(u).edges.push_back(edge);
		}
		int distances[numNodes];
		for(i = 0; i < numNodes; i ++){
			distances[i] = max;
		}
		Dijkstra(&graph, startNodeIndex,distances);
		for(i = 0; i < numQueries; i++){
			int quer;
			scanf("%d", &quer);
			if(distances[quer] != max){
				std::cout << distances[quer] << std::endl;
			}else{
				std::cout <<"Impossible" << std::endl;
			}
		}
	}
}