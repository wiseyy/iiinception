#pragma once

//Screen dimensions
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 960;

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
const int PROF_WIDTH = 30;
const int PROF_HEIGHT = 30;
