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

class Robot{
private:
    SDL_Rect box;
    SDL_Rect fan;
    int frame;
    int dir;
    enum CLIP{
        WALK_R0 = 0,WALK_R1,WALK_R2,WALK_R3,
        WALK_L0,WALK_L1,WALK_L2,WALK_L3,
        FAN_R,FAN_L,
        TOTAL_CLIP
    };
    SDL_Rect clips[TOTAL_CLIP];
    
    enum STATE{
        STAND = 0,
        WALK,
        JUMP,
        QUEST,
        ANGRY,
        TOTAL_STATE,
    };
    int state;
    
    Text * sub_title;
    Timer timer;
    Level * level;
    Stick * test_stick;
    Mission * mission;
    void clip_tile();
    void react_to(Stick * stick);
    void stop_quest();
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
