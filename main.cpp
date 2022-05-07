#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
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
#include <unordered_map>

// #include "network.hpp"
// #include "client.hpp"
// #include "server.hpp"


using namespace std;

Player players[MAX_PLAYERS];
int number_of_players = 0;
int16_t my_id = -1;

// void init_players() {
//     int i;
//     for (i = 0; i < MAX_PLAYERS; i++) {
// 		players[i] = Player("assets/boy.png", roadCoordinates[0].first ,roadCoordinates[0].second, 0,0,gRenderer);
//     }
// }

// void receive_new_id(int id) {
//     my_id = id;
//     number_of_players = id;
//     printf("my_id is now: %d\n", my_id);
// }

// void check_if_its_new_player(int id){
//     if (id > number_of_players) {
//         number_of_players = id;
//         printf("new max player, now %d\n", number_of_players + 1);
//     }
// }

// void* client_loop(void *arg) {
//     int socket = *((int *) arg);
//     int16_t tab[BUF_MAX];
//     int length;
//     int id
//     while (1) {
//         length = client_listen(socket, tab);
//         id = tab[0];
//         if (id == -1) {
//             receive_new_id(tab[1]);
//         }
//         if (id >= 0) {
//             check_if_its_new_player(id);
            
//         }
//         usleep(50);
//     }
// }

int main(int argc, char* argv[]) {
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

		// loading sound effects 
		unordered_map <string, SoundEffect* > soundHashMap; 
		// sound effect for coin
		SoundEffect* coin = new SoundEffect("music/coin.wav");
		soundHashMap["coin"] = coin;
		// sound effect for collecting gift
		SoundEffect* gift = new SoundEffect("music/gift.wav");
		soundHashMap["gift"] = gift;

		SoundEffect* main = new SoundEffect("music/main.mp3");
		soundHashMap["main"] = main;

		SoundEffect* dog = new SoundEffect("music/dog.wav");
		soundHashMap["dog"] = dog;

		SoundEffect* yulu = new SoundEffect("music/yulu.wav");
		soundHashMap["yulu"] = yulu;

		SoundEffect* win = new SoundEffect("music/win.wav");
		soundHashMap["win"] = win;

		SoundEffect* lose = new SoundEffect("music/lose.flac");
		soundHashMap["lose"] = lose;

		SoundEffect* mission = new SoundEffect("music/mission.wav");
		soundHashMap["mission"] = mission;

		SoundEffect* angry = new SoundEffect("music/angry.wav");
		soundHashMap["angry"] = angry;

		SoundEffect* go = new SoundEffect("music/go.mp3");
		soundHashMap["go"] = go;

		// Generating different layers of our tilemap
		TileMap* collisionMap = new TileMap("map/sdl_stuff/collision_tiles.png", COLL_TILE_TYPES,"map/sdl_stuff/collision.txt","collision",COLL_PIXELS_HEIGHT/TILE_HEIGHT, COLL_PIXELS_WIDTH/TILE_WIDTH, gRenderer);
		TileMap* below_roadMap = new TileMap("map/sdl_stuff/below_road_tiles.png", BELOW_ROAD_TILE_TYPES, "map/sdl_stuff/below_road.txt", "below_road", BELOW_ROAD_PIXELS_HEIGHT/TILE_HEIGHT, BELOW_ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* roadMap = new TileMap("map/sdl_stuff/road_tiles.png", ROAD_TILE_TYPES, "map/sdl_stuff/road.txt", "road", ROAD_PIXELS_HEIGHT/TILE_HEIGHT, ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* above_roadMap = new TileMap("map/sdl_stuff/above_road_tiles.png", ABOVE_ROAD_TILE_TYPES, "map/sdl_stuff/above_road.txt", "above_road", ABOVE_ROAD_PIXELS_HEIGHT/TILE_HEIGHT, ABOVE_ROAD_PIXELS_WIDTH/TILE_WIDTH,gRenderer);
		TileMap* trashMap = new TileMap("map/sdl_stuff/trash_tiles.png",TRASH_TILE_TYPES,"map/sdl_stuff/trash.txt","trash",TRASH_PIXELS_HEIGHT/TILE_HEIGHT, TRASH_PIXELS_WIDTH/TILE_WIDTH, gRenderer );
		
		main->play(-1);

		// Generating road coordinates
		vector<pair<int, int>> roadCoordinates; 
		for(int i = 0; i<TOTAL_TILES; ++i){
			if ((roadMap->Map[i])->getType() != 0){
				roadCoordinates.push_back((roadMap->Map[i])->getCoordinates());
			}
		}
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
			p1.move(roadMap->Map, coins, gifts, soundHashMap, gRenderer);
			p1.setCamera(camera);
			SDL_RenderClear(gRenderer);
			collisionMap->render(camera, gRenderer);
			below_roadMap->render(camera, gRenderer);
			roadMap->render(camera, gRenderer);
			above_roadMap->render(camera, gRenderer);
			trashMap->render(camera, gRenderer);
			
			renderGifts(gifts, camera, gRenderer);
			renderCoins(coins, camera, gRenderer);
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