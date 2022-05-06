#pragma once 

#include<iostream>
#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h>
#include <utility>
#include "constants.hpp"
#include "Coin.hpp"
#include "Texture.hpp"
#include "TileMap.hpp"

using namespace std;

// Detect collisisions between to boxes
bool checkCollision(SDL_Rect a, SDL_Rect b);
// Check if a moving object collides with a wall tile
bool touchesWall(SDL_Rect obj, Tile* buildings[], Tile* roads[]);
// function to check if something touches a coin or not
pair<bool, int> touchesCoin(SDL_Rect obj, vector<Coin*> &coins);

// implementation of the above functions

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
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

    if( rightA <= leftB || leftA >= rightB ){
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool touchesWall(SDL_Rect obj, Tile* roads[]){
	for(int i = 0; i< TOTAL_TILES ; ++i){
		if(checkCollision(obj, roads[i]->getBox()) && roads[i]->getType() != 0 ){
			return false;
		}
	}
	return true;
}

pair<bool, int> touchesCoin(SDL_Rect obj, vector<Coin*> &coins){
    for(int i = 0 ; i< TOTAL_COINS; ++i){
        // if a collision between any coin and object then touched coin
        if(checkCollision(obj, coins[i]->getBox())){
            coins[i]->destroy();
            coins[i]->setValue(0);
            return {true, i};
        }
    }
    // object touches no coin 
    return {false, -1};
}
