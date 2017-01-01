//Alec Adair U0725062
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
typedef struct{
	int wait_time;
	int serial;
	int cash;
}Person;
bool compare_cash(const Person &a, const Person &b){
	return a.cash > b.cash;
}
int main(int argc, char** argv){
	int N, T;
	scanf("%d %d",&N,&T);
	std::vector<Person> customers;
	for(int i = 0; i < N; i++){
		Person p;
		p.serial = i;
		int c, t;
		scanf("%d %d",&c,&t);
		p.cash = c;	p.wait_time = t;
		customers.push_back(p);
	}
	std::sort(customers.begin(),customers.end(),compare_cash);
	std::vector<int> final_queue(N, 0);
	for(int i = 0; i < customers.size(); i++){
		for(int j = customers[i].wait_time; j >= 0; j --){
			if(final_queue[j] == 0){
				final_queue[j] = customers[i].cash;
				break;
			}
		}
	}
	int sum = 0;
	for(int i = 0; i < final_queue.size(); i++){
		sum += final_queue[i];
	}
	std::cout << sum << std::endl;
	return 0;
}



