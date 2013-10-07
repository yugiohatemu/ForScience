//
//  backgroundText.h
//  ForScience
//
//  Created by Yue on 10/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__backgroundText__
#define __ForScience__backgroundText__

#include "text.h"

class BackGroundText{
	Text ** textlist;
	int text_count;
public:
    int x, y;
	BackGroundText(int x, int y, std::string * list, int text_count);
	~BackGroundText();
	void show(SDL_Surface * screen);
	
};

#endif /* defined(__ForScience__backgroundText__) */
