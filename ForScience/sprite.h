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
#include "tile.h"
#include "timer.h"
class Sprite{
    private:
        SDL_Rect box;
        int xPos, yPos;
        int pos;
        int frame;
        SDL_Rect clips[7];
        SDL_Surface * tileSheet;
    enum State{
        STAND = 0,
        WALKR0,
        WALKR1,
        WALKR2,
        WALKL0,
        WALKL1,
        WALKL2,
        JUMP,
    };
        
    public:
        Sprite();
        ~Sprite();
        void clip_tile();
        void animate();
        void handle_input(SDL_Event event, Tile * tiles[]);
        void show(SDL_Rect camera,SDL_Surface * dot, SDL_Surface * screen);
        void show(SDL_Rect camera, SDL_Surface * screen);
};


#endif
