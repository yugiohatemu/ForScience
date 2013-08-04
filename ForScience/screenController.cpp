//
//  screenController.cpp
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "screenController.h"
#include <iostream>

ScreenController::ScreenController(Screen * s):Screen(){
    root.push(s);
    top = root.top();
    top->set_controller(this);
}

ScreenController::~ScreenController(){
    //pop everything
    while (!root.empty()) {
        root.pop();
    }
    top = NULL;
}

void ScreenController::push_controller(Screen * next){
    root.push(next);
    next->set_controller(this);
    top = next;
}

void ScreenController::pop_controller(){
    if (root.size() > 1) {
        root.pop();
        top = root.top();
    }
    //do not allow root to be poped
    //deallocated automatically
}


void ScreenController::handle_input(SDL_Event event){
    if (top) top->handle_input(event);
}

void ScreenController::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    if (top)top->show(camera, tileSheet, screen);
}

void ScreenController::animate(){
    if (top) top->animate();
}