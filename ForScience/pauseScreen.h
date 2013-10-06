//
//  pauseScreen.h
//  ForScience
//
//  Created by Yue on 9/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__pauseScreen__
#define __ForScience__pauseScreen__

#include "screen.h"
#include "text.h"
class PauseScreen:public Screen{
    Screen * controller;
    enum CLIP{
        TITLE,
        //resume?
        PAUSE,
        TOTAL_CLIP,
    };
    void set_clip();
    SDL_Rect clips[TOTAL_CLIP];
    Text * instruction;
    Screen * selectLevel;
public:
    PauseScreen(Screen * level_select);
    ~PauseScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    void animate();
};

#endif /* defined(__ForScience__pauseScreen__) */
