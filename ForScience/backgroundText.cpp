//
//  backgroundText.cpp
//  ForScience
//
//  Created by Yue on 10/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "backgroundText.h"
#include "constant.h"

BackGroundText::BackGroundText(int x, int y, std::string *list, int text_count){
    textlist = new Text* [text_count];
    this->text_count = text_count;
    for (int i = 0; i < text_count; i++) {
        textlist[i] = new Text(x , y+ 40*i, list[i], font);
    }
}

BackGroundText::~BackGroundText(){
    for (int i = 0; i < text_count; i++) {
        delete textlist[i];
    }
    delete [] textlist;
}

void BackGroundText::show(SDL_Surface * screen){
    for (int i = 0; i < text_count; i++) {
        textlist[i]->show(screen);
    }
}