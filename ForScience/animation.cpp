//
//  animation.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "animation.h"

Animation::Animation(int total_frame, int * frames, bool reverse, bool recycle){
    this->total_frame = total_frame;
    this->frames = frames;
    this->recycle = recycle;
    this->reverse = reverse;
    
    current_frame = 0;
    is_reversing = false;
}

Animation::~Animation(){
    delete [] frames;
}

void Animation::next(){
    
}

int Animation::get_current_frame(){
    if (!is_reversing) {
        current_frame += 1;
        if (current_frame >= total_frame - 1) { //end of it, ignore recycle for now
            current_frame = total_frame - 1;
        }
    }else{ //go reverse
        current_frame -= 1;
        if (current_frame < 0) {
            current_frame = 0;
            is_reversing = false;
        }
    }
    return current_frame;
}

void Animation::reverse_frame(){
    is_reversing = true;
}