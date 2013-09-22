//
//  screenController.h
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__screenController__
#define __ForScience__screenController__

#include <stack>
#include "screen.h"
#include "SDL/SDL.h"

class ScreenController:public Screen{
    std::stack<Screen *> root;
    Screen * top;
public:
    ScreenController(Screen * s);
    ~ScreenController();
    void push_controller(Screen * next);
    void pop_controller();
    void pop_controller_to(Screen * s);
    void handle_input(SDL_Event event);
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    void animate();
};

#endif /* defined(__ForScience__screenController__) */
