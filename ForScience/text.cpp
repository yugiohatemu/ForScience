//
//  text.cpp
//  ForScience
//
//  Created by Yue on 7/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "text.h"
#include "utility.h"


Text::Text(int x, int y,std::string text, TTF_Font * font){
    this->x = x;
    this->y = y;
    this->text = text;
    this->font = font;
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    font_surface = TTF_RenderText_Solid(font, text.c_str(), color);
}

void Text::show(SDL_Surface *screen){
    apply_surface(x, y, font_surface, screen);
}

void Text::set_text(std::string text){
    if (this->text.compare(text) != 0) {
        this->text = text;
        font_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }
}

Text::~Text(){
    font = NULL;
    SDL_FreeSurface(font_surface);
}