#pragma once

#include<iostream>
#include "SDL.h" 
#include "SDL_image.h"
#include <SDL2/SDL_mixer.h>

using namespace std;

class SoundEffect{
public:
	SoundEffect(std::string path){
		effect = Mix_LoadWAV(path.c_str());
		if(effect == NULL){
			cout <<"Failed to load sound effect! "<< path <<"SDL_mixer Error: " << Mix_GetError() << endl;
		}
	}
	void play(int i){
		Mix_PlayChannel( -1, effect, i );
	}
private:
	Mix_Chunk *effect = NULL;
};