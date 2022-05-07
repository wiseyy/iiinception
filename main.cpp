#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <vector>
#include <utility>
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
#include "Prof.hpp"
#include "Trash.hpp"
#include "client.hpp"
#include "server.hpp"

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

void loadYuluStations(vector<SDL_Rect> &yulus);

int main(int argc, char *argv[])
{
	cout << "Game Started";
	cout << "Screen Width : " << SCREEN_WIDTH << endl;
	cout << "Screen Height : " << SCREEN_HEIGHT << endl;
	cout << "MAP Width : " << MAP_WIDTH << endl;
	cout << "MAP Height : " << MAP_HEIGHT << endl;
	cout << "Total Tiles : " << TOTAL_TILES << endl;

	bool server = false;
	bool client = false;

	string what = argv[1];

	if (what.compare("s") == 0)
	{
		server = true;
		start_server();
	}
	if (what.compare("c") == 0)
	{
		client = true;
		start_client(argv[2]);
	}

	if (!init())
	{
		cout << "Could not initialize SDL\n";
	}
	else
	{

		cout << "SDL initialized successfully\n";
		SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

		// Marking the yulu stations
		vector<SDL_Rect> yulus(8);
		loadYuluStations(yulus);

		// vector<SDL_Rect> hostels();
		// Frame Rate
		Uint32 frameStart = 60;
		int frameTime;

		// loading sound effects
		unordered_map<string, SoundEffect *> soundHashMap;
		// sound effect for coin
		SoundEffect *coin = new SoundEffect("music/coin.wav");
		soundHashMap["coin"] = coin;
		// sound effect for collecting gift
		SoundEffect *gift = new SoundEffect("music/gift.wav");
		soundHashMap["gift"] = gift;

		SoundEffect *main = new SoundEffect("music/main.mp3");
		soundHashMap["main"] = main;

		SoundEffect *dog = new SoundEffect("music/dog.wav");
		soundHashMap["dog"] = dog;

		SoundEffect *yulu = new SoundEffect("music/yulu.wav");
		soundHashMap["yulu"] = yulu;

		SoundEffect *win = new SoundEffect("music/win.wav");
		soundHashMap["win"] = win;

		SoundEffect *lose = new SoundEffect("music/lose.flac");
		soundHashMap["lose"] = lose;

		SoundEffect *mission = new SoundEffect("music/mission.wav");
		soundHashMap["mission"] = mission;

		SoundEffect *angry = new SoundEffect("music/angry.wav");
		soundHashMap["angry"] = angry;

		SoundEffect *go = new SoundEffect("music/go.mp3");
		soundHashMap["go"] = go;

		SoundEffect *trash1 = new SoundEffect("music/trash.wav");
		soundHashMap["trash"] = trash1;

		SoundEffect *throwtrash = new SoundEffect("music/throw.wav");
		soundHashMap["throw"] = throwtrash;
		// Generating different layers of our tilemap
		TileMap *collisionMap = new TileMap("map/sdl_stuff/collision_tiles.png", COLL_TILE_TYPES, "map/sdl_stuff/collision.txt", "collision", COLL_PIXELS_HEIGHT / TILE_HEIGHT, COLL_PIXELS_WIDTH / TILE_WIDTH, gRenderer);
		TileMap *below_roadMap = new TileMap("map/sdl_stuff/below_road_tiles.png", BELOW_ROAD_TILE_TYPES, "map/sdl_stuff/below_road.txt", "below_road", BELOW_ROAD_PIXELS_HEIGHT / TILE_HEIGHT, BELOW_ROAD_PIXELS_WIDTH / TILE_WIDTH, gRenderer);
		TileMap *roadMap = new TileMap("map/sdl_stuff/road_tiles.png", ROAD_TILE_TYPES, "map/sdl_stuff/road.txt", "road", ROAD_PIXELS_HEIGHT / TILE_HEIGHT, ROAD_PIXELS_WIDTH / TILE_WIDTH, gRenderer);
		TileMap *above_roadMap = new TileMap("map/sdl_stuff/above_road_tiles.png", ABOVE_ROAD_TILE_TYPES, "map/sdl_stuff/above_road.txt", "above_road", ABOVE_ROAD_PIXELS_HEIGHT / TILE_HEIGHT, ABOVE_ROAD_PIXELS_WIDTH / TILE_WIDTH, gRenderer);
		TileMap *trashMap = new TileMap("map/sdl_stuff/trash_tiles.png", TRASH_TILE_TYPES, "map/sdl_stuff/trash.txt", "trash", TRASH_PIXELS_HEIGHT / TILE_HEIGHT, TRASH_PIXELS_WIDTH / TILE_WIDTH, gRenderer);

		main->play(-1);

		// Generating road coordinates
		vector<pair<int, int>> roadCoordinates;
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			if ((roadMap->Map[i])->getType() != 0)
			{
				roadCoordinates.push_back((roadMap->Map[i])->getCoordinates());
			}
		}
		Player p1 = Player("assets/boy.png", roadCoordinates[0].first, roadCoordinates[0].second, 0, 0, gRenderer);
		Player p2 = Player("assets/boy2.png", roadCoordinates[0].first, roadCoordinates[0].second, 0, 0, gRenderer);
		// Generating coins for the map
		vector<int> coinIndices = generateRandomVectorDistinct(TOTAL_COINS, 0, roadCoordinates.size() - 1);
		vector<pair<int, int>> coinCoordinates(TOTAL_COINS);
		for (int i = 0; i < TOTAL_COINS; ++i)
		{
			coinCoordinates[i] = roadCoordinates[coinIndices[i]];
		}
		vector<Coin *> coins = generateCoins("assets/coin.png", coinCoordinates, gRenderer);

		// Generating Gifts for the map
		vector<int> giftIndices = generateRandomVectorDistinct(TOTAL_GIFTS, 0, roadCoordinates.size() - 1);
		vector<pair<int, int>> giftCoordinates(TOTAL_GIFTS);
		for (int i = 0; i < TOTAL_GIFTS; ++i)
		{
			giftCoordinates[i] = roadCoordinates[giftIndices[i]];
		}
		vector<Gift *> gifts = generateGifts("assets/box.png", giftCoordinates, gRenderer);
		// Generate Angry Professors
		vector<int> profIndices = generateRandomVectorDistinct(TOTAL_PROFS, 0, roadCoordinates.size() - 1);
		vector<pair<int, int>> profCoordinates(TOTAL_PROFS);
		for (int i = 0; i < TOTAL_PROFS; ++i)
		{
			profCoordinates[i] = roadCoordinates[profIndices[i]];
		}
		vector<Prof*> profsX = generateProfsX("assets/claude.png", profCoordinates, gRenderer);
		// Generate TrashBags 
		vector<int> trashIndices = generateRandomVectorDistinct(TOTAL_TRASH, 0, roadCoordinates.size() - 1);
		vector<pair<int, int>> trashCoordinates(TOTAL_TRASH);
		for (int i = 0; i < TOTAL_TRASH; ++i)
		{
			trashCoordinates[i] = roadCoordinates[trashIndices[i]];
		}
		vector<Trash*> trash = generateTrash("assets/garbage.png", trashCoordinates, gRenderer);

		cout << roadCoordinates.size() << endl;
		cout << "Media Loaded\n";
		bool quit = false;
		SDL_Event e;
		int frame = 0;
		while (!quit)
		{

			if (server)
			{
				// string param = from_client();
				// p2.set(param);
				// string messagetoClient = p1.get();
				// const char *mess = messagetoClient.c_str();
				// to_client(mess);

				frameStart = SDL_GetTicks();

				SDL_RenderClear(gRenderer);
				collisionMap->render(camera, gRenderer);
				below_roadMap->render(camera, gRenderer);
				roadMap->render(camera, gRenderer);
				above_roadMap->render(camera, gRenderer);
				trashMap->render(camera, gRenderer);
				renderProfs(profsX, frame, camera, gRenderer);
				// renderProfs(profsY, frame, camera, gRenderer);
				renderGifts(gifts, camera, gRenderer);
				renderCoins(coins, camera, gRenderer);
				renderTrash(trash, camera, gRenderer);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
						cout << "Now Quitting....\n";
					}
					p1.handleEvent(e, yulus, trashMap->Map, soundHashMap, gRenderer);
				}
				p1.move(roadMap->Map, coins, gifts, profsX,trash, soundHashMap, gRenderer);
				moveProfs(profsX, roadMap->Map, gRenderer);
				moveProfs(profsX, roadMap->Map, gRenderer);
				p1.setCamera(camera);
				
				
				p1.render(camera, frame % 6, gRenderer);
				p2.renderCam(camera, frame%6, gRenderer);
				// t1.setDimensions(20,20);
				// t1.render(0,0,gRenderer);
				SDL_RenderPresent(gRenderer);

				// reset angry attribute of profs after some frames
				if (frame % 600 == 0)
				{
					for (auto prof : profsX)
					{
						prof->setAnger(getRandomInt(5, 30));
					}
				}
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
				frame++;
			}
			else if (client)
			{
				// 		// string messagetoServer = p2.get();
				// 		// const char *mess = messagetoServer.c_str();
				// 		// to_server(mess);
				// 		// string param = from_server();
				// 		// p2.set(param);

				frameStart = SDL_GetTicks();
				SDL_RenderClear(gRenderer);
				collisionMap->render(camera, gRenderer);
				below_roadMap->render(camera, gRenderer);
				roadMap->render(camera, gRenderer);
				above_roadMap->render(camera, gRenderer);
				trashMap->render(camera, gRenderer);
				renderProfs(profsX, frame, camera, gRenderer);
				// renderProfs(profsY, frame, camera, gRenderer);
				renderGifts(gifts, camera, gRenderer);
				renderCoins(coins, camera, gRenderer);
				renderTrash(trash, camera, gRenderer);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
						cout << "Now Quitting....\n";
					}
					p2.handleEvent(e, yulus,trashMap->Map,soundHashMap,  gRenderer);
				}
				p2.move(roadMap->Map, coins, gifts, profsX,trash, soundHashMap, gRenderer);
				moveProfs(profsX, roadMap->Map, gRenderer);
				moveProfs(profsX, roadMap->Map, gRenderer);
				p2.setCamera(camera);
				
				p2.render(camera, frame % 6, gRenderer);
				p1.renderCam(camera, frame%6, gRenderer);
				// t1.setDimensions(20,20);
				// t1.render(0,0,gRenderer);
				SDL_RenderPresent(gRenderer);

				// reset angry attribute of profs after some frames
				if (frame % 600 == 0)
				{
					for (auto prof : profsX)
					{
						prof->setAnger(getRandomInt(5, 30));
					}
				}
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
				frame++;
			}
		}
	}
}

