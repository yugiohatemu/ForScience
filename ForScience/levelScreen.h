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
#include "level.h"


class LevelScreen: public Drawable{
private:
    Level * level;
public:
    LevelScreen(int selected = 0);
    ~LevelScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    void animate();
    void set_sheet(SDL_Surface * robot, SDL_Surface * stick);
};

#endif /* defined(__ForScience__levelScreen__) */
