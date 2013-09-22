//
//  pauseScreen.cpp
//  ForScience
//
//  Created by Yue on 9/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "pauseScreen.h"
#include "utility.h"
#include "screenController.h"
#include "constant.h"

PauseScreen::PauseScreen(Screen * level_select){
    set_clip();
}

PauseScreen::~PauseScreen(){
    
}

void PauseScreen::set_clip(){
    
}

void PauseScreen::handle_input(SDL_Event event){
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        if (dir == SDLK_RETURN) {
             ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->pop_controller();
        }else if(dir == SDLK_ESCAPE){
             ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->pop_controller();
        }
    }
}

void PauseScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    
}

void PauseScreen::animate(){
    
}
