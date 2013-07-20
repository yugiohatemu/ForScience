//
//  exit.cpp
//  ForScience
//
//  Created by Yue on 7/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "exit.h"
#include "utility.h"

Exit::Exit(int x, int y):Sprite(x, y){
    box.w = 60;
    box.h = 160;
    frame = CLOSE0;
    attr = STICK_ACTIVE;
    interacting = false;
    
    set_clip();
    set_anime();
    
}

Exit::~Exit(){
    delete animation;
}

void Exit::set_anime(){
    int * frames = new int [TOTAL_CLIP];
    for (int i = 0; i < TOTAL_CLIP; i +=1) {
        frames[i] = i;
    }
    animation = new Animation(TOTAL_CLIP, frames, false);
}

bool Exit::is_open(){
    return frame == OPEN;
}

void Exit::set_clip(){
    for (int i = CLOSE0; i < TOTAL_CLIP; i +=1) {
        clips[i].x = 200+ i * box.w;
        clips[i].y = 0;
        clips[i].w = box.w;
        clips[i].h = box.h;
    }
}

void Exit::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

void Exit::interact(SDL_Rect rect){
    if (check_collision(box, rect)) {
        //if not animating, animating
        interacting = true;
    }else{
        if (interacting) {
            animation->reverse_frame();
            interacting = false;
        }
    }
}

void Exit::animate(){
    if (interacting || !animation->is_anime_done()) {
        frame = animation->get_current_frame();
    }
}

bool Exit::is_block(){
    return false;
}