//
//  quest.h
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__quest__
#define __ForScience__quest__

class Quest{
    bool done;
    int quest_line;
public:
    Quest(int quest_line);
    ~Quest();
    void set_done(bool done);
    bool is_done();
    int get_quest_line();
};


#endif /* defined(__ForScience__quest__) */
