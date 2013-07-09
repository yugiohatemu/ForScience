//
//  interact.h
//  ForScience
//
//  Created by Yue on 7/9/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__interact__
#define __ForScience__interact__

#include "SDL/SDL.h"

class Sprite{
protected:
    SDL_Rect box;
    int frame;
    virtual void set_clip() = 0;
    enum Attribute{
        ROBOT_ACTIVE, //can only be activated by robot
        STICK_ACTIVE, //can only be activated by stick
        TOTAL_ATTR
    };
    Attribute attr;
public:
    Sprite(int x, int y){box.x = x, box.y = y;}
    virtual ~Sprite(){}
    SDL_Rect get_rect(){return box;}
    Attribute get_attr(){return attr;}
    virtual void animate() = 0;
    virtual void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen) = 0;
    virtual bool is_block()=0;
};

#endif /* defined(__ForScience__interact__) */
