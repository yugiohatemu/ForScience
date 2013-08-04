//
//  robotMaster.h
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__robotMaster__
#define __ForScience__robotMaster__

#include "robot.h"
#include "level.h"
#include "SDL/SDL.h"
#include "stickMaster.h"
#include "text.h"
#include "drawable.h"

class RobotMaster: public Drawable{
    int total_robot;
    int active_robot;
    Robot ** robot_list;
    bool pause;
public:
    
    RobotMaster(Level * level, int total_robot, int pos[]);
    ~RobotMaster();
    void animate();
    void set_text(Text *text);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void react_to(StickMaster * stick_master);
    void set_pause(bool p);
    void handle_input(SDL_Event event) ;
};

#endif /* defined(__ForScience__robotMaster__) */
