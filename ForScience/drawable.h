//
//  Drawable.h
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_drawable_h
#define ForScience_drawable_h

#include "SDL/SDL.h"

class Drawable{
public:
    virtual void handle_input(SDL_Event event) = 0;
    virtual void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen) = 0;
    virtual ~Drawable(){}
    
protected:
    Drawable(){}
    
//    virtual void set_clip() = 0;
};

#endif
