//
//  animation.h
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__animation__
#define __ForScience__animation__

class Animation{
    int * frames;
    int total_frame;
    int current_frame;
    bool recycle;
    bool is_reversing;
public:
    Animation(int total_frame, int * frames, bool recycle);
    ~Animation();
    int get_current_frame();
    void reverse_frame();
    bool is_anime_done();
};

#endif /* defined(__ForScience__animation__) */
