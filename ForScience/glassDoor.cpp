//
//  glassDoor.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "glassDoor.h"
#include "utility.h"
#include  <iostream>
GlassDoor::GlassDoor(int x, int y):Sprite(x,y){
    box.w = 20;
    box.h = 120;
    frame = CLOSE0;
    attr = ROBOT_ACTIVE;
    interacting = false;
    active = false;
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

void GlassDoor::set_active(bool active){
    this->active = active;
}


void GlassDoor::interact(SDL_Rect rect){
    //need another index
    active = true;
    if (check_collision(box, rect)) {
        //if not animating, animating
        interacting = true;
        
    }else{
        if (interacting) {
            animation->reverse_frame();
            interacting = false;
            //need to reverse frame, but where
        }
    }
}

void GlassDoor::interact_with_stick(SDL_Rect rect){ //add a direction?
    if (check_collision(box, rect)) {
        if (frame == OPEN) {
            //add speed vector, allow the stick to pass?
        }else{ //block, 
            
        }
    }
}

void GlassDoor::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

bool GlassDoor::is_block(){
    return frame != OPEN;
}

 
