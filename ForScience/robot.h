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
#include "tile.h"

class Robot{
private:
    SDL_Rect box;
    int xPos, yPos;
    int pos;
    int frame;
    enum State{
        WALK_R0 = 0,
        WALK_R1,
        WALK_R2,
        WALK_R3,
        WALK_L0,
        WALK_L1,
        WALK_L2,
        WALK_L3,
        TOTAL_STATE
    };
    
    SDL_Rect clips[TOTAL_STATE];
public:
    Robot();
    ~Robot();
    void clip_tile();
    void animate(Tile * tiles[]);
    void show(SDL_Rect camera, SDL_Surface * screen, SDL_Surface * tileSheet);
};


#endif /* defined(__ForScience__robot__) */
