// This file contains the wrapper class for an angry professor
#pragma once

#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <utility>
#include<vector>
#include "constants.hpp"
#include "Texture.hpp"
#include "TileMap.hpp"
// #include "Collisions.hpp"
#include "Random.hpp"
bool checkCollisionX(SDL_Rect a, SDL_Rect b)
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

bool touchesWallX(SDL_Rect obj, Tile* collision[]){
	for(int i = 0; i< TOTAL_TILES ; ++i){
		if(checkCollisionX(obj, collision[i]->getBox()) && collision[i]->getType() == 0 ){
			return true;
		}
	}
	return false;
}
class Prof{
public:
	static const int PROF_WIDTH = 25;
	static const int PROF_HEIGHT= 25;
	Prof(std::string path, int x, int y,int vx, int vy ,SDL_Renderer* Renderer);
	void move(Tile* collisions[]);
	SDL_Rect getBox();
	void render(SDL_Rect &camera,int frame, SDL_Renderer* Renderer); 
	int getAnger();
	void setAnger(int x);
	int ProfTimer = 0;
	int dir = -1;
private:
	// Velocity of the prof
	int xVel, yVel;
	// Texture attribute for rendering
	Texture SpriteTex;
	// Collision Box for the prof
	SDL_Rect collBox ;
	// Prof timer for updating anger after sometime meeting a student

	// anger of the prof
	int anger;
};

Prof::Prof(std::string path, int x, int y, int vx, int vy, SDL_Renderer* Renderer){
	collBox = {x,y, PROF_WIDTH, PROF_HEIGHT};
	xVel = vx; 
	yVel = vy;
	if(!SpriteTex.loadfromFile(path, Renderer))
	{
		printf( "Failed to load Prof texture!\n" );
	} 
	anger = getRandomInt(5, 10);
}

SDL_Rect Prof::getBox(){
	return collBox;
}
int Prof::getAnger(){
	return anger;
}

void Prof::move(Tile* collisions[]){
	//Move the dot left or right
    collBox.x += xVel;
    //If the dot went too far to the left or right
    if( ( collBox.x < 0 ) || ( collBox.x + PROF_WIDTH > MAP_WIDTH ) || touchesWallX(collBox, collisions))
    {
        collBox.x -= xVel;
        xVel *= -1; 
    }
	// Move the dot up or downs
    collBox.y += yVel;
    //If the dot went too far up or down
    if( (collBox.y < 0 ) || ( collBox.y + PROF_HEIGHT > MAP_HEIGHT ) || touchesWallX(collBox, collisions))
    {
        collBox.y -= yVel;
        yVel *= -1;
    }
    if (xVel == 0 && yVel == 0){
        	dir = -1;
    }
    if (yVel < 0){
    	dir = 1;
    }
    else if(yVel > 0){
    	dir = 0;
    }
    else if(xVel > 0){
    	dir = 3;
    }
    else if (xVel < 0){
    	dir = 2;
    }
}

void Prof::render(SDL_Rect &camera, int frame, SDL_Renderer* Renderer){
	SDL_Rect ProfRect = {collBox.x - camera.x, collBox.y - camera.y,PROF_WIDTH, PROF_HEIGHT};
	SDL_Rect clip;
	if (dir == 0){
		clip = {frame%4 * SpriteTex.getWidth()/4, 0*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 2){
		clip = {frame%4 * SpriteTex.getWidth()/4, 1*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 3){
		clip = {frame%4* SpriteTex.getWidth()/4, 2*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 1){
		clip = {frame%4 * SpriteTex.getWidth()/4, 3*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	} 
	else{
		clip = {0, 0, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	// cout<<SpriteTex.getHeight()<<endl;
	SDL_RenderCopy(Renderer, SpriteTex.getTexture(), &clip, &ProfRect);
}
void Prof::setAnger(int x){
	anger = x;
}

vector<Prof*> generateProfsX(std::string path, vector<pair<int, int>> coordinates, SDL_Renderer* Renderer){
	vector<Prof*> profs(TOTAL_PROFS);
	for(int i = 0; i<TOTAL_PROFS; ++i){
		Prof* c = new Prof(path, coordinates[i].first,coordinates[i].second, PROF_SPEED, 0, Renderer); 
		profs[i] = c;
	}
	return profs;
}

vector<Prof*> generateProfsY(std::string path, vector<pair<int, int>> coordinates, SDL_Renderer* Renderer){
	vector<Prof*> profs(TOTAL_PROFS);
	for(int i = 0; i<TOTAL_PROFS; ++i){
		Prof* c = new Prof(path, coordinates[i].first,coordinates[i].second, 0, PROF_SPEED, Renderer); 
		profs[i] = c;
	}
	return profs;
}
void renderProfs(vector<Prof*> &profs,int frame, SDL_Rect &camera, SDL_Renderer* Renderer){
	for(int i = 0; i<profs.size(); ++i){
		profs[i]->render(camera,frame, Renderer);
	}
}

void moveProfs(vector<Prof*> &profs, Tile* tiles[], SDL_Renderer* Renderer){
	for(int i = 0; i<profs.size(); ++i){
		profs[i]->move(tiles);
	}
}

void resetAngryProfs(vector<Prof*> &profs, Tile* tiles[]){
	for(int i = 0; i<profs.size(); ++i){
		profs[i]->move(tiles);
	}
}


