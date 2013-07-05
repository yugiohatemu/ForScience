//
//  quest.cpp
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "quest.h"

Quest::Quest(int quest_line){
    done = false;
    this->quest_line = quest_line;
}


Quest::~Quest(){
    
}

void Quest::set_done(bool done){
    this->done = done;
}

bool Quest::is_done(){
    return done;
}

int Quest::get_quest_line(){
    return quest_line;
}
