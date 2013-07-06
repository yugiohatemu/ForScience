//
//  stickMaster.cpp
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stickMaster.h"
#include "constant.h"
StickMaster::StickMaster(Level * level){
    total_stick = 2;
    
    stick_list =new Stick* [total_stick];
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i] = new Stick(level);
    }
    
    stick_list[1]->set_pos(8*TILE_WIDTH,3* TILE_HEIGHT);
    
    active_stick = 0;
    stick_list[active_stick]->set_active(true);
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
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i]->animate();
    }
}


void StickMaster::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    for (int i = 0; i < total_stick; i += 1) {
        stick_list[i]->show(camera, tileSheet, screen);
    }
}

//If tab, then we switch active stick figure
void StickMaster::handle_input(SDL_Event event){
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