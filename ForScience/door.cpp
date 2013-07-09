//
//  door.cpp
//  ForScience
//
//  Created by Yue on 7/7/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "door.h"
#include "utility.h"

Door::Door(int x, int y){
    box.x = x;
    box.y = y;
    box.w = 40;
    box.h = 120;
    
    frame = CLOSE;
    set_clip();
}

Door::~Door(){
    
}

bool Door::is_block(){
    return (frame == CLOSE);
}

void Door::set_clip(){
    clips[CLOSE].x = 0;
    clips[CLOSE].w = 40;
    
    clips[OPEN_R].x = 40;
    clips[OPEN_R].w = 60;
    
    clips[OPEN_L].x = 100;
    clips[OPEN_L].w = 60;
    for (int i = CLOSE; i < TOTAL_CLIP; i +=1) {
        clips[i].h = 120;
        clips[i].y = 160;
    }
}


void Door::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

//TODO:should depends on which way ask the door to open
void Door::animate(){
    if (frame == CLOSE) {
        frame = OPEN_L;
    }else if(frame == OPEN_L){
        frame = CLOSE;
    }
}

SDL_Rect Door::get_rect(){
    return box;
}