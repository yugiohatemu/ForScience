//
//  text.h
//  ForScience
//
//  Created by Yue on 7/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__text__
#define __ForScience__text__

#include "SDL/SDL.h"
#include <string>

class Text{
    std::string text;
    int x, y;
public:
    Text();
    void set_text(std::string t);
    void show(SDL_Surface * screen);
};

#endif /* defined(__ForScience__text__) */
