//
//  robot.cpp
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "robot.h"
#include "constant.h"
#include "utility.h"

Robot::Robot(){
    box.x = 5*TILE_WIDTH;
    box.y = SCREEN_HEIGHT - TILE_HEIGHT - ROBOT_HEIGHT;
    box.w = ROBOT_WIDTH ;
    box.h = ROBOT_HEIGHT;
    
    xPos = 3;
    yPos = 11;
    pos = (yPos-1) * TILE_COLUMN + xPos;
    frame = WALK_R0;
    
    clip_tile();
}

Robot::~Robot(){
    
}

void Robot::clip_tile(){
    for (int i = 0; i < TOTAL_STATE; i += 1) {
        clips[i].x = i* ROBOT_WIDTH;
        clips[i].y = 0;
        clips[i].w = ROBOT_WIDTH;
        clips[i].h = ROBOT_HEIGHT;
    }
}

void Robot::animate(Tile * tiles[]){
    //if no obstacle is encounter, then keep going, if so, then return back
    //a set of movement is from 0 to 3
    //so only need to consider that in 3
    frame +=1;
    if (frame >= WALK_R0 && frame <= WALK_R3) {
        //       frame += 1;

        box.x += TILE_WIDTH/2;
    }else if(frame >= WALK_L0 && frame < WALK_L3){
//        frame += 1;
        box.x -= TILE_WIDTH/2;
        
    }else if(frame == WALK_L3){
        frame = WALK_R0;
    }
//else if(frame == WALK_R3){
//        if (!(tiles[pos + 1]->get_type() == TILE_BRICK|| tiles[pos - TILE_COLUMN+1]->get_type() == TILE_BRICK)&&
//            (tiles[pos+TILE_COLUMN+1]->get_type() == TILE_FLOOR ||tiles[pos+TILE_COLUMN+1]->get_type() == TILE_LADDER)){
//            box.x += TILE_WIDTH/4;
//        }else{
//            
//        }
//        
//    }else if(frame == WALK_L3){
//        
//    }
    
    //not kind of what i want
    //i would rather ask the tile whether i can go there, given my rect position
    //feels more reasonable
    //tiles feel so constranied....
    
}



void Robot::show(SDL_Rect camera, SDL_Surface *screen, SDL_Surface *tileSheet){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}