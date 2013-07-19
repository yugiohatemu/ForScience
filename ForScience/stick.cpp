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
#include "book.h"
Stick::Stick(Level * level){
    //Initialize the offsets
    box.x = 4*TILE_WIDTH;
    box.y = LEVEL_HEIGHT - TILE_HEIGHT - STICK_HEIGHT;
    box.w = STICK_WIDTH ;
    box.h = STICK_HEIGHT;
    
    clip_tile();
    
    frame = I_STAND;
    quest = NULL;
    this->level = level;
    active = false;
    life = 1;
    state = WALK;
    item = NULL;
}


//Clear the tile sheet that is being used
Stick::~Stick(){
    if (quest != NULL) {
        delete quest;
    }
    quest = NULL;
    level = NULL;
    item  = NULL;
}

void Stick::set_pos(int x, int y){
    box.x = x;
    box.y = y;
}

void Stick::set_active(bool active){
//    if (life != 0) {
        this->active = active;
        if (active) {
            frame = A_STAND;
        }else{
            frame = I_STAND;
        }
//    }
}


SDL_Rect Stick::get_rect(){
    return box;
}



void Stick::get_quest(Quest * quest){
    this->quest = quest;
}
bool Stick::has_quest(){
    return quest != NULL;
}

bool Stick::is_quest_done(){
    if (quest != NULL) {
        return quest->is_done();
    }else{
        return true;
    }
}

void Stick::delete_quest(){
    delete quest;
    quest = NULL;
}

bool Stick::is_autopilot(){
    return !active;
}

void Stick::minus_life(){
    life -= 1;
    if (life < 0) {
        life = 0;
       //active = false;
    }
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
    
    //climb
    clips[I_CLIMB0].x = clips[I_JUMP].x + clips[I_JUMP].w;
    clips[I_CLIMB0].w = STICK_WIDTH;
    
    clips[I_CLIMB1].x = clips[I_CLIMB0].x + STICK_WIDTH;
    clips[I_CLIMB1].w = STICK_WIDTH;
    
    //crawl
    clips[I_CRAWL0].x = clips[I_CLIMB1].x + STICK_WIDTH;
    clips[I_CRAWL0].y = 0;
    clips[I_CRAWL0].w = STICK_HEIGHT;
    clips[I_CRAWL0].h = STICK_WIDTH;
    
    clips[I_CRAWL1] = clips[I_CRAWL0];
    clips[I_CRAWL1].y = 40;
    
    clips[I_CRAWL2].x = clips[I_CRAWL0].x + clips[I_CRAWL0].w;
    clips[I_CRAWL2].y = 0;
    clips[I_CRAWL2].w = 80;
    clips[I_CRAWL2].h = 80;
    
    clips[I_CRAWL3].x = clips[I_CRAWL2].x + clips[I_CRAWL2].w;
    clips[I_CRAWL3].y = 0;
    clips[I_CRAWL3].w = 80;
    clips[I_CRAWL3].h = 120;
    
    clips[I_FALL].x = clips[I_CRAWL3].x + clips[I_CRAWL3].w;
    clips[I_FALL].y = 0;
    clips[I_FALL].w = STICK_WIDTH;
    clips[I_FALL].h = STICK_HEIGHT;
    
    for (int i = 0; i <= I_CLIMB1; i += 1) {
        clips[i].y = 0;
        clips[i].h = STICK_HEIGHT;
    }
    
    //Active sprite clips
    for (int i = A_STAND;i < TOTAL_CLIP ;i +=1) {
        clips[i] = clips[i - A_STAND];
        clips[i].y = STICK_HEIGHT + clips[i - A_STAND].y;
    }
}

