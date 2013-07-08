//
//  door.cpp
//  ForScience
//
//  Created by Yue on 7/7/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "door.h"
#include "utility.h"

Door::Door(){
    
}

Door::~Door(){
    
}

void Door::set_clip(){
    clips[CLOSE].x = 0;
    clips[CLOSE].w = 40;
    
    clips[OPEN_R].x = 40;
    clips[OPEN_R].w = 80;
    
    clips[OPEN_L].x = 120;
    clips[OPEN_L].w = 80;
    for (int i = CLOSE; i < TOTAL_CLIP; i +=1) {
        clips[i].h = 60;
        clips[i].y = 0;
    }
}


void Door::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}
