//
//  areaSearch.cpp
//  ForScience
//
//  Created by Yue on 7/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "areaSearch.h"
#include "utility.h"

AreaSearch::AreaSearch(int x, int y, int w, int h){
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;
    
    area_left = area;
}

AreaSearch::~AreaSearch(){
    
}

SDL_Rect AreaSearch::get_area(){
    return area;
}


void AreaSearch::reset(){
    area_left = area;
}

bool AreaSearch::is_search_start(SDL_Rect rect){
    if (check_collision(rect, area)){
        area_left = substract_rect(area_left, rect);
        return true;
    }else
        return false;
}

//if after substraction, the rect is no longer valid, then we finishing all the search area
bool AreaSearch::is_search_end(SDL_Rect rect){
    area_left = substract_rect(area_left, rect);
    return  !is_rect_valid(area_left);
}

bool AreaSearch::try_search(SDL_Rect rect){
    area_left = substract_rect(area_left, rect);
    return  !is_rect_valid(area_left);
}

