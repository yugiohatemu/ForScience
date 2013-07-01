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

class Sprite{
    private:
        SDL_Rect box;
        int xPos, yPos;
        int pos;
        int frame;
        
        SDL_Surface * tileSheet;
    enum State{
        STAND = 0,
        WALK_R0,
        WALK_R1,
        WALK_R2,
        WALK_R3,
        WALK_L0,
        WALK_L1,
        WALK_L2,
        WALK_L3,
        TOTAL_STATE,
    };
        SDL_Rect clips[TOTAL_STATE];
        
    public:
        Sprite();
        ~Sprite();
        void clip_tile();
        void handle_input(SDL_Event event, Level * level);
        void show(SDL_Rect camera, SDL_Surface * screen);
};


#endif
