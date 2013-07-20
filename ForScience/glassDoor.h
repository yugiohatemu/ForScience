//
//  glassDoor.h
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__glassDoor__
#define __ForScience__glassDoor__

#include "sprite.h"
#include "animation.h"

class GlassDoor:public Sprite{
    enum CLIP{
        CLOSE0,
        CLOSE1,
        CLOSE2,
        OPEN,
        TOTAL_CLIP
    };
    SDL_Rect clips[TOTAL_CLIP];
    void set_clip();
    void set_anime();
    Animation * animation;
    bool interacting;
public:
    GlassDoor(int x, int y);
    ~GlassDoor();
    void animate();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen) ;
    bool is_block();
    
};

#endif /* defined(__ForScience__glassDoor__) */
