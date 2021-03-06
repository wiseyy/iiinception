#pragma once 

#include<iostream>
#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h>
#include <utility>
#include "constants.hpp"
#include "Coin.hpp"
#include "Texture.hpp"
#include "TileMap.hpp"
#include "Gift.hpp"
#include "Prof.hpp"
#include "Trash.hpp"

using namespace std;


// Detect collisisions between to boxes
bool checkCollision(SDL_Rect a, SDL_Rect b);
// Check if a moving object collides with a wall tile
bool touchesWall(SDL_Rect obj, Tile* collision[]);
// function to check if something touches a coin or not
pair<bool, int> touchesCoin(SDL_Rect obj, vector<Coin*> &coins);
// Collision with gift
int touchesGiftIndex(SDL_Rect obj, vector<Gift*> &gifts);
bool touchesGift(SDL_Rect obj, vector<Gift*> &gifts);
// collision with prof
bool touchesProf(SDL_Rect obj, vector<Prof*> &profs);
int touchesProfIndex(SDL_Rect obj, vector<Prof*> &profs);


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

bool touchesWall(SDL_Rect obj, Tile* collision[]){
	for(int i = 0; i< TOTAL_TILES ; ++i){
		if(checkCollision(obj, collision[i]->getBox()) && collision[i]->getType() == 0 ){
			return true;
		}
	}
	return false;
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

int touchesGiftIndex(SDL_Rect obj, vector<Gift*> &gifts){
    for(int i = 0; i<TOTAL_GIFTS; ++i){
        // if a collision between any item and object then touched item
        if(checkCollision(obj,gifts[i]->getBox()) ){
            return i;
        }
    }
    // object touches no item
    return -1;
}

bool touchesProf(SDL_Rect obj, vector<Prof*> &profs){
    for(int i = 0; i<TOTAL_PROFS; ++i){
        // if a collision between any item and object then touched item
        if(checkCollision(obj,profs[i]->getBox()) ){
            return true;
        }
    }
    // object touches no item
    return false;
}

int touchesProfIndex(SDL_Rect obj, vector<Prof*> &profs){
    for(int i = 0; i<TOTAL_PROFS; ++i){
        // if a collision between any item and object then touched item
        if(checkCollision(obj,profs[i]->getBox()) ){
            return i;
        }
    }
    // object touches no item
    return -1;
}

bool touchesGift(SDL_Rect obj, vector<Gift*> &gifts){
    for(int i = 0; i<TOTAL_GIFTS; ++i){
        // if a collision between any item and object then touched item
        if(checkCollision(obj,gifts[i]->getBox()) ){
            return true;
        }
    }
    // object touches no item
    return false;
}

bool touchesTrash(SDL_Rect obj, vector<Trash*> &trash){
    for(int i = 0; i<TOTAL_TRASH; ++i){
        // if a collision between any item and object then touched trash
        if(checkCollision(obj,trash[i]->getBox()) ){
            return true;
        }
    }
    // object touches no trash
    return false;
}

int touchesTrashIndex(SDL_Rect obj, vector<Trash*> &trash){
    for(int i = 0; i<TOTAL_TRASH; ++i){
        // if a collision between any item and object then touched item
        if(checkCollision(obj,trash[i]->getBox()) ){
            return i;
        }
    }
    // object touches no item
    return -1;
}

bool touchesTrashCan(SDL_Rect obj, Tile* trashCan[]){
    for(int i = 0; i< TOTAL_TILES ; ++i){
        if(checkCollision(obj, trashCan[i]->getBox()) && trashCan[i]->getType() != 0 ){
            return true;
        }
    }
    return false;
}