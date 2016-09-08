#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <time.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC/1000)

using namespace std;


bool wayToSort(int i,int j){
	return i > j;
}

int calculateDays(vector<int> days){
	sort(days.begin(), days.end(), wayToSort);
	int mostDays = 0;
	for(unsigned int i = 0; i < days.size(); i++){
		int numDays = days.at(i) + i+2;
		if(numDays > mostDays){
			mostDays = numDays;
		}
	}

	return mostDays;
}

double TimeExperiment(int size){
	//construct new random vector of ints
	vector<int> listOfDays;
	for(int i = 0; i < size; i++){
		listOfDays.push_back(rand());
	}
	chrono:: duration<double, milli> elapsed;
	long repetitions = 1;
	do{
		repetitions *= 2;
		//std::chrono::steady_clock::time_point start, finish;
		auto start = chrono::high_resolution_clock::now();
		for(int i = 0; i < repetitions; i ++){
			calculateDays(listOfDays);
		}
	    auto finish =chrono::high_resolution_clock::now();

	    elapsed = finish - start;
	}while(elapsed.count() < 1000);
	double totalAverage = elapsed.count() / repetitions;
	chrono:: duration<double, milli> elapsed2;
	repetitions = 1;
	do{
		repetitions *= 2;
		//std::chrono::steady_clock::time_point start, finish;
		auto start = chrono::high_resolution_clock::now();
		for(int i = 0; i < repetitions; i ++){
			//calculateDays(listOfDays);
		}
	    auto finish =chrono::high_resolution_clock::now();

	    elapsed2 = finish - start;
	}while(elapsed2.count() < 1000);
	double overHeadAverage = elapsed2.count()/repetitions;


	return totalAverage - overHeadAverage;
}

void RunExperiment(){
	cout << "\nSize\tTime (msec)\tDelta (msec)"<<endl;
	double previousTime = 0.0;
	for(int n = 256; n < (256 << 10); n *= 2){
		//cout << n << endl;
		double currentTime = TimeExperiment(n);
			cout << n  << "     " << currentTime << "\t\t"
				<< (currentTime - previousTime)<< endl;
		//clock_t  = clock();
		previousTime = currentTime;
	}
	return;
}

int main(int argc, char* argv[]){

//	int numTrees;
//	int streamHolder;
//	string days;
//	getline(cin,days);
//	numTrees = atoi(days.c_str());
//	getline(cin,days);
//	stringstream stream(days);
//	vector<int> numDays;
//	while(stream >> streamHolder){
//		numDays.push_back(streamHolder);
//	}

	//std::sort(numDays.begin(),numDays.end(),wayToSort);
	/*int mostDays = 0;
	for(int i = 0; i < numDays.size();i++){
		int days = numDays.at(i) + i+2;
		if(days > mostDays){
			mostDays = days;
		}
	}*/
	//cout << mostDays << endl;
	RunExperiment();
	return 0;
}


