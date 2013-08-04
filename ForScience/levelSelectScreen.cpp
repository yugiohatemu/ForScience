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

LevelSelectScreen::LevelSelectScreen():Screen(){
    total_level = 11;
    selected_level = 0;
    //level_row = 2
    //level_column = 5
    //also last one is exit
    
    levels = new bool [total_level]; //1 for exit
    set_selected_level();
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
    clips[SELECT].w = 45;
    clips[SELECT].h = 50;
    
//    clips[U_EXIT].x = 95;
//    clips[U_EXIT].y = 155;
//    clips[U_EXIT].w = 95;
//    clips[U_EXIT].h = 50;
//    
//    clips[S_EXIT].x = 190;
//    clips[S_EXIT].y = 155;
//    clips[S_EXIT].w = 95;
//    clips[S_EXIT].h = 50;
}

void LevelSelectScreen::set_selected_level(){
    for (int i = 0; i < total_level; i +=1) {
        levels[i] = false;
    }
    levels[selected_level] = true;
}

void LevelSelectScreen::handle_input(SDL_Event event){
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        
        if (dir == SDLK_UP){
            //up and down to add row. enly up and down can go to exit?
            selected_level = (selected_level + total_level - 5) % total_level ;
            set_selected_level();
        }else if(dir == SDLK_DOWN){
            selected_level = (selected_level + 5) % total_level ;
            set_selected_level();
        }else if(dir == SDLK_LEFT){
            selected_level = (selected_level + total_level- 1) % total_level;
            set_selected_level();
        }else if(dir == SDLK_RIGHT){
            selected_level = (selected_level + 1) % total_level;
            set_selected_level();
        }else if(dir == SDLK_RETURN){
            current_screen = LEVEL_SCREEN;
            LEVEL_PAUSE = false;
        }else if(dir == SDLK_ESCAPE){
            current_screen = MENU_SCREEN;
        }
    }
}

void LevelSelectScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    SDL_FillRect(screen , NULL , 0x000000);
    for (int i = 0; i < total_level; i += 1) {
        if(levels[i]) apply_surface((i %5) * 50 + 20,(i / 5)*50, tileSheet, screen, &clips[SELECT]);
        else apply_surface((i % 5) * 50+ 20,(i / 5) * 50, tileSheet, screen, &clips[UNSELECT]);
    }
    //add exit
//    if (selected_level == total_level) apply_surface(100, 200, tileSheet, screen, & clips[S_EXIT]);
//    else apply_surface(100, 200, tileSheet, screen, & clips[U_EXIT]);
    
}
