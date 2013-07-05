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

void debug(std::string s){
    std::cout<<s<<std::endl;
}

