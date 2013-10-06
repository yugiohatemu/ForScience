//
//  menuScreen.cpp
//  ForScience
//
//  Created by Yue on 8/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "menuScreen.h"
#include "utility.h"
#include "constant.h"
#include "screenController.h"
#include "levelSelectScreen.h"

MenuScreen::MenuScreen():Screen(){
    frame  = new int[TOTAL_STATE];
    frame[0] = 1;
    frame[1] = 0;
    //dirty now
    set_clip();
    state = START;
    instruction = new Text(0, 500, "Arrow key to switch option, press [Enter] to choose", font);
    //aound 40 per font height
}

MenuScreen::~MenuScreen(){
    delete [] frame;
    delete instruction;
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
    
    clips[U_EXIT].x = 300;
    clips[U_EXIT].y = 95;
    clips[U_EXIT].w = 95;
    clips[U_EXIT].h = 95;
    
    clips[S_EXIT].x = 400;
    clips[S_EXIT].y = 95;
    clips[S_EXIT].w = 95;
    clips[S_EXIT].h = 95;
    
}

void MenuScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    SDL_FillRect(screen , NULL , 0x000000);
    apply_surface(40, 50, menuSheet, screen, &clips[TITLE]);
    if (frame[0] == 1){
        apply_surface(250, 200, menuSheet, screen, &clips[S_START]);
        apply_surface(250, 300, menuSheet, screen, &clips[U_EXIT]);
    }else{
        apply_surface(250, 200, menuSheet, screen, &clips[U_START]);
        apply_surface(250, 300, menuSheet, screen, &clips[S_EXIT]);
    }
    instruction->show(screen);
}


void MenuScreen::handle_input(SDL_Event event){
    //arrow key and enter
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        
        if (dir == SDLK_UP){
            state = (state + 1) % TOTAL_STATE;
            if(frame[0] == 1) {
                frame[1] = 1;
                frame[0] = 0;
            }else{
                frame[0] = 1;
                frame[1] = 0;
            }
        }else if(dir == SDLK_DOWN){
            state = (state - 1) % TOTAL_STATE;
            if(frame[0] == 1) {
                frame[1] = 1;
                frame[0] = 0;
            }
        }else if(dir == SDLK_RETURN){
           
            if (state == START) {
                LevelSelectScreen * next = new LevelSelectScreen();
                ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
                root_controller->push_controller(next);
            }else if(state == EXIT){
                //ask the program to pause
                QUIT = true;
            }
           
        }
    }
    
}

void MenuScreen::animate(){
    
}