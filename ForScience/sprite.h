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

class Sprite{
    private:
        SDL_Rect box;
        int xVel, yVel;
        int xPos, yPos;
        int pos;
    public:
        Sprite();
//        void handle_input(SDL_Event event);
        void handle_input(SDL_Event event, Tile * tiles[]);
        void move(Tile * tiles);
        void show(SDL_Rect camera,SDL_Surface * dot, SDL_Surface * screen);
};


#endif
