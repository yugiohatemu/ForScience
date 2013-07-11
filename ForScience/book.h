//
//  book.h
//  ForScience
//
//  Created by Yue on 7/10/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__book__
#define __ForScience__book__

#include "sprite.h"

class Book: public Sprite{
    enum CLIP{
        BOOK,
        TOTAL_CLIP
    };
    SDL_Rect clips[TOTAL_CLIP];
    enum  STATE{
        DROPED,
        PICKED,
    };
    STATE state = DROPED;
    void set_clip();
    SDL_Rect *stick_rect;
    
public:
    Book(int x, int y);
    ~Book();
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen);
    void animate();
    bool is_block();
    void set_stick_rect(SDL_Rect *sitck_rect);
};

#endif /* defined(__ForScience__book__) */