void Stick::handle_input(SDL_Event event){
    //calculate the diff between box_copy and box
    //apply the change
    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_RIGHT:
                if (state == CRAWL ) {
                    if(level->crawl_tunnel(box, SDLK_RIGHT, 15)){
                        frame += 1;
                        if (active) {
                            if (frame < A_CRAWL0 || frame > A_CRAWL1) frame = A_CRAWL0;
                        }else{
                            if (frame < I_CRAWL0 || frame > I_CRAWL1) frame = I_CRAWL0;
                        }
                    }else{ //no more tunnel left, assume tunnel never get stuck now, we will change frame and change state to fall
                        state = FALL;
                        if (active) frame = A_CRAWL3;
                        else frame = I_CRAWL3;
                        //change box
                        box.x += 80;
                        box.w = STICK_WIDTH;
                        box.h = STICK_HEIGHT;
                    }
                }
//                else if(state == FALL){
//                    debug("s2");
//                    if (frame != A_FALL || frame != I_FALL) {
//                        //adjust box
//                        box.x += 40;
//                        debug("s1");
//                    }
//                    if (active) frame = A_FALL;
//                    else frame = I_FALL;
//                }
                else{
                
                
                    
                    
                if(level->stick_on_level(box, SDLK_RIGHT, 20)){
                    state = WALK;
                    frame += 1;
                    if (active) {
                        if (frame < A_WALK_R0 || frame > A_WALK_R3) frame = A_WALK_R0;
                    }else{
                        if (frame < I_WALK_R0 || frame > I_WALK_R3) frame = I_WALK_R0;
                    }
                }else{
                    if (level->is_tunnel(box, SDLK_RIGHT)) {
                        //change the state = CLAW
                        state = CRAWL;
                        
                        //change frame
                        if (active) {
                            frame = A_CRAWL2;
                        }else{
                            frame = I_CRAWL2;
                        }
                        //and change box
                        box.w = STICK_HEIGHT;
                        box.h = STICK_WIDTH;
                    }
                }
                }
                
                break;
            case SDLK_LEFT:
                
                if(level->stick_on_level(box, SDLK_LEFT, 20)){
                    state = WALK;
                    frame += 1;
                    if (active) {
                        if (frame < A_WALK_L0 || frame > A_WALK_L3) frame = A_WALK_L0;
                    }else{
                        if (frame < I_WALK_L0 || frame > I_WALK_L3) frame = I_WALK_L0;
                    }
                }else{
                    if (level->is_tunnel(box, SDLK_LEFT)) {
                        
                    }
                }
                break;
            case SDLK_UP:
                if(level->stick_on_level(box, SDLK_UP, 20)){
                    state = CLIMB;
                    frame += 1;
                    
                    if (active){
                        if(frame < A_CLIMB0) frame = A_CLIMB0;
                        if(frame > A_CLIMB1) frame = A_CLIMB0;
                    }else{
                        if(frame < I_CLIMB0) frame = I_CLIMB0;
                        if(frame > I_CLIMB1) frame = I_CLIMB0;
                    }
                    
                }else{
                    state = WALK;
                }
                break;
            case SDLK_DOWN:
                
                if(level->stick_on_level(box, SDLK_DOWN, 20)){
                    state = CLIMB;
                    frame += 1;
                    
                    if (active){
                        if(frame < A_CLIMB0) frame = A_CLIMB0;
                        if(frame > A_CLIMB1) frame = A_CLIMB0;
                    }else{
                        if(frame < I_CLIMB0) frame = I_CLIMB0;
                        if(frame > I_CLIMB1) frame = I_CLIMB0;
                    }

                }else{
                    state = WALK;
                }
                break;
            case SDLK_SPACE:
                if (level->stick_on_level(box, SDLK_SPACE, 20)) {
                    state = JUMP;
                    if (active) {
                        frame = A_JUMP;
                    }else{
                        frame = I_JUMP;
                    }
                    box.y -= 20;
                    //dirty quest
                    if (quest != NULL){
                        quest->set_done(true);
                    }
                }
                
                break;
            case SDLK_RETURN:
                level->interact_with_level(box);
                break;
            default: break;
        }
        
    }else if(event.type == SDL_KEYUP){
        //return to stand
        if(state == WALK || state == JUMP){
            if (state == JUMP) {
                box.y += 20;
                state = WALK;
            }
            if (active) frame = A_STAND;
            else frame = I_STAND;
        
        }else if(state == FALL){
            if (frame == I_CRAWL3){
                frame = I_FALL;
                box.x += 40;
                
            }else if(frame == A_CRAWL3){
                
                frame = A_FALL;
                box.x += 40;
                
            }
        }
    }
}

void Stick::hold_item(Sprite * item){
    this->item = item;
}

//For auto pilot mode
void Stick::animate(){
    if(!active && quest != NULL){
        if (frame == I_STAND) {
            frame = I_JUMP;
            box.y -= 20;
        }else if(frame == I_JUMP){
            frame = I_STAND;
            box.y += 20;
            quest->set_done(true);
        }
    }
    if (state == FALL) {
       
        box.y += 20;
        if (level->is_on_ground(box)) {
            state = WALK;
            if (active) frame = A_STAND;
            else frame = I_STAND;
        }
    }
    
}


void Stick::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
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
