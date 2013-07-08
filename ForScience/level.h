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
    enum CLIP{
        WALL_C0, WALL_C1, WALL_C2, WALL_C3,WALL_C4,
        WALL_H0, WALL_H1,WALL_H2,WALL_H3, WALL_H4,
        WALL_V0,WALL_V1,WALL_V2, WALL_V3, WALL_V4,
        EMPTY,BACK_WALL,LADDER, BRICK,
        TOTAL_CLIP,
    };
    
    Tile * tiles;
    SDL_Rect clips[TOTAL_CLIP];
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
