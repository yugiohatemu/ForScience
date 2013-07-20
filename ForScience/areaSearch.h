//
//  areaSearch.h
//  ForScience
//
//  Created by Yue on 7/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__areaSearch__
#define __ForScience__areaSearch__

#include "SDL/SDL.h"

class AreaSearch{
    //use an sdl_rect is better
    SDL_Rect area;
    SDL_Rect area_left;
public:
    
    AreaSearch(int x, int y, int w, int h);
    ~AreaSearch();
    SDL_Rect get_area();
    bool is_search_start(SDL_Rect rect);
    bool is_search_end(SDL_Rect rect);
    bool try_search(SDL_Rect rect);
    void reset();
};

#endif /* defined(__ForScience__areaSearch__) */
