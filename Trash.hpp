#pragma once

#include<iostream>
#include "SDL.h" 
#include "SDL_image.h"
#include <vector>
#include <utility>
#include "constants.hpp"
#include "Texture.hpp"
using namespace std; 

// Trash Object Class 
class Trash{
public:
	Trash(int x, int y, std::string path, SDL_Renderer* Renderer);
	SDL_Rect getBox(); 
	void destroy();
	void render(SDL_Rect &camera, SDL_Renderer* Renderer);
private:
	Texture trashTex; 
	SDL_Rect collBox; 
};
// function to generate trash objects with given x and y coordinates
vector<Trash*> generateTrash(std::string path, vector<pair<int, int>> coordinates , SDL_Renderer* Renderer);
// function to render trash on the map
void renderTrash(vector<Trash*> &trash, SDL_Rect &camera, SDL_Renderer* Renderer);

// implementation of various functions and methods

Trash::Trash(int x, int y, std::string path, SDL_Renderer* Renderer){
	collBox = {x,y,TRASH_WIDTH, TRASH_HEIGHT}; 
	if(!trashTex.loadfromFile(path, Renderer)){
		cout << "Couldn't load trash from the path\n" ;
	}
	trashTex.setDimensions(TRASH_WIDTH, TRASH_HEIGHT);
}

void Trash::render(SDL_Rect &camera, SDL_Renderer* Renderer){
	if (collBox.x >= camera.x && collBox.x <= camera.x + camera.w && collBox.y >= camera.y && collBox.y <= camera.y + camera.h)
		trashTex.render(collBox.x-camera.x, collBox.y-camera.y, Renderer); 
}

SDL_Rect Trash::getBox(){
	return collBox; 
}

void Trash::destroy(){
	trashTex.free();
	collBox = {0,0,0,0}; 
}


vector<Trash*> generateTrash(std::string path, vector<pair<int, int>> coordinates, SDL_Renderer* Renderer){
	vector<Trash*> trash(TOTAL_TRASH);
	for(int i = 0; i<TOTAL_TRASH; ++i){
		Trash* c = new Trash(coordinates[i].first,coordinates[i].second, path, Renderer); 
		trash[i] = c;
	}
	return trash;
}

void renderTrash(vector<Trash*> &trash, SDL_Rect &camera, SDL_Renderer* Renderer){
	for(int i = 0; i<trash.size(); ++i){
		trash[i]->render(camera, Renderer);
	}
}

