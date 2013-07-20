//
//  stickMaster.h
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__stickMaster__
#define __ForScience__stickMaster__

#include "stick.h"
#include "level.h"
#include "SDL/SDL.h"
//Handle all the stick figures together

class StickMaster{
    int total_stick;
    int active_stick;
    Stick ** stick_list;
   
public:
    StickMaster(Level * level,int total_stick, int pos[]);
    ~StickMaster();
    void animate();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void handle_input(SDL_Event event);
    int get_stick_count();
    Stick ** get_stick_list();
    bool is_all_stick_dead();
};

#endif /* defined(__ForScience__stickMaster__) */
