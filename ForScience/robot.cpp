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
    
    //the head of robot is around 25
    fan.x = box.x + box.w;
    fan.y = box.y - 10;
    fan.w = FAN_WIDTH;
    fan.h = FAN_HEIGHT;
    
    frame = WALK_R0;
    dir = SDLK_RIGHT;
    state = WALK;
    clip_tile();
    //Text
    sub_title = NULL;
    
    //Survielence quest
    quest = new Quest(1);
}

Robot::~Robot(){
    sub_title = NULL;
    delete quest;
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
    if(state == STAND || state == QUEST) return  ;
    
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


void Robot::react_to(Sprite * stick){
    //need to judge position first
    SDL_Rect rect = stick->get_rect();
    if (!check_collision(box, rect) && !check_collision(fan, rect)) {
        //set the state to walk
        state = WALK;
        sub_title->set_text("For Science");
        return ;
    }
    //set state to stand
    //if in normal wtate, then set it to quest, ask ppl to process quest
    if (state == WALK) {
        state = QUEST;
        sub_title->set_text("JUMP!");
       
        stick->set_quest(quest);
    }else if(state == QUEST){
        if (quest->is_done()) {
            state = WALK;
            //walk to other direction
            if (dir == SDLK_RIGHT) {
                dir = SDLK_LEFT;
                frame = WALK_L0;
            }else{
                dir = SDLK_RIGHT;
                frame = WALK_R0;
            }
            quest->set_done(false);
            stick->set_quest(NULL);
        }
    }
}

void Robot::link_text(Text * text){
    sub_title = text;
}


void Robot::show(SDL_Rect camera, SDL_Surface *tileSheet,SDL_Surface *screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
    if (dir == SDLK_RIGHT) { // x +w, y-10,
        fan.x = box.x + box.w;
        apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[FAN_R]);
    }else if(dir == SDLK_LEFT){ // x - fan.w, y - 10
        fan.x = box.x - fan.w;
        apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[FAN_L]);
    }
}