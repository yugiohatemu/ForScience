//
//  levelSelectScreen.h
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__levelSelectScreen__
#define __ForScience__levelSelectScreen__

#include "SDL/SDL.h"

class LevelSelectScreen{
private:
    enum CLIP{
        UNSELECT,SELECT,
        TOTAL_CLIP,
    };
    void set_clip();
    SDL_Rect clips[TOTAL_CLIP];
    int total_level;
    int selected_level;
    bool * levels;
public:
    LevelSelectScreen();
    ~LevelSelectScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);

};

#endif /* defined(__ForScience__levelSelectScreen__) */
