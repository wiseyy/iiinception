#pragma once 

#include<iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <utility>
#include<string>
#include<vector>
#include "constants.hpp"
#include "Texture.hpp"
#include "Collisions.hpp"
#include "SoundEffect.hpp"
#include <unordered_map>
#include "Prof.hpp"
#include "Trash.hpp"
#include "game.hpp"
class Player{
	public: 
	// Dimensions of the player 
	static const int PLAYER_WIDTH = 25;
	static const int PLAYER_HEIGHT = 25;

	int PLAYER_VEL = 10;
	// Constructors for the Player
	Player(); 
	// Score heuristic
	int getScore(){
		return 30*thrown + coins + 3*happiness + 2*health + uid(1, 3)*gifts - 2*trash;
	}
	Player(std::string path, int x, int y, int vx, int vy, SDL_Renderer* Renderer);
	// Handle the user input from keyboard or mouse
	void handleEvent (SDL_Event &e, vector<SDL_Rect> &YuluLoc, vector<SDL_Rect> &hostels, vector<SDL_Rect> &eatingPoints, Tile* trashTiles[],unordered_map<string, SoundEffect*> sounds, SDL_Renderer* Renderer);
	// move player in each game loop
	void move(Tile* roads[], vector<Coin*> &coinList, vector<Gift*> &giftList,vector<Prof*> &profListX, vector<Trash*> &trashList, unordered_map<string, SoundEffect*> &sounds, SDL_Renderer* Renderer);
	// render the player according to the camera
	void render(SDL_Rect &camera, int frame, SDL_Renderer* Renderer); 
	// set the camera according to the player
	void setCamera( SDL_Rect& camera );
	// get the collBox for the player
	SDL_Rect getCollBox();
	void getOnYulu(SDL_Renderer* Renderer);
	void getOffYulu(SDL_Renderer* Renderer);
	int getCoins();
	string eatFood();
	string visitHostel();
	string get();
	void set(string param);
	pair<int, int> getCoordinates(){
		return {xPos, yPos};
	}
	int getGifts(){
		return gifts ;
	}
	int getHappiness(){
		return happiness;
	}
	void setHappiness(int x){
		happiness = x;
	}
	void renderCam(SDL_Rect &camera, int frame,  SDL_Renderer* Renderer);
	// vector<SecretItem*> getItemList();
	bool onYulu = false;
	int dir = 0;    //  0 for right , 1 for down , 2 for left , 3 for up 
	int yuluTimer = 0;
<<<<<<< HEAD
	bool visitedHostel = false;
	int status = 1;
=======
>>>>>>> hemank
	Texture display(SDL_Renderer* Renderer)
	{
		Texture result;
		string val = "";
		val += "Coins :" + to_string(coins) + " " + "Trash Thrown :" + to_string(thrown) + " ";
		val += "Current Trash :" + to_string(trash) + " Happiness : " + to_string(happiness) + " Health : " + to_string(health) + " Gift Boxes = " + to_string(gifts);
		gFont = TTF_OpenFont("font/game-font.ttf",28);
		SDL_Color textColor = {255,0,0};
		if( gFont == NULL )
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
			return result;
		}
		else
		{
			//Render text surface
			SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, val.c_str(), textColor );
			if( textSurface == NULL )
			{
				printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
				return result;
			}
			else
			{
				SDL_Texture* display = SDL_CreateTextureFromSurface(Renderer,textSurface);
				result.setTexture(display);
				result.setDimensions(textSurface->w,textSurface->h);
				SDL_FreeSurface(textSurface);
				//global font
				TTF_CloseFont( gFont );
				gFont = NULL;
				return result;
			}
		}
	}

	Texture displayEvent(std::string event, SDL_Renderer* Renderer){
		Texture result;
		string val = event ;
		gFont = TTF_OpenFont("font/game-font.ttf",28);
		SDL_Color textColor = {255,0,0};
		if( gFont == NULL )
		{
			printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
			return result;
		}
		else
		{
			//Render text surface
			SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, val.c_str(), textColor );
			if( textSurface == NULL )
			{
				printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
				return result;
			}
			else
			{
				SDL_Texture* display = SDL_CreateTextureFromSurface(Renderer,textSurface);
				result.setTexture(display);
				result.setDimensions(textSurface->w,textSurface->h);
				SDL_FreeSurface(textSurface);
				//global font
				TTF_CloseFont( gFont );
				gFont = NULL;
				return result;
			}
		}
	}
	// extra features
	bool visitedHostel = false;
	bool ateFood = false;
	int coins = 100; 
	int health = 100;
	int gifts = 0;
	int happiness  = 100;
	int trash = 0;
	int thrown = 0;
	int study = 50;
	int hunger = 100;
