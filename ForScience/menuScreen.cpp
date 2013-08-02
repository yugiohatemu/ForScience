//
//  menuScreen.cpp
//  ForScience
//
//  Created by Yue on 8/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "menuScreen.h"
#include "utility.h"

MenuScreen::MenuScreen(){
    frame = S_START;
    set_clip();
}

MenuScreen::~MenuScreen(){
    
}

void MenuScreen::set_clip(){
    clips[TITLE].x = 0;
    clips[TITLE].y = 0;
    clips[TITLE].h = 85;
    clips[TITLE].w = 555;
    
    clips[U_START].x = 0;
    clips[U_START].y = 95;
    clips[U_START].w = 150;
    clips[U_START].h = 60;
    
    clips[S_START].x = 150;
    clips[S_START].y = 95;
    clips[S_START].w = 150;
    clips[S_START].h = 60;
    
    clips[U_OPTION].x = 300;
    clips[U_OPTION].y = 95;
    clips[U_OPTION].w = 95;
    clips[U_OPTION].h = 95;
    
    clips[S_OPTION].x = 395;
    clips[S_OPTION].y = 95;
    clips[S_OPTION].w = 95;
    clips[S_OPTION].h = 95;
    
}

void MenuScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    apply_surface(40, 50, tileSheet, screen, &clips[TITLE]);
    apply_surface(250, 200, tileSheet, screen, &clips[frame]);
    apply_surface(250, 300, tileSheet, screen, &clips[U_OPTION]);
}

void MenuScreen::handle_input(SDL_Event event){
    //arrow key and enter
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;

        if (dir == SDLK_UP){
            
        }else if(dir == SDLK_DOWN){
            
        }else if(dir == SDLK_RETURN){
            
        }
    }
    
}