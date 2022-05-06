#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include<vector>
#include<utility>
#include "game.hpp"
#include "constants.hpp"
#include "Random.hpp"
#include "Texture.hpp"
using namespace std;

int main() {
    cout << "Game Started";
    cout<< "Screen Width : "<< SCREEN_WIDTH <<endl;
	cout<< "Screen Height : "<< SCREEN_HEIGHT <<endl;
	cout<< "MAP Width : "<< MAP_WIDTH <<endl;
	cout<< "MAP Height : "<< MAP_HEIGHT <<endl;
	cout<<"Total Tiles : "<< TOTAL_TILES<<endl;
	if (!init()){
		cout << "Could not initialize SDL\n";
	}
	else{
		cout << "SDL initialized successfully\n";
		Texture t1 = Texture();
		bool x = t1.loadfromFile("map/b1.png", gRenderer);
		cout<<"Media Loaded\n";
		bool quit = false;
		SDL_Event e;
		while(!quit){
			while(SDL_PollEvent(&e) != 0){
				if( e.type == SDL_QUIT ){
						quit = true;
						cout << "Now Quitting....\n"; 
				}
			}
			t1.setDimensions(20,20);
			t1.render(0,0,gRenderer);
			SDL_RenderPresent( gRenderer );
		}
	}
    return 0;
}