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
#include "constant.h"


EndScreen::EndScreen(bool win, Screen * level_select):Screen(){
    this->win = win;
    this->level_select = level_select;
    set_clip();
    //level complete
    //and press center to continue
    instruction = new Text(0, 500, "Press [Enter] to redo level, [ESC] to menu", font);
    instruction->backColor = COLOR_BLACK;
    instruction->textColor = COLOR_WHITE;
    instruction->render();
}

EndScreen::~EndScreen(){
    delete instruction;
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
           //add option later
            if (true) {
                ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
                root_controller->pop_controller_to(level_select);
            }else{
                ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
                root_controller->pop_controller();
            }
        }
    }

}


void EndScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
//    SDL_FillRect(screen , NULL , 0x000000);
    
    if (win) apply_surface(100, 100, menuSheet, screen, &clips[YOU_WIN]);
    else apply_surface(100, 100, menuSheet, screen, &clips[YOU_LOSE]);
    
    instruction->show(screen);
}

void EndScreen::animate(){
    
}
