//
//  menuScreen.h
//  ForScience
//
//  Created by Yue on 8/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__menuScreen__
#define __ForScience__menuScreen__

#include "SDL/SDL.h"

class MenuScreen{
    //options?
    enum CLIP{
        TITLE,
        S_START, U_START,
        S_OPTION, U_OPTION,
        TOTAL_CLIP,
    };
    
    enum STATE{
        START,
    };
    
    SDL_Rect clips[TOTAL_CLIP];
    void set_clip();
    bool selected;
    int frame;
    STATE state;
public:
    MenuScreen();
    ~MenuScreen();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
};



#endif /* defined(__ForScience__menuScreen__) */
