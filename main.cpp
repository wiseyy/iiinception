#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include<vector>
#include<utility>
#include "game.hpp"
#include "constants.hpp"
#include "Random.hpp"
#include "Texture.hpp"
#include "Coin.hpp"
#include "Player.hpp"
#include "TileMap.hpp"
#include "Gift.hpp"
#include <fstream>

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
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	
		// Texture t1 = Texture();
		// Texture map = Texture("assets/map.")
		Player p1 = Player("assets/player.png", 30*32 + 5 ,129*32+5, 0,0,gRenderer);
		TileMap* mazeMap = new TileMap("map/map_tiles.png", MAP_TILE_TYPES,"map/map.txt","map",MAP_PIXELS_HEIGHT/TILE_HEIGHT, MAP_PIXELS_WIDTH/TILE_WIDTH, gRenderer);
		TileMap* roadMap = new TileMap("map/road_tiles.png", ROAD_TILE_TYPES, "map/roads.txt", "road", ROAD_PIXELS_HEIGHT/TILE_HEIGHT, ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);

		// Generating road coordinates
		vector<pair<int, int>> roadCoordinates; 
		for(int i = 0; i<TOTAL_TILES; ++i){
			if ((roadMap->Map[i])->getType() != 0){
				roadCoordinates.push_back((roadMap->Map[i])->getCoordinates());
			}
		}
		// Generating coins for the map
		vector<int> coinIndices = generateRandomVectorDistinct(TOTAL_COINS, 0, roadCoordinates.size()-1);
		vector<pair<int, int>> coinCoordinates(TOTAL_COINS);
		for(int i = 0; i<TOTAL_COINS; ++i){
			coinCoordinates[i] = roadCoordinates[coinIndices[i]];
		}
		vector<Coin*> coins = generateCoins("assets/coin.png", coinCoordinates, gRenderer);

		// Generating Gifts for the map
		vector<int> giftIndices = generateRandomVectorDistinct(TOTAL_GIFTS, 0, roadCoordinates.size()-1);
		vector<pair<int, int>> giftCoordinates(TOTAL_GIFTS);
		for(int i = 0; i<TOTAL_GIFTS; ++i){
			giftCoordinates[i] = roadCoordinates[giftIndices[i]];
		}
		vector<Gift*> gifts = generateGifts("assets/box.png", giftCoordinates, gRenderer);

		cout<< roadCoordinates.size()<<endl;
		cout<<"Media Loaded\n";
		bool quit = false;
		SDL_Event e;
		int frame = 0;
		while(!quit){
			while(SDL_PollEvent(&e) != 0){
				if( e.type == SDL_QUIT ){
						quit = true;
						cout << "Now Quitting....\n"; 
				}
				p1.handleEvent(e, gRenderer);
			}
			p1.move(roadMap->Map, coins);
			p1.setCamera(camera);
			SDL_RenderClear(gRenderer);
			mazeMap->render(camera, gRenderer);
			roadMap->render(camera, gRenderer);
			renderCoins(coins, camera, gRenderer);
			renderGifts(gifts, camera, gRenderer);
			p1.render(camera, gRenderer);

			// t1.setDimensions(20,20);
			// t1.render(0,0,gRenderer);
			SDL_RenderPresent( gRenderer );

			frame++ ;
		}
		cout<<"Well Played \n"<<"You collected "<<p1.getCoins()<<endl;
	}
    return 0;
}