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

PauseScreen::PauseScreen(Screen * level_select):Screen(){
    set_clip();
    
    instruction = new Text(0, 500, "Press [Enter] to go to select level, [ESC] to unpause", font);
    instruction->backColor = COLOR_BLACK;
    instruction->textColor = COLOR_WHITE;
    instruction->render();
    
    selectLevel = level_select;
}

PauseScreen::~PauseScreen(){
    delete instruction;
    selectLevel = NULL;
}

void PauseScreen::set_clip(){
    clips[PAUSE].x = 365;
    clips[PAUSE].y = 200;
    clips[PAUSE].h = 50;
    clips[PAUSE].w = 150;
}

void PauseScreen::handle_input(SDL_Event event){
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        if (dir == SDLK_RETURN) {
            ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->pop_controller_to(selectLevel);
        }else if(dir == SDLK_ESCAPE){
             ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->pop_controller();
        }
    }
}

void PauseScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    apply_surface(100, 200, menuSheet, screen, &clips[PAUSE]);
    instruction->show(screen);
}

void PauseScreen::animate(){
    
}
