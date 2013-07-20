//
//  animation.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "animation.h"

Animation::Animation(int total_frame, int * frames, bool recycle){
    this->total_frame = total_frame;
    this->frames = frames;
    this->recycle = recycle;
    
    current_frame = 0;
    is_reversing = false;
}

Animation::~Animation(){
    delete [] frames;
}


int Animation::get_current_frame(){
    
    if (!is_reversing) {
        current_frame += 1;
        if (current_frame >= total_frame - 1) current_frame = total_frame - 1;
        
    }else{ //go reverse
        current_frame -= 1;
        if (current_frame < 0) current_frame = 0;

    }
    if (is_anime_done() && recycle) reverse_frame();
    
    return current_frame;
}

void Animation::reverse_frame(){
    is_reversing = !is_reversing;
}

bool Animation::is_anime_done(){
    if (is_reversing && current_frame == total_frame - 1) return true;
    else if(!is_reversing && current_frame == 0) return true;
    return false;
}
