#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
	int n;
	scanf("%d",&n);

	vector<vector<int> > adj_matrx;
	for(int i = 0; i < n; i++){
		string line;
		getline(cin,line);
		stringstream ss(line);
		string token;
 		while(ss >> token){
 			adj_matrx[i].push_back(stoi(token));
 		}
	}
	return 0;
}