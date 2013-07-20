//
//  robot.h
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__robot__
#define __ForScience__robot__

#include "SDL/SDL.h"
#include "level.h"
#include "text.h"
#include "timer.h"
#include "stickMaster.h"
#include "mission.h"
#include "areaSearch.h"
#include "stopWatch.h"

class Robot{
private:
    SDL_Rect box;
    SDL_Rect fan;
    int frame;
    int dir;
    enum CLIP{ //normal, angry, pause?
        N_WALK_R0 = 0, N_WALK_R1, N_WALK_R2, N_WALK_R3,
        N_WALK_L0, N_WALK_L1, N_WALK_L2, N_WALK_L3,
        N_FAN_R,N_FAN_L,
        A_WALK_R0,A_WALK_R1,A_WALK_R2,A_WALK_R3,
        A_WALK_L0,A_WALK_L1,A_WALK_L2,A_WALK_L3,
        A_FAN_R,A_FAN_L,
        TOTAL_CLIP
    };
    SDL_Rect clips[TOTAL_CLIP];
    
    enum STATE{
        STAND = 0,
        NORMAL = 15,
        WARNING,
        SUSPICIOUS,
        ALERT,
        
        TOTAL_STATE,
    };
    STATE state;
    int speed; //walk or angry
    Text * sub_title;
    Timer timer;
    Level * level;
    Stick * test_stick;
    Mission * mission;
    AreaSearch * search_area;
    StopWatch * stopWatch;
    void clip_tile();
    void react_to(Stick * stick);
    void stop_quest();
    void turn_back();
public:
    Robot(Level * level);
    ~Robot();
    void set_pos(int x, int y);
    void animate();
    void react_to(StickMaster * stick_master);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void set_text(Text * text);
    void set_mission(Mission * mission);
};


#endif /* defined(__ForScience__robot__) */
