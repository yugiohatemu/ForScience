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
const int SCREEN_HEIGHT = 540;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 30;


//Stick man
const int STICK_WIDTH = 40;
const int STICK_HEIGHT = 120;

//Robot
const int ROBOT_WIDTH = 45;
const int ROBOT_HEIGHT = 80; //or 40

//The dimensions of the level
const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;
const int TOTAL_TILES = 192;

const int TILE_COLUMN = 16;
const int TILE_ROW = 12;

//
const int TILE_SPRITES = 5;
const int TILE_EMPTY = 0;
const int TILE_FLOOR = 1;
const int TILE_BACKWALL = 2;
const int TILE_LADDER = 3;
const int TILE_BRICK = 4;

#endif
