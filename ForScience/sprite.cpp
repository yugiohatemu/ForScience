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
    box.x = 5*TILE_WIDTH;
    box.y = SCREEN_HEIGHT - TILE_HEIGHT - DOT_HEIGHT;
    box.w = DOT_WIDTH ;
    box.h = DOT_HEIGHT;
    
    xPos = 5;
    yPos = 11;
    pos = (yPos-1) * TILE_COLUMN + xPos;
    
    tileSheet = NULL;
    clip_tile();
    
    frame = 0;
    
}


void Sprite::clip_tile(){
    tileSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/stickman.png" );
    
    clips[STAND].x = 8;
    clips[STAND].y = 8;
    clips[STAND].w = 50;
    clips[STAND].h = 140;
    
    clips[WALKR0].x = clips[STAND].x + DOT_WIDTH;
    clips[WALKR0].y = 8;
    clips[WALKR0].w = 50;
    clips[WALKR0].h = 140;
    
    clips[WALKR1].x = clips[WALKR0].x + DOT_WIDTH + 20;
    clips[WALKR1].y = 8;
    clips[WALKR1].w = 50;
    clips[WALKR1].h = 140;
    
    clips[WALKR2].x = clips[WALKR1].x + DOT_WIDTH + 20;
    clips[WALKR2].y = 8;
    clips[WALKR2].w = 50;
    clips[WALKR2].h = 140;
    
    clips[WALKL2].x = clips[WALKR2].x + DOT_WIDTH + 10;
    clips[WALKL2].y = 8;
    clips[WALKL2].w = 55;
    clips[WALKL2].h = 140;
    
    clips[WALKL1].x = clips[WALKL2].x+ DOT_WIDTH + 20;
    clips[WALKL1].y = 8;
    clips[WALKL1].w = 50;
    clips[WALKL1].h = 140;
    
    clips[WALKL0].x = clips[WALKL1].x + DOT_WIDTH + 20;
    clips[WALKL0].y = 8;
    clips[WALKL0].w = 50;
    clips[WALKL0].h = 140;
    
}


void Sprite::animate(){
    if (frame != STAND) {
        if (frame >= WALKR0 && frame < WALKR2) {
            frame += 1;
            box.x += TILE_WIDTH/3;
        }else if(frame >= WALKL0 && frame < WALKL2){
            frame += 1;
            box.x -= TILE_WIDTH/3;
        }else{
            if (frame == WALKR2) {
                xPos += 1;
                pos += 1;
            }else if(frame == WALKL2){
                xPos -= 1;
                pos -= 1;
            }
            frame = STAND;
        }
    }
}

void Sprite::handle_input(SDL_Event event,Tile * tiles[]){

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
                        if (frame > WALKR2) {
                            frame = WALKR0;
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
                        if (frame < WALKL0) { //stand or run right
                            frame = WALKL0;
                        }
                        if (frame > WALKL2) {
                            frame = WALKL0;
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
   
}

void Sprite::show(SDL_Rect camera,SDL_Surface * dot, SDL_Surface * screen){
    //Show the Sprite
    apply_surface( box.x - camera.x, box.y - camera.y, dot, screen );
}

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
