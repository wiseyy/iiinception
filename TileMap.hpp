// file for tile map design 
#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <utility>
#include <fstream>
#include "constants.hpp"
#include "Texture.hpp"

using namespace std; 

class Tile{
public:
	Tile(string idx, int x, int y, int tileType );
	int getType();
	SDL_Rect getBox();
	string getID();
	pair<int, int> getCoordinates();
	// void render(SDL_Renderer* Renderer);
private:
	int type; 
	SDL_Rect collBox; 
	string id ;
};

class TileMap{
	public:
		TileMap(std::string sprite, int typeCount, std::string path,string idx,int height, int width, SDL_Renderer* Renderer); 
		void render(SDL_Rect &camera, SDL_Renderer* Renderer); 
		void Debug();   // Printing the state of Map
		Tile* Map[TOTAL_TILES];
		int types; 
	private:
		Texture tileSprite; 
		SDL_Rect TileClips[10000];
};

Tile::Tile(string idx , int x, int y, int tileType){
	//Get the offsets
    collBox.x = x;
    collBox.y = y;

    //Set the collision box
    collBox.w = TILE_WIDTH;
    collBox.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;
}

pair<int, int> Tile::getCoordinates(){
	return {collBox.x , collBox.y};
}
int Tile::getType(){
	return type; 
}

SDL_Rect Tile::getBox(){
	return collBox;
}
string Tile::getID(){
	return id;
}

bool checkCollisionCam(SDL_Rect a, SDL_Rect b){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomA <= topB  || topA >= bottomB)
    {
        return false;
    }

    if( rightA <= leftB || leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

TileMap::TileMap(std::string sprite,int typeCount,  std::string path,string idx,int height, int width, SDL_Renderer* Renderer){
	if (!tileSprite.loadfromFile(sprite, Renderer)){
		cout << "Unable to load map texture\n";
	}
	types = typeCount;
	// setting the map offset
	int x = 0, y = 0;

    //Open the map
    std::ifstream map(path);

  	//If the map couldn't be loaded
    if( map.fail() ){
		cout << "Unable to load map file! " << path <<endl;
    } 
    else{
    	//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i ){
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if(map.fail()){
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				break;
			}

			//If the number is a valid tile number
			if(( tileType >= 0 ) && ( tileType < types)){
				Map[i] = new Tile(idx, x, y, tileType );
			}
			//If we don't recognize the tile type
			else{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= MAP_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		int cnt = 0;
		for(int i = 0; i<height; ++i){
			for(int j = 0; j<width; ++j){
				TileClips[cnt] = {j*TILE_WIDTH, i*TILE_HEIGHT, TILE_WIDTH , TILE_HEIGHT};
				cnt++;
			}
		}
		
    }
} 

void TileMap::render(SDL_Rect &camera, SDL_Renderer* Renderer){
	int n = MAP_HEIGHT/TILE_HEIGHT; 
	int m = MAP_WIDTH/TILE_WIDTH ;
	int cnt = 0;
	for(int j = 0; j< MAP_HEIGHT/TILE_HEIGHT; ++j){
		for(int i = 0; i< MAP_WIDTH / TILE_WIDTH; ++i){
			if(checkCollisionCam( camera, Map[cnt]->getBox())){
				tileSprite.renderSprite(Map[cnt]->getBox().x - camera.x, Map[cnt]->getBox().y - camera.y,Renderer,  &TileClips[Map[cnt]->getType()]); 
			}
			cnt++;
		}
	}
}

void TileMap::Debug(){
	for(int i = 0; i<TOTAL_TILES; ++i){
		cout << Map[i]->getType()<<endl ; 
	}
}
