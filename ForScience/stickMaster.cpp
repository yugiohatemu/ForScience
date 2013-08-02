//
//  stickMaster.cpp
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stickMaster.h"
#include "constant.h"


StickMaster::StickMaster(Level * level,int total_stick, int pos[]){
    this->total_stick = total_stick;
    
    stick_list =new Stick* [total_stick];
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i] = new Stick(level);
        stick_list[i]->set_pos(pos[2*i], pos[2*i+1]);
    }
    
    active_stick = 0;
    stick_list[active_stick]->set_active(true);
    pause = false;
    
}

StickMaster::~StickMaster(){
    for (int i = 0; i < total_stick; i += 1) {
        delete stick_list[i];
    }
    delete [] stick_list;
    
}


int StickMaster::get_stick_count(){
    return total_stick;
}

Stick ** StickMaster::get_stick_list(){
    return stick_list;
}

void StickMaster::animate(){
    if(pause) return ;
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i]->animate();
    }
}

bool StickMaster::is_all_stick_dead(){
    for (int i = 0; i < total_stick; i += 1){
        if (stick_list[i]->is_alive()) {
            return false;
        }
    }
        
    return true;
}

//needs to overwrite
bool StickMaster::is_win(){
    return true;
}
bool StickMaster::is_gameover(){
    return true;
}

void StickMaster::set_pause(bool p){
    pause = p;
}

void StickMaster::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i]->show(camera, tileSheet, screen);
    }
}

//If tab, then we switch active stick figure
void StickMaster::handle_input(SDL_Event event){
    if(pause) return ;
    if (LEVEL_PAUSE) return ;
    bool all_exit = true;
    for (int i = 0; i < total_stick; i += 1) {
        if(stick_list[i]->get_state() != EXIT){
            //or all the stick dies?
            all_exit = false;
            break;
        }
    }
    LEVEL_PAUSE = all_exit;
    
    if( event.type == SDL_KEYDOWN ){
        if (event.key.keysym.sym == SDLK_TAB) {
            active_stick += 1;
            if (active_stick == total_stick) {
                active_stick = 0;
            }
            for (int i = 0; i < total_stick; i += 1) {
                stick_list[i]->set_active(false);
            }
            stick_list[active_stick]->set_active(true);
        }else{
            stick_list[active_stick]->handle_input(event);
        }
    }else if(event.type == SDL_KEYUP){
        stick_list[active_stick]->handle_input(event);
    }
}