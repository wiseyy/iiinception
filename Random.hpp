#pragma once

#include<iostream>
#include<vector>
#include<time.h>
#include<random>
#include<chrono>

using namespace std;

#define uid(a,b) uniform_int_distribution<long long>(a,b)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// function to constraint a number in a given range
int constraint(int x, int lower, int upper);
// generate a random array of given dimension (elements might repeat)
vector<int> generateRandomVector(int n, int lower, int upper);
// generate a random array of given dimension (all elements are distinct)
vector<int> generateRandomVectorDistinct(int n, int lower, int upper);
// function to give a random integer every different time
int getRandomInt(int lower, int upper);

// implementation of the above design 
int constraint(int x, int lower, int upper){
	return x %(upper - lower + 1)  +  lower ;
}

vector<int> generateRandomVector(int n, int lower, int upper){
	vector<int> randomVector(n);
	for(int i = 0; i<n; ++i){
		randomVector[i] = uid(lower, upper);
	}
	return randomVector;
}

vector<int> generateRandomVectorDistinct(int n, int lower, int upper){
	srand(time(0));
	vector<int> randomVector(n);
	int i = 0;
	while(i<n){
		int gen = uid(lower, upper);
		bool found = false;
		for(int j = 0; j<i; ++j){
			if (randomVector[j] == gen){
				found = true; 
				break; 
			}
		}
		if (!found){
			randomVector[i] = gen;
			i++;
		}
	}
	return randomVector;
}

int getRandomInt(int lower, int upper){
	return uid(lower, upper);
}