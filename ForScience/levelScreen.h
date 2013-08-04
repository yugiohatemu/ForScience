//
//  levelScreen.h
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__levelScreen__
#define __ForScience__levelScreen__

#include "SDL/SDL.h"
#include "drawable.h"

class LevelScreen: public Drawable{
private:
    void set_clip();
    
public:
    LevelScreen();
    ~LevelScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    
};

#endif /* defined(__ForScience__levelScreen__) */
