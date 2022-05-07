#pragma once

#include<iostream>
#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h>
#include <random>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "constants.hpp"
#include "Texture.hpp"
#include "Random.hpp"

using namespace std; 

// #define uid(a,b) uniform_int_distribution<long long>(a,b)(rng)
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


class Gift{
public:
	Gift(int val, int x, int y, std::string path, SDL_Renderer* Renderer);
	SDL_Rect getBox(); 
	void destroy();
	void setValue(int val);
	void render(SDL_Rect &camera, SDL_Renderer* Renderer);
	int getValue();
	// string getID();
private:
	// string id;
	int value;
	Texture giftTex; 
	SDL_Rect collBox; 
};

// function to generate item objects with given x and y coordinates
vector<Gift*> generateGifts(std::string path, vector<pair<int, int>> coordinates, SDL_Renderer* Renderer);
// function to render items on the map
void renderGifts(vector<Gift*> &gifts, SDL_Rect &camera, SDL_Renderer* Renderer);


// impelementation of the above functions and methods

Gift::Gift(int val, int x, int y, std::string path, SDL_Renderer* Renderer){
	// id = idx;
	value = val;
	collBox = {x, y, GIFT_WIDTH, GIFT_HEIGHT};
	if(!giftTex.loadfromFile(path, Renderer)){
		cout << "Couldn't load gift from the path\n" ;
	}
	giftTex.setDimensions(GIFT_WIDTH, GIFT_HEIGHT);
}

SDL_Rect Gift::getBox(){
	return collBox;
} 
void Gift::destroy(){
	giftTex.free();
	value = 0;
	collBox = {0,0,0,0}; 
}
void Gift::setValue(int val){
	value = val;
}
int Gift::getValue(){
	return value;
}

void Gift::render(SDL_Rect &camera, SDL_Renderer* Renderer){
	if (collBox.x >= camera.x && collBox.x <= camera.x + camera.w && collBox.y >= camera.y && collBox.y <= camera.y + camera.h)
		giftTex.render(collBox.x-camera.x, collBox.y-camera.y, Renderer); 
}

vector<Gift*> generateGifts(std::string path, vector<pair<int, int>> coordinates, SDL_Renderer* Renderer){
	vector<Gift*> items(TOTAL_GIFTS);
	for(int i = 0; i<TOTAL_GIFTS; ++i){
		Gift* c = new Gift( uid(10, 100) ,coordinates[i].first, coordinates[i].second, path, Renderer); 
		items[i] = c;
	}
	return items;
}

void renderGifts(vector<Gift*> &gifts, SDL_Rect &camera, SDL_Renderer* Renderer){
	for(int i = 0; i<gifts.size(); ++i){
		gifts[i]->render(camera, Renderer);
	}
}
