#pragma once

#include<iostream>
#include "SDL.h" 
#include "SDL_image.h"
#include <vector>
#include "constants.hpp"
#include "Texture.hpp"
using namespace std; 

// Coin Object Class 
class Coin{
public:
	Coin(int x, int y, std::string path, SDL_Renderer* Renderer);
	SDL_Rect getBox(); 
	void destroy();
	void setValue(int val);
	void render(SDL_Rect &camera, SDL_Renderer* Renderer);
	int getValue();
private:
	int value = 1;
	Texture coinTex; 
	SDL_Rect collBox; 
};
// function to generate coin objects with given x and y coordinates
vector<Coin*> generateCoins(std::string path, vector<int> x, vector<int> y, SDL_Renderer* Renderer);
// function to render coins on the map
void renderCoins(vector<Coin*> &coins, SDL_Rect &camera, SDL_Renderer* Renderer);

// implementation of various functions and methods

Coin::Coin(int x, int y, std::string path, SDL_Renderer* Renderer){
	collBox = {x,y,COIN_WIDTH, COIN_HEIGHT}; 
	if(!coinTex.loadfromFile(path, Renderer)){
		cout << "Couldn't load coin from the path\n" ;
	}
	coinTex.setDimensions(COIN_WIDTH, COIN_HEIGHT);
}

void Coin::render(SDL_Rect &camera, SDL_Renderer* Renderer){
	if (collBox.x >= camera.x && collBox.x <= camera.x + camera.w && collBox.y >= camera.y && collBox.y <= camera.y + camera.h)
		coinTex.render(collBox.x-camera.x, collBox.y-camera.y, Renderer); 
}

SDL_Rect Coin::getBox(){
	return collBox; 
}

void Coin::destroy(){
	coinTex.free();
	value = 0;
	collBox = {0,0,0,0}; 
}
void Coin::setValue(int val){
	value = val;
}
int Coin::getValue(){
	return value;
}

vector<Coin*> generateCoins(std::string path, vector<int> x, vector<int> y, SDL_Renderer* Renderer){
	vector<Coin*> coins(TOTAL_COINS);
	for(int i = 0; i<TOTAL_COINS; ++i){
		Coin* c = new Coin(x[i], y[i], path, Renderer); 
		coins[i] = c;
	}
	return coins;
}

void renderCoins(vector<Coin*> &coins, SDL_Rect &camera, SDL_Renderer* Renderer){
	for(int i = 0; i<coins.size(); ++i){
		coins[i]->render(camera, Renderer);
	}
}

