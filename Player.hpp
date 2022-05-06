#pragma once 

#include<iostream>
#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h>
#include <utility>
#include<vector>
#include "constants.hpp"
#include "Texture.hpp"
#include "Collisions.hpp"


class Player{
	public: 
	// Dimensions of the player 
	static const int PLAYER_WIDTH = 30;
	static const int PLAYER_HEIGHT = 30;

	int PLAYER_VEL = 2;
	// Constructors for the Player
	Player(); 
	Player(std::string path, int x, int y, int vx, int vy, SDL_Renderer* Renderer);
	// Handle the user input from keyboard or mouse
	void handleEvent (SDL_Event &e, SDL_Renderer* Renderer);
	// move player in each game loop
	void move(Tile* roads[], vector<Coin*> &coinList, vector<Gift*> &giftList);
	// render the player according to the camera
	void render(SDL_Rect &camera, int frame, SDL_Renderer* Renderer); 
	// set the camera according to the player
	void setCamera( SDL_Rect& camera );
	// get the collBox for the player
	SDL_Rect getCollBox();
	void getOnYulu(SDL_Renderer* Renderer);
	void getOffYulu(SDL_Renderer* Renderer);
	int getCoins();
	pair<int, int> getCoordinates(){
		return {xPos, yPos};
	}
	int getGifts(){
		return gifts ;
	}
	// vector<SecretItem*> getItemList();
	bool onYulu = false;
	int dir = 0;    //  0 for right , 1 for down , 2 for left , 3 for up 
private:
	// Position of the player
	int xPos, yPos;
	// Velocity of the player
	int xVel, yVel;
	// Texture attribute for rendering
	Texture SpriteTex;
	// Collision Box for the player
	SDL_Rect collBox;
	// extra features
	int coins = 500; 
	int health = 100;
	int gifts = 0;
	// vector<SecretItem*> items; 

};

Player::Player(){
	collBox = {0,0,PLAYER_WIDTH, PLAYER_HEIGHT};
	xPos = yPos = xVel = yVel = 0; 
	SpriteTex.setTexture(NULL);
	SpriteTex.setDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
}

Player::Player(std::string path, int x, int y, int vx, int vy, SDL_Renderer* Renderer){
	collBox = {x,y, PLAYER_WIDTH, PLAYER_HEIGHT};
	xPos = x;
	yPos = y;
	xVel = vx;
	yVel = vy;
	if(!SpriteTex.loadfromFile(path, Renderer))
	{
		printf( "Failed to load Player texture!\n" );
	} 
	// SpriteTex.setDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
}

void Player::handleEvent(SDL_Event& e, SDL_Renderer* Renderer){
    //If a key was pressed
    
    if ( e.type == SDL_KEYUP && e.key.repeat == 0 ){
    	//Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: yVel += PLAYER_VEL; break;
            case SDLK_DOWN: yVel -= PLAYER_VEL; break;
            case SDLK_LEFT: xVel += PLAYER_VEL; break;
            case SDLK_RIGHT: xVel -= PLAYER_VEL; break;
        }
    }
    else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity or handle the events
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: yVel -= PLAYER_VEL; break;
            case SDLK_DOWN: yVel += PLAYER_VEL; break;
            case SDLK_LEFT: xVel -= PLAYER_VEL;break;
            case SDLK_RIGHT: xVel += PLAYER_VEL; break;
            case SDLK_p:
            	cout<<"Pressed P\n";
	        	cout<<PLAYER_VEL<<endl;
	    //     	if (onYulu == false){
	    //     		PLAYER_VEL  = 7.5;
	    //     		cout<<PLAYER_VEL<<endl;
					// onYulu = true; 
					// if(!PlayerTex.loadfromFile("assets/riding.png", Renderer)){
					// 	cout<<"Could load riding picture\n";
					// }
					// PlayerTex.setDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
	    //     	}
	    //     	else{
	    //     		PLAYER_VEL = 5;
	    //     		onYulu = false;
	    //     		if(!PlayerTex.loadfromFile("assets/body.png", Renderer)){
					// 	cout<<"Could load get off yulu picture\n";
					// }
					// PlayerTex.setDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
	    //     	}
	        	break;

        }
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

void Player::setCamera(SDL_Rect &camera){
	//Center the camera over the dot
	camera.x = ( collBox.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( collBox.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 ){ 
		camera.x = 0;
	}
	if( camera.y < 0 ){
		camera.y = 0;
	}
	if( camera.x > MAP_WIDTH - camera.w )
	{
		camera.x = MAP_WIDTH - camera.w;
	}
	if( camera.y > MAP_HEIGHT - camera.h )
	{
		camera.y = MAP_HEIGHT - camera.h;
	}
}

SDL_Rect Player::getCollBox(){
	return collBox; 
}

void Player::move(Tile* roads[], vector<Coin*> &coinList, vector<Gift*> &giftList){
	//Move the dot left or right
    xPos += xVel;
    collBox.x += xVel;
    //If the dot went too far to the left or right
    if( ( xPos < 0 ) || ( xPos + PLAYER_WIDTH > MAP_WIDTH ) || touchesWall(collBox, roads)){
        //Move back
        xPos -= xVel;
        collBox.x -= xVel; 
    }
	// Move the dot up or down
    yPos += yVel;
    collBox.y += yVel;
    //If the dot went too far up or down
    if( ( yPos < 0 ) || ( yPos + PLAYER_HEIGHT > MAP_HEIGHT ) || touchesWall(collBox, roads)){
        //Move back
        yPos -= yVel;
        collBox.y -= yVel;
    }
    if(touchesCoin(collBox, coinList).first){
    	this->coins += 1;
    	cout << "Collected a coin\n";
    }
    if(touchesGift(collBox, giftList)){
    	int ind = touchesGiftIndex(collBox, giftList);
    	int val = giftList[ind]->getValue();
    	gifts += val;
    	giftList[ind]->destroy();
    	cout<<"Collected srcret item"<<" "<<val<<endl;
    }
}

void Player::render(SDL_Rect &camera, int frame, SDL_Renderer* Renderer){
	SDL_Rect clip; 
	if (dir == 0){
		clip = {frame%4 * SpriteTex.getWidth()/4, 0, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 1){
		clip = {frame%3 * SpriteTex.getWidth()/4, SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 2){
		clip = {frame%4* SpriteTex.getWidth()/4, 2*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	else if (dir == 3){
		clip = {frame%4 * SpriteTex.getWidth()/4, 3*SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	} 
	else{
		clip = {0, 0, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
	}
	SDL_Rect PlayerRect = {xPos - camera.x, yPos - camera.y,PLAYER_WIDTH, PLAYER_HEIGHT};
	// SpriteTex.setDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
	// SDL_RenderCopy( gRenderer, texture, NULL, &renderQuad);
	SDL_RenderCopy(Renderer, SpriteTex.getTexture(), &clip, &PlayerRect);
	// SpriteTex.renderSprite(xPos - camera.x, yPos - camera.y, Renderer, &clip) ;
}

int Player::getCoins(){
	return coins; 
}
