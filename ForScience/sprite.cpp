//
//  sprite.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "sprite.h"
#include "utility.h"
#include "constant.h"

Sprite::Sprite(){
    //Initialize the offsets
    box.x = 0;
    box.y = 0;
    box.w = DOT_WIDTH ;
    box.h = DOT_HEIGHT;
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Sprite::handle_input(SDL_Event event){
    //If a key was pressed
    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += DOT_HEIGHT  / 2; break;
            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += DOT_WIDTH  / 2; break;
            default: break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_UP: yVel += DOT_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= DOT_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += DOT_WIDTH  / 2; break;
            case SDLK_RIGHT: xVel -= DOT_WIDTH  / 2; break;
            default: break;
        }
    }
}

void Sprite::move(){
}

/*void Sprite::move( Tile *tiles[] ){
    //Move the Sprite left or right
    box.x += xVel;
    
    //If the Sprite went too far to the left or right or touched a wall
    if( ( box.x < 0 ) || ( box.x + Sprite_WIDTH > LEVEL_WIDTH ) || touches_wall( box, tiles ) )
    {
        //move back
        box.x -= xVel;
    }
    
    //Move the Sprite up or down
    box.y += yVel;
    
    //If the Sprite went too far up or down or touched a wall
    if( ( box.y < 0 ) || ( box.y + Sprite_HEIGHT > LEVEL_HEIGHT ) || touches_wall( box, tiles ) )
    {
        //move back
        box.y -= yVel;
    }
}*/

void Sprite::show(SDL_Rect camera,SDL_Surface * dot, SDL_Surface * screen){
    //Show the Sprite
    apply_surface( box.x - camera.x, box.y - camera.y, dot, screen );
}

//void Sprite::set_camera(SDL_Rect camera)
//{
//    //Center the camera over the Sprite
//    camera.x = ( box.x + DOT_WIDTH  / 2 ) - DOT_WIDTH  / 2;
//    camera.y = ( box.y + box.y / 2 ) - box.y / 2;
//    
//    //Keep the camera in bounds.
//    if( camera.x < 0 ) camera.x = 0;
//    if( camera.y < 0 ) camera.y = 0;
//    if( camera.x > LEVEL_WIDTH - camera.w ) camera.x = LEVEL_WIDTH - camera.w;
//    if( camera.y > LEVEL_HEIGHT - camera.h ) camera.y = LEVEL_HEIGHT - camera.h;
    
//}
