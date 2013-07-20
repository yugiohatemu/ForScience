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
    fan.w = 120;
    fan.h = 140;
    
    frame = N_WALK_R0;
    dir = SDLK_RIGHT;
    state = NORMAL;
    speed = 15;
    clip_tile();
    //Text
    sub_title = NULL;
    
    //Survielence quest
   
    this->level = level;
    test_stick = NULL;
    mission = NULL;
    //
    search_area = new AreaSearch(TILE_WIDTH, 5 * TILE_HEIGHT,4 * TILE_WIDTH , TILE_HEIGHT);
}

Robot::~Robot(){
    sub_title = NULL;
    level = NULL;
    test_stick = NULL;
    if (mission) {
        delete mission;
    }
    delete search_area;
}


void Robot::set_pos(int x, int y){
    //box and fan together
    box.x = x;
    box.y = y;
    fan.x = box.x + box.w;
    fan.y = box.y - 40;
}

void Robot::set_text(Text * text){
    sub_title = text;
}

void Robot::set_mission(Mission * mission){
    this->mission = mission;
}


void Robot::clip_tile(){
    for (int i = 0; i < N_FAN_R; i += 1) {
        clips[i].x = i* ROBOT_WIDTH;
        clips[i].y = 0;
        clips[i].w = ROBOT_WIDTH;
        clips[i].h = ROBOT_HEIGHT;
    }
    
    for (int i = A_WALK_R0; i < TOTAL_CLIP; i +=1) {
        clips[i] = clips[i-A_WALK_R0];
        clips[i].y = ROBOT_HEIGHT;
    }
    
    //now clip the fans
    //grid 20 sub grid 5
    clips[N_FAN_R].x = 120;
    clips[N_FAN_R].y = 160;
    clips[N_FAN_R].w = 120;
    clips[N_FAN_R].h = 140;
    
    clips[N_FAN_L].x = 0;
    clips[N_FAN_L].y = 160;
    clips[N_FAN_L].w = 120;
    clips[N_FAN_L].h = 140;
    
    clips[A_FAN_L] = clips[N_FAN_L];
    clips[A_FAN_L].y = clips[N_FAN_L].y + 140;
    clips[A_FAN_R] = clips[N_FAN_R];
    clips[A_FAN_R].y = clips[N_FAN_L].y + 140;
}


void Robot::animate(){
    if(state == NORMAL || state == QUEST) return  ;
    
    SDL_Rect whole_box = merge_rect(box, fan);
    bool movable = false;
    if (level->move_on_level(whole_box, dir, speed)) {
        movable = level->move_on_level(box, dir, speed);
    }
   // level->interact_with_level(whole_box);
    if (state == ALERT) {
        if ((frame >= A_WALK_R0 && frame < A_WALK_R3) || (frame >= A_WALK_L0 && frame < A_WALK_L3)) {
            frame += 1;
        }else if(frame == A_WALK_R3){
            frame = A_WALK_R0;
        }else if(frame == A_WALK_L3){
            frame = A_WALK_L0;
        }
    }else{
        
        if ((frame >= N_WALK_R0 && frame < N_WALK_R3) || (frame >= N_WALK_L0 && frame < N_WALK_L3)) {
            frame += 1;
        }else if(frame == N_WALK_R3){
            frame = N_WALK_R0;
        }else if(frame == N_WALK_L3){
            frame = N_WALK_L0;
        }

    }
    ////we r not progressing, so need to change direction
    if (!movable) {
        if (dir == SDLK_RIGHT) {
            dir = SDLK_LEFT;
            if (state == ALERT) {
                frame = A_WALK_L0;
            }else{
                frame = N_WALK_L0;
            }
        }else{
            dir = SDLK_RIGHT;
            if (state == ALERT) {
                frame = A_WALK_R0;
            }else{
                frame = N_WALK_R0;
            }
        }
    }
    
    //mission
    if (mission) {
        if(mission->is_active()) {
            mission->update_status(dir, box.x, box.y);
        }
        else {
            state = ALERT;
            frame += A_WALK_R0;
            //maybe not necessary latter
            delete mission;
            mission = NULL;
            //stop questing
            if(test_stick) test_stick->delete_quest();
            timer.stop();
            test_stick = NULL;
            speed = 30;
            
        }
    }
    
    
   
}

