//
//  winScreen.h
//  ForScience
//
//  Created by Yue on 8/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__winScreen__
#define __ForScience__winScreen__

#include "screen.h"
#include "text.h"
class EndScreen:public Screen{
    Screen * controller;
    Screen * level_select;
    enum CLIP{
        YOU_WIN,
        YOU_LOSE,
        TOTAL_CLIP,
    };
    void set_clip();
    SDL_Rect clips[TOTAL_CLIP];
    bool win;
    Text * instruction;
public:
    EndScreen(bool win, Screen * level_select);
    ~EndScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    void animate();
};

#endif /* defined(__ForScience__winScreen__) */