void loadYuluStations(vector<SDL_Rect> &yulus)
{
	yulus[0] = yulu1;
	yulus[1] = yulu2;
	yulus[2] = yulu3;
	yulus[3] = yulu4;
	yulus[4] = yulu5;
	yulus[5] = yulu6;
	yulus[6] = yulu7;
	yulus[7] = yulu8;
}

void loadAllHostels(vector<SDL_Rect> &hostels, unordered_map<string, SDL_Rect> &loc)
{
	hostels[0] = loc["Girnar"];
	hostels[1] = loc["Satpura"];
	hostels[2] = loc["Himadri"];
	hostels[3] = loc["Kailash"];
	hostels[4] = loc["Jwalamukhi"];
	hostels[5] = loc["Jwalamukhi1"];
	hostels[6] = loc["Vindy"];
	hostels[7] = loc["Zanskar"];
	hostels[8] = loc["Shivalik"];
	hostels[9] = loc["Kumaon"];
	hostels[10] = loc["Nalanda"];
	hostels[11] = loc["Karakoram"];
	hostels[12] = loc["Karakoram1"];
	hostels[13] = loc["Aravali"];
	hostels[14] = loc["Aravali1"];
	hostels[15] = loc["Aravali2"];
	hostels[16] = loc["Udaigiri"];
	hostels[17] = loc["Nilgiri"];
}

