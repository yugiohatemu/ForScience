//
//  book.cpp
//  ForScience
//
//  Created by Yue on 7/10/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "book.h"
#include "utility.h"


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
    stick_rect= NULL;
}

void Book::set_clip(){
    clips[BOOK].x = 160;
    clips[BOOK].y = 160;
    clips[BOOK].w = 40;
    clips[BOOK].h = 40;
}

void Book::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
     apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}

void Book::animate(){
    if (state == PICKED) {
        box.x = stick_rect->x + stick_rect->w/2;
        box.y = stick_rect->y + stick_rect->h/2;
    }//else do nothing
}

bool Book::is_block(){
    return false;
}

//two state, one states, the books position will go with the stick
//another state just stay on ground
void Book::set_stick_rect(SDL_Rect *sitck_rect){
    if (stick_rect == this->stick_rect) {
        debug("c");
        return ;
    }
    //can use this for interchanging object between sticks latter
    if (this->stick_rect == NULL && state == DROPED) {
        state = PICKED;
        box.x = stick_rect->x + stick_rect->w/2;
        box.y = stick_rect->y + stick_rect->h/2;
        debug("b");
    }else{ //not nulled
        box.x = stick_rect->x + stick_rect->w/2;
        box.y = stick_rect->y + stick_rect->h;
    }
    this->stick_rect = stick_rect;
}