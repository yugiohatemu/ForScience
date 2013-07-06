//
//  timer.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_timer_h
#define ForScience_timer_h

//The timer
class Timer{
private:

    int startTicks;
    int pausedTicks;
    
    bool paused;
    bool started;
    
public:
    
    Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};


#endif
