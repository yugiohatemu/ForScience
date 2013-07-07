//
//  level.h
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__level__
#define __ForScience__level__

#include "SDL/SDL.h"


class Level{
    struct Tile{
        SDL_Rect box;
        int type;
        Tile();
        void set_tile(int x, int y, int w, int h, int type);
    };
    Tile * tiles;
    SDL_Rect * clips;
    void set_clip();
    void set_tile();
    int get_tile_pos(int x, int y);
    
public:
    Level();
    ~Level();
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    bool move_on_level(SDL_Rect &box, int dir, int speed);

};

#endif /* defined(__ForScience__level__) */
