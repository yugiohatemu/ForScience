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
    box.y = SCREEN_HEIGHT - TILE_HEIGHT - STICK_HEIGHT;
    box.w = STICK_WIDTH ;
    box.h = STICK_HEIGHT;
    
    xPos = 5;
    yPos = 11;
    pos = (yPos-1) * TILE_COLUMN + xPos;
    
    tileSheet = NULL;
    clip_tile();
    
    frame = 0;
    
}


void Sprite::clip_tile(){
    tileSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/stickman.png" );
    
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
    clips[WALK_R4] = clips[WALK_R0]; //R4 = R0
    
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
    clips[WALK_L4] = clips[WALK_L0];
   
    
}


void Sprite::animate(){
//    if (frame != STAND) {
//        if (frame >= WALK_R0 && frame < WALK_R2) {
//            frame += 1;
//            box.x += TILE_WIDTH/3;
//        }else if(frame >= WALK_L0 && frame < WALK_L2){
//            frame += 1;
//            box.x -= TILE_WIDTH/3;
//        }else{
//            if (frame == WALK_R2) {
//                xPos += 1;
//                pos += 1;
//            }else if(frame == WALK_L2){
//                xPos -= 1;
//                pos -= 1;
//            }
//            frame = STAND;
//        }
//    }
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
                if (frame > WALK_R4) {
                    frame = WALK_R0;
                }
                break;
            case SDLK_LEFT:
                level->move_on_level(box, SDLK_LEFT, 20);
                frame += 1;
                if (frame < WALK_L0) { //stand or run right
                    frame = WALK_L0;
                }
                if (frame > WALK_L4) {
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
        //frame = STAND;
    }
}

/*void Sprite::handle_input(SDL_Event event,Tile * tiles[]){

    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_RIGHT:
                
                if (xPos+1 < TILE_COLUMN && yPos +1 <= TILE_ROW) {
                    if (!(tiles[pos + 1]->get_type() == TILE_BRICK||
                        tiles[pos - TILE_COLUMN+1]->get_type() == TILE_BRICK||
                        tiles[pos - TILE_COLUMN*2+1]->get_type() == TILE_BRICK)&&
                        (tiles[pos+TILE_COLUMN+1]->get_type() == TILE_FLOOR ||
                        tiles[pos+TILE_COLUMN+1]->get_type() == TILE_LADDER)) {
                        
                        box.x += TILE_WIDTH/3;
                        frame += 1;
                        if (frame > WALK_R2) {
                            frame = WALK_R0;
                            xPos += 1;
                            pos += 1;
                        }
                    }
                    //add a time check here, if time overlap , then change animation?
                    //do a whole frame of animation by one self?
                    
                }
                
                break; //ladder
            case SDLK_LEFT:
                //std::cout<<"????"<<std::endl;
                if (xPos > 0 && yPos - 1 >= 0 ) {
                    if (!(tiles[pos - 1]->get_type() == TILE_BRICK||
                          tiles[pos - TILE_COLUMN-1]->get_type() == TILE_BRICK||
                          tiles[pos - TILE_COLUMN*2-1]->get_type() == TILE_BRICK)&&
                        (tiles[pos+TILE_COLUMN-1]->get_type() == TILE_FLOOR || tiles[pos+TILE_COLUMN-1]->get_type() == TILE_LADDER)) {
                        box.x -= TILE_WIDTH/3;
                        frame += 1;
                        if (frame < WALK_L0) { //stand or run right
                            frame = WALK_L0;
                        }
                        if (frame > WALK_L2) {
                            frame = WALK_L0;
                            xPos -= 1;
                            pos -= 1;
                        }
                    }
                   
                }
                
                break;
            case SDLK_UP:
                if (0 <= pos && pos < TOTAL_TILES && tiles[pos]->get_type() == TILE_LADDER) {
                    yPos -= 1;
                    pos -= TILE_COLUMN;
                    box.y -= TILE_HEIGHT;
                }
                break;
            case SDLK_DOWN:
                if (0 <= pos && pos < TOTAL_TILES && tiles[pos+TILE_COLUMN]->get_type() == TILE_LADDER) {
                    yPos += 1;
                    pos += TILE_COLUMN;
                    box.y += TILE_HEIGHT;
                }
                break;
            default: break;
        }
        //std::cout<<pos<<" "<<box.x <<" "<< box.y<<" "<<tiles[pos]->get_type() <<std::endl;
    }else if( event.type == SDL_KEYUP ){
       
    }
   
}*/


void Sprite::show(SDL_Rect camera, SDL_Surface * screen){
    apply_surface(box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[frame]);
}


//Clear the tile sheet that is being used
Sprite::~Sprite(){
    if (tileSheet) {
        SDL_FreeSurface(tileSheet);
    }
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
