//
//  utility.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <algorithm>
#include <iostream>

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
//    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    return loadedImage;
    //If the image loaded
//    if( loadedImage != NULL )
//    {
//        //Create an optimized surface
//        optimizedImage = SDL_DisplayFormat( loadedImage );
//        
//        //Free the old surface
//        SDL_FreeSurface( loadedImage );
//        
//        //If the surface was optimized
//        if( optimizedImage != NULL )
//        {
//            //Color key surface
//            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
//        }
//    }
    
    //Return the optimized surface
//    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip  ){
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool check_collision( SDL_Rect A, SDL_Rect B ){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
        return false;
    
    //If none of the sides from A are outside B
    return true;
}

//merge to rect together
SDL_Rect merge_rect(SDL_Rect A, SDL_Rect B){
    SDL_Rect rect;
    rect.x = std::min(A.x,B.x);
    rect.y = std::min(A.y,B.y);
    rect.w = std::max(A.x + A.w - B.x, B.x + B.w - A.x);
    rect.h = std::max(A.y + A.h - B.y, B.y + B.h - A.y);
    return rect;
}

int collide_position(SDL_Rect A, SDL_Rect B){ //related to A
    if (!check_collision(A, B)) {
        return -1;
    }
    //check for center
    int center_A_x = A.x + A.w/2;
    int center_A_y = A.y + A.h/2;
    int center_B_x = B.x + B.w/2;
    int center_B_y = B.y + B.h/2;
    if (center_B_x < center_A_x) {
        if (center_B_y < A.y) return LEFT_UP;
        else if(center_B_y < A.y + A.h) return LEFT;
        else return LEFT_DOWN;
    }
    return -1;
}

//if A is on ? side of B
bool is_rect_on_side(int dir ,SDL_Rect A, SDL_Rect B){
    if (check_collision(A, B)) return true;
    
    if(dir == SDLK_RIGHT) return A.x > B.x + B.w;
    else if(dir == SDLK_LEFT) return A.x + A.w < B.x;
    
    return false;
}

bool is_rect_valid(SDL_Rect A){
    //the first 2 might not matter
    return A.x >= 0 && A.y >= 0 && A.w > 0 && A.h > 0;
}

//A is the rect that is substracted
SDL_Rect substract_rect(SDL_Rect A, SDL_Rect B){
    SDL_Rect rect = A;
    //A is on the rigth side of B
    if (check_collision(A, B)) {
        if (A.x + A.w >= B.x) {
            //dirty overflow
            if (A.x > B.x) rect.w = 0;
            else rect.w = B.x - A.x;
        }else if(A.x >= B.x + B.w){
            rect.x = B.x + B.w;
            if (A.w + A.x < B.x + B.w) rect.w = 0;
            else rect.w = A.w + A.x - B.x - B.w;
//            debug("D");
        }
    }
    
    return rect;
}

//if use the y to judge, need to redefine area
bool is_rect_inside(SDL_Rect A, SDL_Rect B){
    return A.x >= B.x && A.x + A.w <= B.x + B.w;
}

void debug(std::string s){
    std::cout<<s<<std::endl;
}

