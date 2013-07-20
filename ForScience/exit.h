//
//  exit.h
//  ForScience
//
//  Created by Yue on 7/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__exit__
#define __ForScience__exit__

#include "sprite.h"
#include "animation.h"

class Exit:public Sprite{
    enum CLIP{
        CLOSE0,
        CLOSE1,
        CLOSE2,
        OPEN,
        TOTAL_CLIP
    };
    SDL_Rect clips[TOTAL_CLIP];
    Animation * animation;
    void set_clip();
    void set_anime();
    bool interacting;
public:
    Exit(int x, int y);
    ~Exit();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void animate();
    bool is_block();
    void interact(SDL_Rect rect);
    bool is_open();
};

#endif /* defined(__ForScience__exit__) */
