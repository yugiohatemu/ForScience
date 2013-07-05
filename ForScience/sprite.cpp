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
    quest = NULL;
}

//Clear the tile sheet that is being used
Sprite::~Sprite(){
    quest = NULL;
}

void Sprite::clip_tile(){
    
    clips[STAND].x = 0;
    clips[STAND].w = STICK_WIDTH;
   
    //Right
    clips[WALK_R0].x = clips[STAND].x + STICK_WIDTH;
    clips[WALK_R0].w = STICK_WIDTH;
    
    clips[WALK_R1].x = clips[WALK_R0].x + STICK_WIDTH ;
    clips[WALK_R1].w =STICK_WIDTH;
    
    clips[WALK_R2].x = clips[WALK_R1].x + STICK_WIDTH;
    clips[WALK_R2].w = STICK_WIDTH;
    
    clips[WALK_R3] = clips[WALK_R1]; //R3 = R1
    
    //Left
    clips[WALK_L0].x = clips[WALK_R2].x + STICK_WIDTH ;
    clips[WALK_L0].w = STICK_WIDTH;
    
    clips[WALK_L1].x = clips[WALK_L0].x+ STICK_WIDTH ;
    clips[WALK_L1].w = STICK_WIDTH;
   
    clips[WALK_L2].x = clips[WALK_L1].x + STICK_WIDTH ;
    clips[WALK_L2].w = STICK_WIDTH;
       
    clips[WALK_L3] = clips[WALK_L1];
    //Jump
    clips[JUMP].x = 7 * STICK_WIDTH;
    clips[JUMP].w = 60;
    
    for (int i = 0; i < TOTAL_CLIP; i += 1) {
        clips[i].y = 0;
        clips[i].h = STICK_HEIGHT;
    }
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
            case SDLK_SPACE:
                frame = JUMP;
                break;
            default: break;
        }
        if (quest != NULL) {
            if(event.key.keysym.sym == SDLK_SPACE){
                quest->set_done(true);
            }
        }
        
        
    }else if(event.type == SDL_KEYUP){
        //return to stand
        frame = STAND;
    }
}


void Sprite::set_quest(Quest * quest){
    this->quest = quest;
}
void Sprite::process_quest(){
    if (quest != NULL) {
        
    }
}


void Sprite::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
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
