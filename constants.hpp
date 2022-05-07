#pragma once

#include<iostream>
#include<utility>

using namespace std;
// frame Rate 
const int FPS = 60;
const int frameDelay = 1000/FPS ;

//Screen dimensions
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 960;

const int MAX_PLAYERS = 2;
const int TAB = 1;
const int BUF_MAX = 256;

const int SERVER_PORT = 6666;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int numCols = 380;
const int numRows = 170; 

// Field Dimensions
const int MAP_WIDTH = TILE_WIDTH*numCols;
const int MAP_HEIGHT = TILE_HEIGHT*numRows;

const int TOTAL_TILES = MAP_WIDTH/TILE_WIDTH* MAP_HEIGHT/TILE_HEIGHT ;


const int COLL_PIXELS_HEIGHT = 32;
const int COLL_PIXELS_WIDTH = 64;
const int COLL_TILE_TYPES = COLL_PIXELS_HEIGHT/32 * COLL_PIXELS_WIDTH/32;

const int BELOW_ROAD_PIXELS_WIDTH = 1216;
const int BELOW_ROAD_PIXELS_HEIGHT = 1184; 
const int BELOW_ROAD_TILE_TYPES = BELOW_ROAD_PIXELS_HEIGHT/32 * BELOW_ROAD_PIXELS_WIDTH/32;

const int ROAD_PIXELS_WIDTH = 384;
const int ROAD_PIXELS_HEIGHT = 352; 
const int ROAD_TILE_TYPES = ROAD_PIXELS_HEIGHT/32 * ROAD_PIXELS_WIDTH/32;

const int ABOVE_ROAD_PIXELS_WIDTH = 2528;
const int ABOVE_ROAD_PIXELS_HEIGHT = 2464; 
const int ABOVE_ROAD_TILE_TYPES = ABOVE_ROAD_PIXELS_HEIGHT/32 * ABOVE_ROAD_PIXELS_WIDTH/32;

const int TRASH_PIXELS_HEIGHT = 64;
const int TRASH_PIXELS_WIDTH = 96;
const int TRASH_TILE_TYPES = TRASH_PIXELS_HEIGHT/32 * TRASH_PIXELS_WIDTH/32;


// Coin Dimensions 
const int COIN_WIDTH = 25;
const int COIN_HEIGHT = 25; 

const int TOTAL_COINS = 300; 

// Gift Dimensions
const int GIFT_WIDTH = 25;
const int GIFT_HEIGHT = 25;

const int TOTAL_GIFTS = 50;

// Prof Dimensions
const int PROF_WIDTH = 40;
const int PROF_HEIGHT = 40;

const int TOTAL_PROFS = 10;

const int PROF_SPEED = 1;

// Location offset
const int LOC_OFFSET = 200;

// YULU Locations
SDL_Rect yulu1 = {1695, 506, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu2 = {1529, 3381, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu3 = {5320, 3053, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu4 = {5947, 3044, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu5 = {5570, 1664, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu6 = {10269, 751, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu7 = {8475, 2657, LOC_OFFSET, LOC_OFFSET};
SDL_Rect yulu8 = {7704, 2689, LOC_OFFSET, LOC_OFFSET};

// Hostel Locations
SDL_Rect satpura = {5372, 941, LOC_OFFSET, LOC_OFFSET};
SDL_Rect girnar= {5876, 1629, LOC_OFFSET, LOC_OFFSET};
SDL_Rect himadri= {10778, 1284, LOC_OFFSET, LOC_OFFSET};
SDL_Rect kailash= {9981, 1697, LOC_OFFSET, LOC_OFFSET};
SDL_Rect kailash1= {10462, 503, LOC_OFFSET, LOC_OFFSET};
SDL_Rect jwala= {665, 969, LOC_OFFSET, LOC_OFFSET};
SDL_Rect jwala1= {1041, 969, LOC_OFFSET, LOC_OFFSET};
SDL_Rect vindy = {4000, 777, LOC_OFFSET, LOC_OFFSET};
SDL_Rect zanskar = {4272, 2177, LOC_OFFSET, LOC_OFFSET};
SDL_Rect shivalik = {3600, 1758, LOC_OFFSET, LOC_OFFSET};
SDL_Rect nalanda = {2086, 4307, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  kara = {1423, 2734, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  kara1 = {1047, 2794, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  kara2 = {653, 2799, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  ara = {1373,1742 , LOC_OFFSET, LOC_OFFSET};
SDL_Rect  ara1 = {1067, 1791, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  ara2 = {678, 1797, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  udai = {6500, 500, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  nil= {1440, 3503, LOC_OFFSET, LOC_OFFSET};


// ATM Locations
SDL_Rect  atm1 = {4042, 2175, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  atm2 = {7783, 2970, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  atm3 = {7932, 2519, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  atm4 = {8859, 2708, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  atm5 = {8996, 2405, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  atm6 = {2364, 3766, LOC_OFFSET, LOC_OFFSET};

// gate Locations
SDL_Rect gate1 ={10328, 412, LOC_OFFSET, LOC_OFFSET};
SDL_Rect gate3 = {416,4142, LOC_OFFSET, LOC_OFFSET};
SDL_Rect gate6 = {1700 ,450, LOC_OFFSET, LOC_OFFSET};

// Eating Locations 
SDL_Rect  snm = {5728 , 1664, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  zanskarmess= { 4900, 2276, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  kumaonmess= {2400 , 866, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  delhi16 = { 1735, 1593, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  masalamix= { 5121, 2493, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  chaayos= { 5248, 2641, LOC_OFFSET, LOC_OFFSET};
SDL_Rect rajdhani = { 4800,3000 , LOC_OFFSET, LOC_OFFSET};
SDL_Rect shiru = { 7877, 2605, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  holistic = { 832, 2017, LOC_OFFSET, LOC_OFFSET};

// Sports Locations
SDL_Rect volley = { 3085, 1732, LOC_OFFSET, LOC_OFFSET};
SDL_Rect cricket = {6942 , 3199, LOC_OFFSET, LOC_OFFSET};
SDL_Rect hockey = { 7880, 3130, LOC_OFFSET, LOC_OFFSET};
SDL_Rect football = { 5650, 3344, LOC_OFFSET, LOC_OFFSET};

// Acad buildings
SDL_Rect sac = {3000,3744 , LOC_OFFSET, LOC_OFFSET};
SDL_Rect  pantonic = { 1500, 1440, LOC_OFFSET, LOC_OFFSET};
SDL_Rect  bharti = { 7000, 2949, LOC_OFFSET, LOC_OFFSET};
SDL_Rect sit = {6505 ,2694 , LOC_OFFSET, LOC_OFFSET};
SDL_Rect lhc = { 9336,3277 , LOC_OFFSET, LOC_OFFSET};
SDL_Rect lhc1 = { 9646,3100 , LOC_OFFSET, LOC_OFFSET};


// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = {, , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
// SDL_Rect  = { , , LOC_OFFSET, LOC_OFFSET};
