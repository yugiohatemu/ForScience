//
//  Stick.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_Stick_h
#define ForScience_Stick_h

#include "SDL/SDL.h"
#include "level.h"
#include "quest.h"
#include "sprite.h"
class Stick{
private:
    SDL_Rect box;
    int frame;
    int life;
    enum CLIP{ //I - Inactive, A - Active
        I_STAND = 0,
        I_WALK_R0,I_WALK_R1,I_WALK_R2,I_WALK_R3,
        I_WALK_L0,I_WALK_L1,I_WALK_L2,I_WALK_L3,
        I_JUMP,
        I_CLIMB0, I_CLIMB1,
        A_STAND,
        A_WALK_R0,A_WALK_R1,A_WALK_R2,A_WALK_R3,
        A_WALK_L0,A_WALK_L1,A_WALK_L2,A_WALK_L3,
        A_JUMP,
        A_CLIMB0, A_CLIMB1,
        TOTAL_CLIP,
    };
    SDL_Rect clips[TOTAL_CLIP];
    Quest * quest;
    Level * level;
    Sprite * item;
    bool active;
    void clip_tile();
    enum STATE{
        WALK,
        JUMP,
        CLIMB,
        TOTAL_STATE
    };
    STATE state;
public:
    Stick(Level * level);
    ~Stick();
    void set_pos(int x, int y);
    void set_active(bool active);
    void animate();
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    SDL_Rect get_rect();
    //Quest realted
    void get_quest(Quest * quest);
    bool has_quest();
    bool is_quest_done();
    void delete_quest();
    bool is_autopilot();
    void minus_life();
    void hold_item(Sprite * item);
};


#endif
