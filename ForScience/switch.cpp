//
//  switch.cpp
//  ForScience
//
//  Created by Yue on 7/1/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "switch.h"
#include "constant.h"
#include "utility.h"

Switch::Switch(int x, int y):Sprite(x, y){
    box.w = 40;
    box.h = 40;
    
    frame = OFF;
    set_clip();
}

Switch::~Switch(){
    
}

void Switch::set_clip(){
    
}

void Switch::animate(){
    if (frame == OFF) {
        frame = ON;
    }else{
        frame = OFF;
    }
}

void Switch::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x, box.y, tileSheet, screen, &clips[frame]);
    //show hint to player that it is active
    //or not?
}

bool Switch::is_block(){
    return false;
}