void Robot::stop_quest(){
    state = NORMAL;
    sub_title->set_text("For Science");
    test_stick->delete_quest();
    if (dir == SDLK_RIGHT) {
        dir = SDLK_LEFT;
        if (state == ALERT) {
            frame = A_WALK_L0;
        }else{
            frame = N_WALK_L0;
        }
    }else{
        dir = SDLK_RIGHT;
        if (state == ALERT) {
            frame = A_WALK_R0;
        }else{
            frame = N_WALK_R0;
        }
    }
    timer.stop();
    test_stick = NULL;
}

void Robot::react_to(Stick * stick){
    //need to judge position first
    SDL_Rect rect = stick->get_rect();
    HUMAN_STATE h_state = stick->get_state();
    SDL_Rect range = merge_rect(box, fan);
    //based on dir, if the robot is facing right, and rect is on left, then ignore behaviour and collison
    //if in visible range
    if (is_rect_on_side(dir, rect, box)) {
        if (h_state != WALK) { //or space?. maybe expanded latter
            //then robot is suspicious
            state = SUSPICIOUS;
        }
    }
    if (state == SUSPICIOUS) {
        //need use scanner to check the radar
        //1st robot collide with search area
        
        if (check_collision(search_area->get_area(), range)) {
            if (search_area->try_search(range)) {
                //stick is in there, then good
                if (check_collision(rect, range) && h_state == WALK) {
                    state = NORMAL;
                    search_area->reset();
                    //TODO: TURN Direction
                }
            }else{
                state = ALERT;
                //going to excution mode
            }
        }
    }
    if (state == ALERT) {
        if (check_collision(search_area->get_area(), range)){
            stick->minus_life();
            //call the level to end the game maybe?
        }
    }
    
//    
//    bool collide = (check_collision(box, rect) || check_collision(fan, rect));
//    //if not interactive nor the stick that robot cares now
//    if ( !collide && test_stick != stick) {
//        return ;
//    }
//    if (state == ALERT && collide) {
//        stick->minus_life();
//        debug("lose life");
//        state = NORMAL;
//        frame -= A_WALK_R0;
//        return ;
//    }
//    //collide or test_stick == stick
//    //suppose normal state is walk
//    if (state == NORMAL && collide) {
//        
//        state = QUEST;
//        stick->get_quest(new Quest(1));
//        //if the stick is on auto pilot mode, do not change sub title
//        if (!stick->is_autopilot()) {
//            sub_title->set_text("JUMP!");
//        }
//        test_stick = stick;
//        timer.start();
//        //For now, just count for simple collision
//        if (mission  && mission->is_active()) {
//            mission->check_in();
//        }
//    }else if(state == QUEST){
//        //so the only way quest is done is that
//        //collide (do quest in robot area)
//        //has quest, get quest done, not time out
//        //doing quest is collide, has quest, quest not done
//        //others are abandon questing
//        if (collide && stick->has_quest() && timer.get_ticks() <= 2000) {
//            if(stick->is_quest_done()){
//                stop_quest();
//                if(mission){
//                    mission->reset(dir,box.x,box.y);
//                }
//            }
//        }else{
//            stick->minus_life();
//            debug("lose life");
//            stop_quest();
//        }
//        
//    }
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
        
        if (state == ALERT) apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[A_FAN_R]);
        else apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[N_FAN_R]);
        
    }else if(dir == SDLK_LEFT){ // x - fan.w, y - 10
        fan.x = box.x - fan.w;
        if(state == ALERT) apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[A_FAN_L]);
        else apply_surface(fan.x - camera.x, fan.y - camera.y, tileSheet, screen, &clips[N_FAN_L]);
    }
}