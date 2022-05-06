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
		
		// Frame Rate 
		Uint32 frameStart = 60; 
		int frameTime; 
		// Generating different layers of our tilemap
		TileMap* collisionMap = new TileMap("map/sdl_stuff/collision_tiles.png", COLL_TILE_TYPES,"map/sdl_stuff/collision.txt","collision",COLL_PIXELS_HEIGHT/TILE_HEIGHT, COLL_PIXELS_WIDTH/TILE_WIDTH, gRenderer);
		TileMap* below_roadMap = new TileMap("map/sdl_stuff/below_road_tiles.png", BELOW_ROAD_TILE_TYPES, "map/sdl_stuff/below_road.txt", "below_road", BELOW_ROAD_PIXELS_HEIGHT/TILE_HEIGHT, BELOW_ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* roadMap = new TileMap("map/sdl_stuff/road_tiles.png", ROAD_TILE_TYPES, "map/sdl_stuff/road.txt", "road", ROAD_PIXELS_HEIGHT/TILE_HEIGHT, ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* above_roadMap = new TileMap("map/sdl_stuff/above_road_tiles.png", ABOVE_ROAD_TILE_TYPES, "map/sdl_stuff/above_road.txt", "above_road", ABOVE_ROAD_PIXELS_HEIGHT/TILE_HEIGHT, ABOVE_ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* trashMap = new TileMap("map/sdl_stuff/trash_tiles.png",TRASH_TILE_TYPES,"map/sdl_stuff/trash.txt","trash",TRASH_PIXELS_HEIGHT/TILE_HEIGHT, TRASH_PIXELS_WIDTH/TILE_WIDTH, gRenderer );
		
		// Generating road coordinates
		vector<pair<int, int>> roadCoordinates; 
		for(int i = 0; i<TOTAL_TILES; ++i){
			if ((roadMap->Map[i])->getType() != 0){
				roadCoordinates.push_back((roadMap->Map[i])->getCoordinates());
			}
		}
		// generating player on the road
		Player p1 = Player("assets/boy.png", roadCoordinates[0].first ,roadCoordinates[0].second, 0,0,gRenderer);
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
			frameStart = SDL_GetTicks();

			while(SDL_PollEvent(&e) != 0){
				if( e.type == SDL_QUIT ){
						quit = true;
						cout << "Now Quitting....\n"; 
				}
				p1.handleEvent(e, gRenderer);
			}
			p1.move(roadMap->Map, coins, gifts);
			p1.setCamera(camera);
			SDL_RenderClear(gRenderer);
			collisionMap->render(camera, gRenderer);
			below_roadMap->render(camera, gRenderer);
			roadMap->render(camera, gRenderer);
			above_roadMap->render(camera, gRenderer);
			trashMap->render(camera, gRenderer);
			renderCoins(coins, camera, gRenderer);
			renderGifts(gifts, camera, gRenderer);
			p1.render(camera, frame%6, gRenderer);
			
			

			// t1.setDimensions(20,20);
			// t1.render(0,0,gRenderer);
			SDL_RenderPresent( gRenderer );

			frameTime = SDL_GetTicks() - frameStart;
			if(frameDelay > frameTime){
				SDL_Delay(frameDelay - frameTime);
			}
			frame++;
		}
		cout<<"Well Played \n"<<"You collected "<<p1.getCoins()<<endl;
	}
    return 0;
}