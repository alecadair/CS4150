/*
 * ps7-7.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: adair
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>


unsigned long modulus(unsigned long x, unsigned long y){
	if(x < 0){
		return (unsigned long)-((-x)%y);
	}else{
		return (unsigned long)x%y;
	}
}

unsigned long mod_exp(unsigned long x, unsigned long y, unsigned long N){
//	long z = 1;
	unsigned long result = 1;
	x = x%N;
	do{
		if(y&1){
			result = modulus(result*x,N);
		}
		y = y >>1;
		x = modulus((x*x),N);
	}while(y > 0);
	return result;
//	unsigned long z = 1;
//	unsigned long bitmask = 0x8000000000000000;
//	for(int i = 0; i < 64;i ++){
//		unsigned long result;
//		result = bitmask&y;
//		result = result >> (63 - i);
//		if(result == 1){
//			z = modulus(x*z*z,N);
//		}
//		else{
//			z = modulus(z*z,N);
//		}
//		bitmask = bitmask >> 1;
//	}
//	return z;
//
//	if(y == 0){
//		return 1;
//	}
//	else{
//		long z = mod_exp(x,y>>1,N);
//		if((y & 0x1) == 0){
//			return modulus((z*z),N);
//		}
//		else{
//			return modulus((x*(z*z)),N);
//		}
//	}
}

long greatest_common_divisor(long a, long b){
	/*if(b == 0){
		return a;
	}
	else{
		return greatest_common_divisor(b, modulus(a,b));
	}*/
	while(b >0){
		unsigned long aModB = modulus(a,b);
		a = b;
		b = aModB;
	}
	return a;
}

/*
 * x and y are for avoiding returning an array
 */
long extended_euclids(long a, long b, long* x, long* y){
	//long* result = new long[3];
	if(b == 0){
		*x = 1;
		*y = 0;
		return a;
	}
	else{
		long xPrime,yPrime = 0;
		long d = extended_euclids(b,modulus(a,b),&xPrime,&yPrime);
		*x = yPrime;
		*y = (xPrime - (a/b)*yPrime);
		return d;
	}
}

long modular_inverse(long a, long N){

	long x, y;
	unsigned long d = extended_euclids(a,N,&x,&y);
	if(d == 1){
		//long offs = (x %(N+N));// modulus(x,N+N);
		//offs = offs%N;//modulus(offs,N);
		return(x%N+N)%N;
		//std::cout << (x%N+N)%N << std::endl;
		//return;		//return modulus(x,N);
	}else{
		return -1;
		//std::cout << "none" << std::endl;
		//return;
	}
}

char is_prime(long N){
	if((N== 2) || (N==3) || (N==5)){
		return true;
	}
	if(mod_exp(2,N-1,N)!= 1){
		return false;
	}
	if(mod_exp(3,N-1,N) != 1){
		return false;
	}
	if(mod_exp(5,N-1,N) != 1){
		return false;
	}
	return true;
}

void key(unsigned long p, unsigned long q){
	unsigned long N = p*q; //N is modulus
	std::cout << N <<" ";
	unsigned long phi = (p-1)*(q-1);
	unsigned long pub_exp = 0;
	unsigned long gcd = 0;
	for(unsigned long i = 2; gcd != 1; i ++){
		gcd = (unsigned long)greatest_common_divisor((long)i,(long)phi);
		pub_exp = i;
	}
	std::cout << pub_exp << " ";
	unsigned long priv_exp = 0;
	priv_exp = modular_inverse(pub_exp,phi);
//	for(long i = 0;i < N;i++){
//		priv_exp = modulus(pub_exp*i,phi);
//		if(priv_exp == 1){
//			priv_exp = i;
//			break;
//		}
//	}
	std::cout << priv_exp << std::endl;
	//long public_exp = gcd(e,phi) != 1;
	return;
}
int main(int argc, char** argv){
	std::string line;
//	for(long i = 1; i < 50; i ++){
//		//std::cout << "i: " << i << "\tis prime: " << (int)is_prime(i) << std::endl;
//	}
	while(std::getline(std::cin,line)){
		std::stringstream ss(line);
		std::string toke;
		std::vector<std::string> command_strings;
		while(getline(ss,toke,' ')){
			command_strings.push_back(toke);
		}
//		for(unsigned int i = 0; i < command_strings.size(); i ++){
//			std::cout << command_strings[i] <<  " ";
//		}
		std::string command = command_strings[0];
		if(command == "isprime"){
			long num;
			char* endstring;
			num = strtol(command_strings[1].c_str(),&endstring,10);
			if(is_prime(num)){
				std::cout <<"yes"<<std::endl;
			}
			else{
				std::cout<<"no"<<std::endl;
			}
		}else if(command == "gcd"){
			long num1,num2;
			char* end1; char* end2;
			num1 = strtol(command_strings[1].c_str(),&end1,10);
			num2 = strtol(command_strings[2].c_str(),&end2,10);
			std::cout<< greatest_common_divisor(num1,num2) << std::endl;
		}else if(command == "exp"){
			unsigned long num1,num2, num3;
			char* end1; char* end2; char* end3;
			num1 = strtoul(command_strings[1].c_str(),&end1,10);
			num2 = strtoul(command_strings[2].c_str(),&end2,10);
			num3 = strtoul(command_strings[3].c_str(),&end3,10);

			std::cout<< mod_exp(num1,num2,num3) << std::endl;
		}else if(command == "inverse"){
			long num1,num2;
			char* end1; char* end2;
			num1 = strtol(command_strings[1].c_str(),&end1,10);
			num2 = strtol(command_strings[2].c_str(),&end2,10);
			//modular_inverse(num1,num2);
			if(modular_inverse(num1,num2) != -1){
				std::cout<< modular_inverse(num1,num2) << std::endl;
			}
			else{
				std::cout << "none" << std::endl;
			}
		}else if(command == "key"){
			unsigned long num1,num2;
			char* end1; char* end2;
			num1 = strtoul(command_strings[1].c_str(),&end1,10);
			num2 = strtoul(command_strings[2].c_str(),&end2,10);
			key(num1,num2);
		}

	}
	//long gcd = greatest_common_divisor(0,0);
	return 0;
}
