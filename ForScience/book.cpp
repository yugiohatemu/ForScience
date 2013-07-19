//
//  book.cpp
//  ForScience
//
//  Created by Yue on 7/10/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "book.h"
#include "utility.h"
#include <iostream>

Book::Book(int x, int y):Sprite(x,y){
    box.w = 40;
    box.h = 40;
    set_clip();
    attr = STICK_ACTIVE;
    frame = BOOK;
    stick_rect = NULL;
    state = DROPED;
}

Book::~Book(){
    stick_rect = NULL;
}

void Book::set_clip(){
    clips[BOOK].x = 160;
    clips[BOOK].y = 160;
    clips[BOOK].w = 40;
    clips[BOOK].h = 40;
}

void Book::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    if (stick_rect) {
        box.x = stick_rect->x + stick_rect->w/2;
        box.y = stick_rect->y + stick_rect->h/2;
    }
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

void Book::animate(){
    //else do nothing
}

bool Book::is_block(){
    return false;
}

//two state, one states, the books position will go with the stick
//another state just stay on ground
void Book::set_stick_rect(SDL_Rect *rect){
  
    if (rect) {
        box.x = rect->x + rect->w/2;
        box.y = rect->y + rect->h/2;
    }else{
        box.x = stick_rect->x + stick_rect->w/2;
        box.y = stick_rect->y + stick_rect->h;
    }
    stick_rect = rect;
}