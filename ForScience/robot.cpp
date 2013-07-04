//
//  robot.cpp
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "robot.h"
#include "constant.h"
#include "utility.h"

Robot::Robot(){
    box.x = 8*TILE_WIDTH;
    box.y = LEVEL_HEIGHT - TILE_HEIGHT - ROBOT_HEIGHT;
    box.w = ROBOT_WIDTH ;
    box.h = ROBOT_HEIGHT;
    
    frame = WALK_R0;
    dir = SDLK_RIGHT;
    clip_tile();
}

Robot::~Robot(){
    
}

void Robot::clip_tile(){
    for (int i = 0; i < TOTAL_STATE; i += 1) {
        clips[i].x = i* ROBOT_WIDTH;
        clips[i].y = 0;
        clips[i].w = ROBOT_WIDTH;
        clips[i].h = ROBOT_HEIGHT;
    }
}

void Robot::animate(Level * level){
    int oldx = box.x;
    level->move_on_level(box, dir, 15);
    
    if ((frame >= WALK_R0 && frame < WALK_R3) || (frame >= WALK_L0 && frame < WALK_L3)) {
        frame += 1;
    }else if(frame == WALK_R3){
        frame = WALK_R0;
    }else if(frame == WALK_L3){
        frame = WALK_L0;
    }
    ////we r not progressing, so need to change direction
    if (oldx == box.x) { 
        if (dir == SDLK_RIGHT) {
            dir = SDLK_LEFT;
            frame = WALK_L0;
        }else{
            dir = SDLK_RIGHT;
            frame = WALK_R0;
        }
    }
}


void Robot::show(SDL_Rect camera, SDL_Surface *tileSheet,SDL_Surface *screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}