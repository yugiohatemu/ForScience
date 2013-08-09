//
//  EndScreen.cpp
//  ForScience
//
//  Created by Yue on 8/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "endScreen.h"
#include "utility.h"
#include "screenController.h"

EndScreen::EndScreen(bool win):Screen(){
    this->win = win;
    
    //level complete
    //and press center to continue
    
}

EndScreen::~EndScreen(){
    
}

void EndScreen::set_clip(){
    clips[YOU_WIN].x = 0;
    clips[YOU_WIN].y = 205;
    clips[YOU_WIN].h = 45;
    clips[YOU_WIN].w = 180;
    
    clips[YOU_LOSE].x = 180;
    clips[YOU_LOSE].y = 205;
    clips[YOU_LOSE].h = 45;
    clips[YOU_LOSE].w = 185;
}

void EndScreen::handle_input(SDL_Event event){
    //press enter
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        if (dir == SDLK_RETURN) {
           
            
        }
    }

}

void EndScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    if (win) apply_surface(100, 300, tileSheet, screen, &clips[YOU_WIN]);
    else apply_surface(100, 300, tileSheet, screen, &clips[YOU_LOSE]);
}

void EndScreen::animate(){
    
}
