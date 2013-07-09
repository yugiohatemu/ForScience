//
//  door.h
//  ForScience
//
//  Created by Yue on 7/7/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__door__
#define __ForScience__door__

#include "SDL/SDL.h"

class Door{
    SDL_Rect box;
    enum CLIP{
        CLOSE,
        OPEN_R,
        OPEN_L,
        TOTAL_CLIP
    };
    int frame;
    SDL_Rect clips[TOTAL_CLIP];
    
    void set_clip();
public:
    Door(int x, int y);
    ~Door();
    SDL_Rect get_rect();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void animate();
    bool is_block();
};

#endif /* defined(__ForScience__door__) */
