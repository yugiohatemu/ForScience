//
//  screen.h
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_screen_h
#define ForScience_screen_h

#include "SDL/SDL.h"

class Screen{
protected:
    Screen * root;
public:
    Screen(){};
    virtual ~Screen(){root = NULL;};
    virtual void handle_input(SDL_Event event){};
    virtual void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){};
    virtual void animate(){};
    void set_controller(Screen * s){
        root = s;
    }

    
};

#endif
