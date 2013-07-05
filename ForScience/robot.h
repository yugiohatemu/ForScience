//
//  robot.h
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__robot__
#define __ForScience__robot__


#include "SDL/SDL.h"
#include "level.h"

class Robot{
private:
    SDL_Rect box;

    int frame;
    int dir;
    enum State{
        WALK_R0 = 0,
        WALK_R1,
        WALK_R2,
        WALK_R3,
        WALK_L0,
        WALK_L1,
        WALK_L2,
        WALK_L3,
        FAN_R,
        FAN_L,
        TOTAL_STATE
    };
    
    SDL_Rect clips[TOTAL_STATE];
public:
    Robot();
    ~Robot();
    void clip_tile();
    void animate(Level * level);
    //void animate(Tile * tiles[]);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
};


#endif /* defined(__ForScience__robot__) */
