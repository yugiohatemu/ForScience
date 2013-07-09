//
//  exit.cpp
//  ForScience
//
//  Created by Yue on 7/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "exit.h"
#include "utility.h"

Exit::Exit(int x, int y){
    box.x = x;
    box.y = y;
    box.w = 60;
    box.h = 160;
    frame = 0;
    set_clip();
}

Exit::~Exit(){
    
}

void Exit::set_clip(){
    for (int i = CLOSE; i < TOTAL_CLIP; i +=1) {
        clips[i].x = 200+ i * box.w;
        clips[i].y = 0;
        clips[i].w = box.w;
        clips[i].h = box.h;
    }
}

void Exit::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

SDL_Rect Exit::get_rect(){
    return box;
}

void Exit::animate(){
    if (frame == CLOSE) {
        frame = OPEN;
    }else{
        frame = CLOSE;
    }
}