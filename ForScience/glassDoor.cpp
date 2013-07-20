//
//  glassDoor.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "glassDoor.h"
#include "utility.h"

GlassDoor::GlassDoor(int x, int y):Sprite(x,y){
    box.w = 20;
    box.h = 120;
    frame = CLOSE0;
    attr = ROBOT_ACTIVE;
    interacting = false;
    
    set_clip();
    set_anime();
}

GlassDoor::~GlassDoor(){
    delete animation;
}

void GlassDoor::set_clip(){
    for (int i = CLOSE0; i < TOTAL_CLIP; i +=1) {
        clips[i].x = 200+ i * box.w;
        clips[i].y = 160;
        clips[i].w = box.w;
        clips[i].h = box.h;
    }
}

void GlassDoor::set_anime(){
    int * frames = new int [TOTAL_CLIP];
    for (int i = 0; i < TOTAL_CLIP; i +=1) {
        frames[i] = i;
    }
    animation = new Animation(TOTAL_CLIP, frames, false);
}

void GlassDoor::animate(){
    if (interacting || !animation->is_anime_done()) {
        frame = animation->get_current_frame();
    }
}

void GlassDoor::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

bool GlassDoor::is_block(){
    return frame != OPEN;
}