//
//  switch.h
//  ForScience
//
//  Created by Yue on 7/1/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__switch__
#define __ForScience__switch__

#include "sprite.h"

class Switch: public Sprite{
    enum{
        OFF = 0,
        ON,
        TOTAL_CLIP
    }CLIPS;
    
    void set_clip();
    SDL_Rect clips[TOTAL_CLIP];
public:
    Switch(int x, int y);
    ~Switch();
    void animate();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    bool is_block();
};

#endif /* defined(__ForScience__switch__) */
