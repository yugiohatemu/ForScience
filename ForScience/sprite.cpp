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
#include <iostream>

Sprite::Sprite(){
    //Initialize the offsets
    box.x = 4*TILE_WIDTH;
    box.y = LEVEL_HEIGHT - TILE_HEIGHT - STICK_HEIGHT;
    box.w = STICK_WIDTH ;
    box.h = STICK_HEIGHT;
    
    clip_tile();
    
    frame = 0;
    
}


void Sprite::clip_tile(){
    
    
    clips[STAND].x = 0;
    clips[STAND].y = 0;
    clips[STAND].w = STICK_WIDTH;
    clips[STAND].h = STICK_HEIGHT;
    
    //Right
    clips[WALK_R0].x = clips[STAND].x + STICK_WIDTH;
    clips[WALK_R0].y = 0;
    clips[WALK_R0].w = STICK_WIDTH;
    clips[WALK_R0].h =STICK_HEIGHT;
    
    clips[WALK_R1].x = clips[WALK_R0].x + STICK_WIDTH ;
    clips[WALK_R1].y = 0;
    clips[WALK_R1].w =STICK_WIDTH;
    clips[WALK_R1].h =STICK_HEIGHT;
    
    clips[WALK_R2].x = clips[WALK_R1].x + STICK_WIDTH;
    clips[WALK_R2].y = 0;
    clips[WALK_R2].w = STICK_WIDTH;
    clips[WALK_R2].h = STICK_HEIGHT;
    
    clips[WALK_R3] = clips[WALK_R1]; //R3 = R1
    
    //Left
    clips[WALK_L0].x = clips[WALK_R2].x + STICK_WIDTH ;
    clips[WALK_L0].y = 0;
    clips[WALK_L0].w = STICK_WIDTH;
    clips[WALK_L0].h = STICK_HEIGHT;
    
    clips[WALK_L1].x = clips[WALK_L0].x+ STICK_WIDTH ;
    clips[WALK_L1].y = 0;
    clips[WALK_L1].w = STICK_WIDTH;
    clips[WALK_L1].h = STICK_HEIGHT;
    
    clips[WALK_L2].x = clips[WALK_L1].x + STICK_WIDTH ;
    clips[WALK_L2].y = 0;
    clips[WALK_L2].w = STICK_WIDTH;
    clips[WALK_L2].h = STICK_HEIGHT;
    
    clips[WALK_L3] = clips[WALK_L1];
    
    
}

void Sprite::handle_input(SDL_Event event, Level * level){
    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_RIGHT:
                level->move_on_level(box, SDLK_RIGHT, 20);
                frame += 1;
                if (frame < WALK_R0) {
                    frame = WALK_R0;
                }
                if (frame > WALK_R3) {
                    frame = WALK_R0;
                }
                break;
            case SDLK_LEFT:
                level->move_on_level(box, SDLK_LEFT, 20);
                frame += 1;
                if (frame < WALK_L0) { //stand or run right
                    frame = WALK_L0;
                }
                if (frame > WALK_L3) {
                    frame = WALK_L0;
                }
                break;
            case SDLK_UP:
                level->move_on_level(box, SDLK_UP, 20);
                break;
            case SDLK_DOWN:
                level->move_on_level(box, SDLK_DOWN, 20);
                break;
            default: break;
        }
    }else if(event.type == SDL_KEYUP){
        //return to stand
        frame = STAND;
    }
}


void Sprite::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}


//Clear the tile sheet that is being used
Sprite::~Sprite(){
   
}

SDL_Rect Sprite::get_rect(){
    return box;
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
