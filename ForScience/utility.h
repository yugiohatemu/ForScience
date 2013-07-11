//
//  utility.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//  Used to do calculation 

#ifndef __ForScience__utility__
#define __ForScience__utility__
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include <string>

enum Interaction{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,
    SPACE,
    ENTER,
};

SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
bool check_collision( SDL_Rect A, SDL_Rect B );
SDL_Rect merge_rect(SDL_Rect A, SDL_Rect B);
void debug(std::string s);
int collide_position(SDL_Rect A, SDL_Rect B); // not done;

#endif /* defined(__ForScience__utility__) */
