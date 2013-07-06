//
//  mission.cpp
//  ForScience
//
//  Created by Yue on 7/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "mission.h"
#include "SDL/SDL.h"

Mission::Mission(int dir, int x, int y){
    active = true;
    reset(dir, x, y);
}

Mission::~Mission(){
    
}

void Mission::check_in(){
    check = true;
}

bool Mission::is_active(){
    return active;
}

void Mission::update_status(int dir, int x, int y){
    if (dir_list.size()!= 0 && dir_list[0] != dir) {
        dir_list.erase(dir_list.begin());
    }else if(dir_list.size() == 1){
        if (dir_list[0] == SDLK_LEFT) {
            if (x > this->x) {
                if (check) {
                    reset(dir, x, y);
                }else{
                    active = false;
                }
            }
        }else if (dir_list[0] == SDLK_RIGHT) {
            if (x < this->x) {
                if (check) {
                    reset(dir, x, y);
                }else{
                    active = false;
                }
            }
        }
    }
}

void Mission::reset(int dir, int x, int y){
    this->x = x;
    this->y = y;
    dir_list.clear();
    if (dir == SDLK_LEFT) {
        dir_list.push_back( SDLK_LEFT);
        dir_list.push_back( SDLK_RIGHT);
        dir_list.push_back( SDLK_LEFT);
    }else if(dir == SDLK_RIGHT){
        dir_list.push_back( SDLK_RIGHT);
        dir_list.push_back( SDLK_LEFT);
        dir_list.push_back( SDLK_RIGHT);
    }
    check = false;
}