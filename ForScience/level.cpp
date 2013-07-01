//
//  level.cpp
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "level.h"
#include "utility.h"
#include "constant.h"
#include <fstream>

Level::Level(){
    //Fill this up later
    clips = NULL;
    tiles = NULL;
    set_clip();
    set_tile();
}


Level::~Level(){
    delete [] clips;
    delete [] tiles;
}

void Level::set_clip(){
    clips = new SDL_Rect[TOTAL_TILES];
    
    clips[ TILE_EMPTY ].x = 40;
    clips[ TILE_LADDER ].x = 80;
    clips[ TILE_FLOOR ].x = 120;
    clips[ TILE_BACKWALL ].x = 200;
    clips[ TILE_BRICK ].x = 160;
      
    for (int i = 0; i < TOTAL_TILES; i ++) {
        clips[i].y = 0;
        clips[i].w = TILE_WIDTH;
        clips[i].h = TILE_HEIGHT;
    }
}

void Level::set_tile(){
    tiles = new Level::Tile[TOTAL_TILES];
    
    std::ifstream map( "/Users/wei/Desktop/ForScience/ForScience/lazy.map" );
    for (int i = 0; i < TILE_ROW; i++) {
        for (int j = 0; j < TILE_COLUMN; j ++) {
            int tileType = -1;
            map >> tileType;
            if( map.fail() == true ){
                break;
            }
            
            //If the number is a valid tile number, else close
            if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) ){
                tiles[i * TILE_COLUMN + j].set_tile(j * TILE_HEIGHT, i * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT, tileType);
            }else{
                break;
            }
        }
    }
    
    //Close the file
    map.close();
}

void Level::show(SDL_Rect camera, SDL_Surface *tileSheet, SDL_Surface *screen){
    for (int i = 0; i < TOTAL_TILES; i ++) {
        apply_surface(tiles[i].box.x,tiles[i].box.y, tileSheet, screen, &clips[tiles[i].type]);
    }
}

void Level::move_on_level(SDL_Rect &box, int dir, int speed){
    //1st based on the box x, y w h, calculate which area it is on
    int corner[4][2];
    corner[0][0] = box.x;
    corner[0][1] = box.y; //LT
    corner[1][0] = box.x + box.w;
    corner[1][1] = box.y; //RT
    corner[2][0] = box.x;
    corner[2][1] = box.y + box.h;//LB
    corner[3][0] = box.x + box.w;
    corner[3][1] = box.y + box.h;//RB
    //no ...
    
    switch (dir) {
        case SDLK_RIGHT:
            //the under foot is floor or ladder
            //2nd, no obstacle for body
            if (box.y+box.h ) {
                
            }
            break;
        case SDLK_LEFT:
            break;
        default:
            break;
    }
}

//Tile

Level::Tile::Tile(){
    type = 0;
}

void Level::Tile::set_tile(int x, int y, int w, int h, int type){
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    this->type = type;
}

