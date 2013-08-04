//
//  levelSelectScreen.cpp
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelSelectScreen.h"
#include "utility.h"
#include "constant.h"

LevelSelectScreen::LevelSelectScreen(){
    total_level = 3;
    selected_level = 0;
    
    levels = new bool[total_level];
    for (int i = 0; i < total_level; i +=1) {
        levels[i] = false;
    }
    levels[selected_level] = true;
    
    set_clip();
}

LevelSelectScreen::~LevelSelectScreen(){
    delete [] levels;
}

void LevelSelectScreen::set_clip(){
    //155, 50
    clips[UNSELECT].x = 0;
    clips[UNSELECT].y = 155;
    clips[UNSELECT].w = 50;
    clips[UNSELECT].h = 50;
    
    clips[SELECT].x = 50;
    clips[SELECT].y = 155;
    clips[SELECT].w = 50;
    clips[SELECT].h = 50;
}

void LevelSelectScreen::handle_input(SDL_Event event){
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        
        if (dir == SDLK_UP){
            
        }else if(dir == SDLK_DOWN){
           
        }else if(dir == SDLK_LEFT){
            selected_level = (selected_level + total_level- 1) % total_level;
            for (int i = 0; i < total_level; i +=1) {
                levels[i] = false;
            }
            levels[selected_level] = true;
        }else if(dir == SDLK_RIGHT){
            selected_level = (selected_level + 1) % total_level;
            for (int i = 0; i < total_level; i +=1) {
                levels[i] = false;
            }
            levels[selected_level] = true;
        }else if(dir == SDLK_RETURN){
           //return
            current_screen = LEVEL_SCREEN;
            LEVEL_PAUSE = false;
        }
    }
}

void LevelSelectScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    SDL_FillRect(screen , NULL , 0x000000);
    for (int i = 0; i < total_level; i += 1) {
        if(levels[i]) apply_surface(i * 50 + 20, 50, tileSheet, screen, &clips[SELECT]);
        else apply_surface(i * 50+ 20, 50, tileSheet, screen, &clips[UNSELECT]);
    }
}
