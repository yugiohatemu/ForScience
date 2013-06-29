//
//  constant.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_constant_h
#define ForScience_constant_h

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 30;

//The dot dimensions
const int DOT_WIDTH = 50;
const int DOT_HEIGHT = 140;

//The dimensions of the level
const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;
const int TOTAL_TILES = 192;
const int TILE_SPRITES = 4;
const int TILE_COLUMN = 16;
const int TILE_ROW = 12;

//
const int TILE_EMPTY = 0;
const int TILE_FLOOR = 1;
const int TILE_BACKWALL = 2;
const int TILE_LADDER = 3;


#endif
