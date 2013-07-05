//
//  text.cpp
//  ForScience
//
//  Created by Yue on 7/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "text.h"
#include "utility.h"

Text::Text(){
    
}

void Text::show(SDL_Surface *screen){
    apply_surface(x, y, NULL, screen);
}

void Text::set_text(std::string t){
    text = t;
}