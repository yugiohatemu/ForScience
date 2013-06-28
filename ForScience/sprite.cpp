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
    box.x = 0;
    box.y = SCREEN_HEIGHT - TILE_HEIGHT - DOT_HEIGHT;
    box.w = DOT_WIDTH ;
    box.h = DOT_HEIGHT;
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
    xPos = 0;
    yPos = 11;
    pos = (yPos-1) * TILE_COLUMN + xPos;
//    box.x = xPos * TILE_WIDTH;
//    box.y = yPos * TILE_HEIGHT - DOT_HEIGHT;
//    std::cout<<box.x <<" "<< box.y<<std::endl;
}

//void Sprite::handle_input(SDL_Event event){
//    //If a key was pressed
//    if( event.type == SDL_KEYDOWN ){
//        //Adjust the velocity
//        switch( event.key.keysym.sym ){
//            case SDLK_UP: yVel -= DOT_HEIGHT / 2; break;
//            case SDLK_DOWN: yVel += DOT_HEIGHT  / 2; break;
//            case SDLK_LEFT: xVel -= DOT_WIDTH / 2; break; //ladder
//            case SDLK_RIGHT: xVel += DOT_WIDTH  / 2; break; //ladder
//            case SDLK_SPACE: break; //jump
//            case SDLK_RETURN: break; //interact with interactable
//            default: break;
//        }
//    }else if( event.type == SDL_KEYUP ){
//        //Adjust the velocity
//        switch( event.key.keysym.sym ){
//            case SDLK_UP: yVel += DOT_HEIGHT / 2; break;
//            case SDLK_DOWN: yVel -= DOT_HEIGHT / 2; break;
//            case SDLK_LEFT: xVel += DOT_WIDTH  / 2; break;
//            case SDLK_RIGHT: xVel -= DOT_WIDTH  / 2; break;
//            default: break;
//        }
//    }
//}

void Sprite::move(Tile * tiles){
    //check if u can move
    
    
}

void Sprite::handle_input(SDL_Event event,Tile * tiles[]){
    
    if( event.type == SDL_KEYDOWN ){
        //Adjust the velocity
        switch( event.key.keysym.sym ){
            case SDLK_RIGHT:
                if (xPos+1 < TILE_COLUMN && yPos +1 <= TILE_ROW) {
                    if (tiles[pos+TILE_COLUMN+ 1]->get_type() == TILE_FLOOR || tiles[pos+TILE_COLUMN+ 1]->get_type() == TILE_LADDER) {
                        xPos += 1;
                        pos += 1;
                        box.x += TILE_WIDTH;
                    }
                    
                }
                break; //ladder
            case SDLK_LEFT:
                if (xPos > 0 && yPos - 1 >= 0 && (tiles[pos+TILE_COLUMN-1]->get_type() == TILE_FLOOR || tiles[pos+TILE_COLUMN-1]->get_type() == TILE_LADDER)) {
                    xPos -= 1;
                    pos -= 1;
                    box.x -= TILE_WIDTH;
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
        std::cout<<pos<<" "<<box.x <<" "<< box.y<<" "<<tiles[pos]->get_type() <<std::endl;
    }else if( event.type == SDL_KEYUP ){
       
    }

}

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
