//
//  screenController.cpp
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "screenController.h"

ScreenController::ScreenController(){
    current = NULL;
}

ScreenController::~ScreenController(){
    //pop everything
    while (!root.empty()) {
        root.pop();
    }
}

void ScreenController::push_controller(Screen * next){
    root.push(next);
    current = next;
}

void ScreenController::pop_controller(){
    root.pop();
    current = root.top();
    //deallocated automatically
}


void ScreenController::handle_input(SDL_Event event){
    current->handle_input(event);
}

void ScreenController::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    current->show(camera, tileSheet, screen);
}

void ScreenController::animate(){
    current->animate();
}