void loadAllEatingPoints(vector<SDL_Rect> &eatingPoints, unordered_map<string, SDL_Rect> &loc)
{
	eatingPoints[0] = loc["Holistic"];
	eatingPoints[1] = loc["Delhi16"];
	eatingPoints[2] = loc["Kumaon Mess"];
	eatingPoints[3] = loc["Zanskar Mess"];
	eatingPoints[4] = loc["Satpura Night Mess"];
	eatingPoints[5] = loc["Masalamix"];
	eatingPoints[6] = loc["Chaayos"];
	eatingPoints[7] = loc["Rajdhani"];
	eatingPoints[8] = loc["Volley"];
	eatingPoints[9] = loc["Shiru Cafe"];
	eatingPoints[10] = loc["Amul"];
	eatingPoints[11] = loc["Nescafe"];
	eatingPoints[12] = loc["Himadri Night Mess"];
}

void makeLocationHashMap(unordered_map<string, SDL_Rect> &loc)
{
	loc["YuluStand1"] = yulu1;
	loc["YuluStand2"] = yulu2;
	loc["YuluStand3"] = yulu3;
	loc["YuluStand4"] = yulu4;
	loc["YuluStand5"] = yulu5;
	loc["YuluStand6"] = yulu6;
	loc["YuluStand7"] = yulu7;
	loc["YuluStand8"] = yulu8;
	loc["Satpura"] = satpura;
	loc["Girnar"] = girnar;
	loc["Himadri"] = himadri;
	loc["Kailash"] = kailash;
	loc["Jwalamukhi"] = jwala;
	loc["Jwalamukhi1"] = jwala1;
	loc["Vindy"] = vindy;
	loc["Zanskar"] = zanskar;
	loc["Shivalik"] = shivalik;
	loc["Kumaon"] = kumaon;
	loc["Nalanda"] = nalanda;
	loc["Karakoram"] = kara;
	loc["Karakoram1"] = kara1;
	loc["Aravali"] = ara;
	loc["Aravali1"] = ara1;
	loc["Aravali2"] = ara2;
	loc["Udaigiri"] = udai;
	loc["Nilgiri"] = nil;
	loc["SAC"] = sac;
	loc["Gate1"] = gate1;
	loc["Gate3"] = gate3;
	loc["Gate6"] = gate6;
	loc["Pantonic"] = pantonic;
	loc["Holistic"] = holistic;
	loc["Bharti"] = bharti;
	loc["SIT"] = sit;
	loc["Delhi16"] = delhi16;
	loc["Kumaon Mess"] = kumaonmess;
	loc["Zanskar Mess"] = zanskarmess;
	loc["Atm1"] = atm1;
	loc["Atm2"] = atm2;
	loc["Atm3"] = atm3;
	loc["Atm4"] = atm4;
	loc["Atm5"] = atm5;
	loc["Atm6"] = atm6;
	loc["Satpura Night Mess"] = snm;
	loc["Masalamix"] = masalamix;
	loc["Chaayos"] = chaayos;
	loc["Rajdhani"] = rajdhani;
	loc["Volley"] = volley;
	loc["Cricket"] = cricket;
	loc["Hockey"] = hockey;
	loc["Football"] = football;
	loc["Apollo"] = apollo;
	loc["Hospital"] = hospital;
	loc["Scoops"] = scoops;
	loc["Shiru Cafe"] = shiru;
	loc["Library"] = library;
	loc["LHC"] = lhc;
	loc["Amul"] = amul;
	loc["Nescafe"] = nescafe;
	loc["Main Building"] = mainbuilding;
	loc["Himadri Night Mess"] = hnm;
	loc["Tennis"] = tennis;
	loc["Research"] = research;
	loc["Prof_House"] = prof_house;
}
