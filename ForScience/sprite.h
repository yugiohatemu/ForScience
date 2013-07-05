//
//  sprite.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_sprite_h
#define ForScience_sprite_h

#include "SDL/SDL.h"
#include "level.h"
#include "quest.h"

class Sprite{
private:
    SDL_Rect box;
    int frame;
    enum CLIP{
        STAND = 0,
        WALK_R0,
        WALK_R1,
        WALK_R2,
        WALK_R3,
        WALK_L0,
        WALK_L1,
        WALK_L2,
        WALK_L3,
        TOTAL_CLIP,
    };
    SDL_Rect clips[TOTAL_CLIP];
    Quest * quest;
    
    void clip_tile();
    void process_quest();
public:
    Sprite();
    ~Sprite();
    
    void handle_input(SDL_Event event, Level * level);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    SDL_Rect get_rect();
    void set_quest(Quest * quest);
    
};


#endif
