//
//  text.cpp
//  ForScience
//
//  Created by Yue on 7/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "text.h"
#include "utility.h"
//TODO: still buggy, the surface is not cleared...
SDL_Color black = {0,0,0};

Text::Text(int x, int y,std::string text, TTF_Font * font){
    this->x = x;
    this->y = y;
    this->text = text;
    this->font = font;
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    font_surface = TTF_RenderText_Shaded(font, text.c_str(), color, black);
}

void Text::show(SDL_Surface *screen){
    apply_surface(x, y, font_surface, screen);
}

void Text::set_text(std::string text){
    if (this->text.compare(text) != 0) {
        this->text = text;
        SDL_FreeSurface(font_surface);
        font_surface = TTF_RenderText_Shaded(font, text.c_str(), color, black);
    }
}

Text::~Text(){
    font = NULL;
    SDL_FreeSurface(font_surface);
}