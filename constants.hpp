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


const int MAP_PIXELS_HEIGHT = 2624;
const int MAP_PIXELS_WIDTH = 2688;
const int MAP_TILE_TYPES = MAP_PIXELS_HEIGHT/32 * MAP_PIXELS_WIDTH/32;

const int ROAD_PIXELS_WIDTH = 384;
const int ROAD_PIXELS_HEIGHT = 352; 
const int ROAD_TILE_TYPES = ROAD_PIXELS_HEIGHT/32 * ROAD_PIXELS_WIDTH/32;
// const int GRASS = 0;
// const int WATER = 1;
// const int ROAD = 2;
// const int DIRT = 3;

// Coin Dimensions 
const int COIN_WIDTH = 30; 
const int COIN_HEIGHT = 30; 

const int TOTAL_COINS = 300; 

// Gift Dimensions
const int GIFT_WIDTH = 30;
const int GIFT_HEIGHT = 30; 

const int TOTAL_GIFTS = 50;

// Prof Dimensions
const int PROF_WIDTH = 30;
const int PROF_HEIGHT = 30;
