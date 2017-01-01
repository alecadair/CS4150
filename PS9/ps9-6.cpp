#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

int main(int argc, char** argv){
	unsigned int i;
    unsigned int n;
    scanf("%d",&n);
    std::vector<int> stops;
    for(i = 0; i <= n; i++){
        int dist;
        scanf("%d",&dist);
        stops.push_back(dist);
    }
    std::vector<int> optimal;
    for(i = 0; i < stops.size(); i++){
        optimal.push_back(pow(400 - stops[i],2));
    	unsigned int j = 0;
        for(; j < i; j++){
            int current_penalty = pow(400 - (stops[i] - stops[j]),2);
            if((optimal[j] + current_penalty) < optimal[i]){
                optimal[i] = optimal[j] + current_penalty;
            }
    	}
    }
    std::cout << optimal[n] << std::endl;
    return 0;
}
