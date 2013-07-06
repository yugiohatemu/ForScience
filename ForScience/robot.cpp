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
#include "quest.h"
#include <iostream>
Robot::Robot(Level * level){
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
   
    this->level = level;
    test_stick = NULL;
    mission = NULL;
}

Robot::~Robot(){
    sub_title = NULL;
    level = NULL;
    test_stick = NULL;
    if (mission) {
        delete mission;
    }
}


void Robot::set_pos(int x, int y){
    //box and fan together
    box.x = x;
    box.y = y;
    fan.x = box.x + box.w;
    fan.y = box.y - 10;
}

void Robot::set_text(Text * text){
    sub_title = text;
}

void Robot::set_mission(Mission * mission){
    this->mission = mission;
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


void Robot::animate(){
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
    //mission
    if (mission) {
        if(mission->is_active()) {
            mission->update_status(dir, box.x, box.y);
        }
        else {
            state = ANGRY;
            //maybe not necessary latter
            delete mission;
            mission = NULL;
            //stop questing
            if(test_stick) test_stick->delete_quest();
            timer.stop();
            test_stick = NULL;
            debug("Angry");
        }
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

void Robot::stop_quest(){
    state = WALK;
    sub_title->set_text("For Science");
    test_stick->delete_quest();
    if (dir == SDLK_RIGHT) {
        dir = SDLK_LEFT;
        frame = WALK_L0;
    }else{
        dir = SDLK_RIGHT;
        frame = WALK_R0;
    }
    timer.stop();
    test_stick = NULL;
}

void Robot::react_to(Stick * stick){
    //need to judge position first
    SDL_Rect rect = stick->get_rect();
    bool collide = (check_collision(box, rect) || check_collision(fan, rect));
    //if not interactive nor the stick that robot cares now
    if ( !collide && test_stick != stick) {
        return ;
    }
    //collide or test_stick == stick
    //suppose normal state is walk
    if (state == WALK && collide) {
        
        state = QUEST;
        stick->get_quest(new Quest(1));
        //if the stick is on auto pilot mode, do not change sub title
        if (!stick->is_autopilot()) {
            sub_title->set_text("JUMP!");
        }
        test_stick = stick;
        timer.start();
        //For now, just count for simple collision
        if (mission  && mission->is_active()) {
            mission->check_in();
        }
    }else if(state == QUEST){
        //so the only way quest is done is that
        //collide (do quest in robot area)
        //has quest, get quest done, not time out
        //doing quest is collide, has quest, quest not done
        //others are abandon questing
        if (collide && stick->has_quest() && timer.get_ticks() <= 2000) {
            if(stick->is_quest_done()){
                stop_quest();
                if(mission){
                    mission->reset(dir,box.x,box.y);
                }
            }
        }else{
            stick->minus_life();
            stop_quest();
        }
        
    }
}


void Robot::react_to(StickMaster * stick_master){
    //ask stickmaster to return a list of stick that might interact
    Stick ** stick_list = stick_master->get_stick_list();
    int total_count = stick_master->get_stick_count();
    for (int i = 0; i < total_count; i += 1) {
        react_to(stick_list[i]);
    }
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