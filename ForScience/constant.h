//
//  constant.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_constant_h
#define ForScience_constant_h

#include "SDL_ttf/SDL_ttf.h"
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
//Fan
const int FAN_WIDTH = 60;
const int FAN_HEIGHT = 70;

//The dimensions of the level
const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 40;
const int TILE_HEIGHT = 40;

enum HUMAN_STATE{
    WALK,
    JUMP,
    CLIMB,
    CRAWL,
    FALL,
    STUCK,
    EXIT,
};

enum ROBOT_STATE{
    NORMAL,
    SUSPICIOUS,
    WARNING,
    ALERT,
    TURN,
};

extern bool LEVEL_PAUSE;


extern SDL_Surface *screen ;
extern SDL_Surface *tileSheet ;
extern SDL_Surface *robotSheet ;
extern SDL_Surface *stickSheet ;
extern SDL_Surface *menuSheet ;
extern TTF_Font *font;
extern bool QUIT;
#endif
