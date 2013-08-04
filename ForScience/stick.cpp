//
//  Stick.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stick.h"
#include "utility.h"

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

HUMAN_STATE Stick::get_state(){
    return state;
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

bool Stick::is_alive(){
    return life > 0;
}

void Stick::minus_life(){
    if (life > 0) {
        life -= 1;
        if (active) frame = A_STUN;
        else frame = I_STUN;
        box.y += 20;
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
    
    for (int i = 0; i <= I_CLIMB1; i += 1) {
        clips[i].y = 0;
        clips[i].h = STICK_HEIGHT;
    }
    
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
    
    clips[I_STUN].x = clips[I_FALL].x + clips[I_FALL].w;
    clips[I_STUN].y = 20;
    clips[I_STUN].w = 60;
    clips[I_STUN].h = 100;
    
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
        int dir = event.key.keysym.sym;
        HUMAN_STATE next_state = level->stick_on_level(box, dir, 20, state);
        //handling all the state change
        //that is not stucked
        if (next_state != STUCK && next_state != state) {
            if (state == WALK && next_state == CLIMB) {
                //change state and frame
                //god I want an animation class...., but after fixing this
                if (active) frame = A_CLIMB0;
                else frame = I_CLIMB0;
            }else if(state == WALK && next_state == JUMP){
                if (active) frame = A_JUMP;
                else frame = I_JUMP;
                
                //Dirty quest
                if (quest != NULL) quest->set_done(true);
                
            }else if(state == CLIMB && next_state == WALK){
                if (active) frame = A_STAND;
                else frame = I_STAND;
            }else if(state == CLIMB && next_state == CRAWL){
                if(active) frame = A_CRAWL2;
                else frame = I_CRAWL2;
                //changin box
                box.w = STICK_HEIGHT;
                box.h = STICK_WIDTH;
            }else if(state == CRAWL && next_state == FALL){
                if(active) frame = A_CRAWL3;
                else frame = I_CRAWL3;
                
                box.x += 120;
                box.w = STICK_WIDTH;
                box.h = STICK_HEIGHT;
            }else if(next_state == EXIT){
                debug("WIN");
            }
            state = next_state;
        }else if (state != STUCK) {
            frame += 1;
            if (state == WALK && dir == SDLK_RIGHT) {
                
                if (active) {
                    if (frame < A_WALK_R0 || frame > A_WALK_R3) frame = A_WALK_R0;
                }else{
                    if (frame < I_WALK_R0 || frame > I_WALK_R3) frame = I_WALK_R0;
                }
            }else if(state == WALK && dir == SDLK_LEFT){
                if (active) {
                    if (frame < A_WALK_L0 || frame > A_WALK_L3) frame = A_WALK_L0;
                }else{
                    if (frame < I_WALK_L0 || frame > I_WALK_L3) frame = I_WALK_L0;
                }
            }else if(state == CLIMB){ //there is a direction about that
                if (active){
                    if(frame < A_CLIMB0 || frame > A_CLIMB1) frame = A_CLIMB0;
                }else{
                    if(frame < I_CLIMB0 || frame > I_CLIMB1) frame = I_CLIMB0;
                }
            }else if(state == CRAWL){
                if (active) {
                    if (frame < A_CRAWL0 || frame > A_CRAWL1) frame = A_CRAWL0;
                }else{
                    if (frame < I_CRAWL0 || frame > I_CRAWL1) frame = I_CRAWL0;
                }
            }
        }
        
        if (dir == SDLK_RETURN) {
            level->interact_with_level(&box);
            
        }
    }else if(event.type == SDL_KEYUP){
        if(state == WALK || state == JUMP){
            if (state == JUMP) {
                box.y += 20;
                state = WALK;
            }
            if (active) frame = A_STAND;
            else frame = I_STAND;
            
        }
    }

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
        if (frame == I_CRAWL3){
            frame = I_FALL;
            box.x += 40;
            
        }else if(frame == A_CRAWL3){
            frame = A_FALL;
            box.x += 40;
            
        }
        box.y += 20;
        if (level->is_on_ground(box)) {
            state = WALK;
            if (active) frame = A_STAND;
            else frame = I_STAND;
        }
    }
    
}


void Stick::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, stickSheet, screen, &clips[frame]);
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
