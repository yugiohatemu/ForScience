//
//  mission.h
//  ForScience
//
//  Created by Yue on 7/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__mission__
#define __ForScience__mission__

#include <vector>

class Mission{
    
    std::vector<int> dir_list;
    int x, y;
    bool check;
    bool active;
public:
    Mission(int dir, int x, int y);
    ~Mission();
    
    void reset(int dir, int x, int y);
    void update_status(int dir, int x, int y);
    void check_in();
    bool is_active();
};

#endif /* defined(__ForScience__mission__) */
