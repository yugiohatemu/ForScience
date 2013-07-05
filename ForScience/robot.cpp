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
    //if the walk is right,
    //then the position of fan is relative to taht
}

Robot::~Robot(){
    
}

void Robot::clip_tile(){
    for (int i = 0; i < FAN_R; i += 1) {
        clips[i].x = i* ROBOT_WIDTH;
        clips[i].y = 0;
        clips[i].w = ROBOT_WIDTH;
        clips[i].h = ROBOT_HEIGHT;
    }
    int offset = 8 * ROBOT_WIDTH + 80;
    //now clip the fans
    //grid 20 sub grid 5
    clips[FAN_R].x = offset+60;
    clips[FAN_R].y = 5;
    clips[FAN_R].w = 60;
    clips[FAN_R].h = 70;
    
    clips[FAN_L].x = offset;
    clips[FAN_L].y = 5;
    clips[FAN_L].w = 60;
    clips[FAN_L].h = 70;
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
    if (dir == SDLK_RIGHT) { // x +w, y-10
        apply_surface(box.x - camera.x+box.w, box.y - camera.y -10, tileSheet, screen, &clips[FAN_R]);
    }else if(dir == SDLK_LEFT){ // x - fan.w, y - 10
        apply_surface(box.x - camera.x-60, box.y - camera.y - 10, tileSheet, screen, &clips[FAN_L]);
    }
}