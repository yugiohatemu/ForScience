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
#include "SDL_ttf/SDL_ttf.h"

class Text{
    std::string text;
    int x, y;
    SDL_Color color;
    TTF_Font * font;
    SDL_Surface * font_surface;
public:
    Text(int x, int y, std::string text, TTF_Font * font);
    void set_text(std::string t);
    void show(SDL_Surface * screen);
    ~Text();
};

#endif /* defined(__ForScience__text__) */
