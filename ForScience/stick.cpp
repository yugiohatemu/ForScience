//
//  Stick.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stick.h"
#include "utility.h"
#include "constant.h"
#include <iostream>

Stick::Stick(){
    //Initialize the offsets
    box.x = 4*TILE_WIDTH;
    box.y = LEVEL_HEIGHT - TILE_HEIGHT - STICK_HEIGHT;
    box.w = STICK_WIDTH ;
    box.h = STICK_HEIGHT;
    
    clip_tile();
    
    frame = 0;
    quest = NULL;
    active = false;
}


//Clear the tile sheet that is being used
Stick::~Stick(){
    quest = NULL;
}

void Stick::set_pos(int x, int y){
    box.x = x;
    box.y = y;
}

void Stick::set_active(bool active){
    this->active = active;
}

void Stick::clip_tile(){
    //In active
    clips[I_STAND].x = 0;
    clips[I_STAND].w = STICK_WIDTH;
   
    //Right
    clips[I_WALK_R0].x = clips[I_STAND].x + STICK_WIDTH;
    clips[I_WALK_R0].w = STICK_WIDTH;
    
    clips[I_WALK_R1].x = clips[I_WALK_R0].x + STICK_WIDTH ;
    clips[I_WALK_R1].w =STICK_WIDTH;
    
    clips[I_WALK_R2].x = clips[I_WALK_R1].x + STICK_WIDTH;
    clips[I_WALK_R2].w = STICK_WIDTH;
    
    clips[I_WALK_R3] = clips[I_WALK_R1]; //R3 = R1
    
    //Left
    clips[I_WALK_L0].x = clips[I_WALK_R2].x + STICK_WIDTH ;
    clips[I_WALK_L0].w = STICK_WIDTH;
    
    clips[I_WALK_L1].x = clips[I_WALK_L0].x+ STICK_WIDTH ;
    clips[I_WALK_L1].w = STICK_WIDTH;
   
    clips[I_WALK_L2].x = clips[I_WALK_L1].x + STICK_WIDTH ;
    clips[I_WALK_L2].w = STICK_WIDTH;
       
    clips[I_WALK_L3] = clips[I_WALK_L1];
    //Jump
    clips[I_JUMP].x = 7 * STICK_WIDTH;
    clips[I_JUMP].w = 60;
    
    for (int i = 0; i <= I_JUMP; i += 1) {
        clips[i].y = 0;
        clips[i].h = STICK_HEIGHT;
    }
    
    for (int i = A_STAND;i <= A_JUMP ;i +=1) {
        clips[i] = clips[i - A_STAND];
        clips[i].y = STICK_HEIGHT;
    }
}

void Stick::handle_input(SDL_Event event, Level * level){
    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_RIGHT:
                level->move_on_level(box, SDLK_RIGHT, 20);
                frame += 1;
                if (frame < I_WALK_R0) {
                    frame = I_WALK_R0;
                }
                if (frame > I_WALK_R3) {
                    frame = I_WALK_R0;
                }
                break;
            case SDLK_LEFT:
                level->move_on_level(box, SDLK_LEFT, 20);
                frame += 1;
                if (frame < I_WALK_L0) { //stand or run right
                    frame = I_WALK_L0;
                }
                if (frame > I_WALK_L3) {
                    frame = I_WALK_L0;
                }
                break;
            case SDLK_UP:
                level->move_on_level(box, SDLK_UP, 20);
                break;
            case SDLK_DOWN:
                level->move_on_level(box, SDLK_DOWN, 20);
                break;
            case SDLK_SPACE:
                frame = I_JUMP;
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
        frame = I_STAND;
    }
}


void Stick::set_quest(Quest * quest){
    this->quest = quest;
}
void Stick::process_quest(){
    if (quest != NULL) {
        
    }
}


void Stick::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}




SDL_Rect Stick::get_rect(){
    return box;
}

//void Stick::set_camera(SDL_Rect camera)
//{
//    //Center the camera over the Stick
//    camera.x = ( box.x + DOT_WIDTH  / 2 ) - DOT_WIDTH  / 2;
//    camera.y = ( box.y + box.y / 2 ) - box.y / 2;
//    
//    //Keep the camera in bounds.
//    if( camera.x < 0 ) camera.x = 0;
//    if( camera.y < 0 ) camera.y = 0;
//    if( camera.x > LEVEL_WIDTH - camera.w ) camera.x = LEVEL_WIDTH - camera.w;
//    if( camera.y > LEVEL_HEIGHT - camera.h ) camera.y = LEVEL_HEIGHT - camera.h;
    
//}