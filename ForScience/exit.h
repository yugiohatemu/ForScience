//
//  exit.h
//  ForScience
//
//  Created by Yue on 7/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__exit__
#define __ForScience__exit__

#include "SDL/SDL.h"

class Exit{
    SDL_Rect box;
    enum CLIP{
        CLOSE,
        OPEN,
        TOTAL_CLIP
    };
    int frame;
    SDL_Rect clips[TOTAL_CLIP];
    
    void set_clip();
public:
    Exit(int x, int y);
    ~Exit();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    SDL_Rect get_rect();
    void animate();
};

#endif /* defined(__ForScience__exit__) */