private:
	// Position of the player
	int xPos, yPos;
	// Velocity of the player
	int xVel, yVel;
	// Texture attribute for rendering
	Texture SpriteTex;
	// Collision Box for the player
	SDL_Rect collBox;
	
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
void Player::renderCam(SDL_Rect &camera,int frame,  SDL_Renderer* Renderer){
	SDL_Rect clip;
	// If Player not on yulu 
	if(!onYulu){
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
	}
	// If player on Yulu 
	else{
		if (dir == 0){
			clip = {frame%4 * SpriteTex.getWidth()/4, 0, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
		}
		else if (dir == 2){
			clip = {frame%4 * SpriteTex.getWidth()/4, SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
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
	}
	SDL_Rect PlayerRect = {xPos - camera.x, yPos - camera.y,PLAYER_WIDTH, PLAYER_HEIGHT};
	
	if (xPos >= camera.x && xPos <= camera.x + camera.w && yPos >= camera.y && yPos <= camera.y + camera.h)
		SDL_RenderCopy(Renderer, SpriteTex.getTexture(), &clip, &PlayerRect);
}
void Player::handleEvent(SDL_Event& e, vector<SDL_Rect> &YuluLoc, vector<SDL_Rect> &hostels, vector<SDL_Rect> &eatingPoints, Tile* trashTiles[], unordered_map<string, SoundEffect*> sounds,   SDL_Renderer* Renderer){
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
            
        }
    }


    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
    	switch(e.key.keysym.sym){
    		case SDLK_RETURN:
    		{
            	bool onStation = false ;
            	// check if player is on yulu station
            	for(auto yulu : YuluLoc){
            		if(checkCollision(collBox, yulu)){
            			onStation = true; 
            		}

            	}
	        	cout<<PLAYER_VEL<<endl;
	        	// at the station and not having yulu
	        	if(!onYulu && onStation){
	        		getOnYulu(Renderer);
	        		string ev =  "Yulu Picked";
	        		eventHappened = ev ;
	        	}
	        	else if (onYulu){
	        		string ev =  "Yulu Dropped";
	       			eventHappened = ev;
	        		getOffYulu(Renderer);
	        	}
	        	break;
	        }
	       	case SDLK_p :
	       		xVel = 0;
	       		yVel = 0;
	       		break;
	       	case SDLK_t:
	       	{
	       		bool onTrashCan = false ;
	       		// check if player touches any trash can
	       		SDL_Rect obj = {collBox.x - 10, collBox.y - 10, collBox.w + 20, collBox.h + 20};
	       		onTrashCan = touchesTrashCan(obj, trashTiles);
	       		if(trash > 0 && trash <= 10 && onTrashCan){
	       			thrown += trash ;
	       			trash = 0;
					coins += 10 ;
	       			string ev =  "Trash Thrown \n";
	       			eventHappened = ev; 
	       			sounds["throw"]->play(0);
	       		}
	       		else{
	       			string ev = "Collect some garbage to throw in the trash can\n";
	       			eventHappened = ev ;
	       		}
	       		break ;
	       	}
	       	case SDLK_v :
	       	{
	       		string ev = visitHostel();
	       		eventHappened = ev;
	       		break ;
	       	}
	       	case SDLK_e :
	       	{
	       		string ev = eatFood() ;
	       		eventHappened = ev; 
	       		break ;
	       	}
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

void Player::move(Tile* roads[], vector<Coin*> &coinList, vector<Gift*> &giftList, vector<Prof*> &profListX, vector<Trash*> &trashList,  unordered_map<string, SoundEffect*> &sounds, SDL_Renderer* Renderer){
	// yulu Timer checks if player needs to get off yulu
    if (onYulu){
    	if(yuluTimer < 600){
    		yuluTimer += 1;
    		sounds["yulu"]->play(0);
    		// cout<<yuluTimer<<endl;
    	}
    	else{ 
    		yuluTimer = 0;
    		getOffYulu(Renderer);
    	}
    }

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
    	string ev =  "Collected a coin";
    	eventHappened = ev;
    	sounds["coin"]->play(0);
    }
    if(touchesGift(collBox, giftList)){
    	int ind = touchesGiftIndex(collBox, giftList);
    	int val = giftList[ind]->getValue();
    	gifts += val;
    	giftList[ind]->destroy();
    	string ev = "Collected srcret item";
    	eventHappened = ev;
    	sounds["gift"]->play(0);
    }
    if(touchesProf(collBox, profListX)){
    	int ind = touchesProfIndex(collBox, profListX);
    	int anger = profListX[ind]->getAnger();
    	profListX[ind]->setAnger(0);
    	happiness -= anger ;
    	string ev = "Collided with an angry prof";
    	eventHappened = ev;
    	sounds["angry"]->play(0);
    }
    if (touchesTrash(collBox, trashList)){
    	if(trash < 10){
    		int ind = touchesTrashIndex(collBox, trashList);
    		trash++; 
    		trashList[ind]->destroy();
    		string ev =  "Collected Trash Item";
    		eventHappened = ev;
    		sounds["trash"]->play(0);
    	}
    	else{
    		string ev =  "Cannot pick more trash... Throw some in trash cans";
    		eventHappened = ev;
    	}
    }
}

void Player::render(SDL_Rect &camera, int frame, SDL_Renderer* Renderer){
	SDL_Rect clip;
	// If Player not on yulu 
	if(!onYulu){
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
	}
	// If player on Yulu 
	else{
		if (dir == 0){
			clip = {frame%4 * SpriteTex.getWidth()/4, 0, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
		}
		else if (dir == 2){
			clip = {frame%4 * SpriteTex.getWidth()/4, SpriteTex.getHeight()/4, SpriteTex.getWidth()/4, SpriteTex.getHeight()/4};
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
	}
	SDL_Rect PlayerRect = {xPos - camera.x, yPos - camera.y,PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(Renderer, SpriteTex.getTexture(), &clip, &PlayerRect);
}

int Player::getCoins(){
	return coins; 
}

void Player::getOffYulu(SDL_Renderer* Renderer){
	if(onYulu){
		onYulu = false;
		PLAYER_VEL = 5;
		if(!SpriteTex.loadfromFile("assets/boy.png", Renderer)){
			cout<<"Could load get on yulu picture\n";
		}
	}
}

void Player::getOnYulu(SDL_Renderer* Renderer){
	if(!onYulu){
		onYulu = true;
		coins -= 10;
		PLAYER_VEL += 10;
		if(!SpriteTex.loadfromFile("assets/yulub.png", Renderer)){
			cout<<"Could load get off yulu picture\n";
		}
	}
	happiness += 5; 
	if(happiness > 100){
		happiness = 100 ;
	}
}
string Player::get(){
	vector<int> ch = {onYulu?1:0, dir, yuluTimer, xPos, yPos, xVel, yVel, coins, health, gifts, happiness, trash, thrown, study, visitedHostel?1:0, hunger};
	
	string ret = "";
	for(int i = 0; i<ch.size(); i++){
		ret += to_string(ch[i])+"_";
	}
	return ret;
}

string Player::eatFood(){
	if(!ateFood){
		if(coins > 10){
			ateFood = false;
			happiness += 10; 
			health += 10;
			return "Ate very delicious food";
		}
		return "Not enough Coins";
	}
	return "Just ate food";
}

string Player::visitHostel(){
	if(!visitedHostel){
		visitedHostel = true;
		happiness += 10; 
		health += 10;
		coins += 5;
		return "Visited Hostel";
	}
	return "Visited the hostel just a moment ago";
}
void Player::set(string param){
	int iter = 0;
	int prev = 0;
	for(int i=0; i<param.size();i++){
		if(param[i]=='_'){
			string curr = param.substr(prev, i-prev);
			int now = stoi(curr);
			prev = i+1;
			if(iter == 0){
				onYulu = (now == 1);
				iter++;
			}
			else if(iter == 1){
				dir = now;
				iter++;
			}
			else if(iter == 2){
				yuluTimer = now;
				iter++;
			}
			else if(iter == 3){
				xPos = now;
				iter++;
			}
			else if(iter == 4){
				yPos = now;
				iter++;
			}
			else if(iter == 5){
				xVel = now;
				iter++;
			}
			else if(iter == 6){
				yVel = now;
				iter++;
			}
			else if(iter == 7){
				coins = now;
				iter++;
			}
			else if(iter == 8){
				health = now;
				iter++;
			}
			else if(iter == 9){
				gifts = now;
				iter++;
			}
			else if(iter == 10){
				happiness = now;
				iter++;
			}
			else if(iter == 11){
				trash = now;
				iter++;
			}
			else if(iter == 12){
				thrown = now;
				iter++;
			}
			else if(iter == 13){
				study = now;
				iter++;
			}
			else if(iter == 14){
				visitedHostel = (now == 1);
				iter++;
			}
			else if(iter == 15){
				hunger = now;
				iter++;
			}
		}
	}

}
