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

Switch::Switch(){
    box.x = 7 * TILE_WIDTH;
    box.y = 9 * TILE_HEIGHT;
    box.w = 40;
    box.h = 40;
    
    frame = 0;
}

Switch::~Switch(){
    
}

//only interactable if rect collide
bool Switch::is_interacble(SDL_Rect rect){
    //Also shows that it is interacable to player, right?
    return check_collision(rect, box);
}

void Switch::handle_input(int key){
    if(key == SDLK_RETURN){
        if (frame == 0) {
            frame = 1;
        }else{
            frame = 0;
        }
    }
}

void Switch::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x, box.y, tileSheet, screen, &clips[frame]);
    //show hint to player that it is active
    //or not?
}