//
//  switch.h
//  ForScience
//
//  Created by Yue on 7/1/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__switch__
#define __ForScience__switch__

#include "SDL/SDL.h"

class Switch{
    enum{
        S_OFF = 0,
        S_ON,
        TOTAL_STATE
    }state;
    SDL_Rect box;
    void set_clip();
    SDL_Rect clips[TOTAL_STATE];
    int frame;
public:
    Switch();
    ~Switch();
    void handle_input(int key);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    bool is_interacble(SDL_Rect rect);
};

#endif /* defined(__ForScience__switch__) */
