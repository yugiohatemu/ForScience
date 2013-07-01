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

//get which pos on given x and y
//if not valid , return -1?
int Level::get_tile_pos(int x, int y){
    int m = x/TILE_WIDTH;
    int n = y/TILE_HEIGHT;
    return m * TILE_COLUMN + n;
}

void Level::move_on_level(SDL_Rect &box, int dir, int speed){
    //1st based on the box x, y w h, calculate which area it is on
    int bot_right, top_right, bot_left, top_left = 0;
    int bot_center, top_center, center = 0;
    bool is_stuck = false;
    //it depends on whether it is in between or else where?
    switch (dir) {
        case SDLK_RIGHT:
            //check for further posistion directly
            bot_right= get_tile_pos(box.x + box.w + speed, box.y+ box.h);
            top_right = get_tile_pos(box.x + box.w + speed, box.y);
            if (tiles[bot_right + TILE_COLUMN].type == TILE_FLOOR  || tiles[bot_right + TILE_COLUMN].type == TILE_LADDER) { 
                //2nd, no obstacle for body
                for (int i = top_right; i <= bot_right; i += TILE_COLUMN) {
                    if (tiles[i].type == TILE_BRICK) {
                        is_stuck = true;
                        break;
                    }
                }
                if (is_stuck) {
                    box.x = (int)(box.x % TILE_COLUMN) * TILE_WIDTH;
                }else{
                    box.x += speed;
                }
            }
            break;
        case SDLK_LEFT:
            top_left = get_tile_pos(box.x - speed, box.y);
            bot_left = get_tile_pos(box.x- speed, box.y + box.h);
            if (tiles[bot_left + TILE_COLUMN].type == TILE_FLOOR  || tiles[bot_left + TILE_COLUMN].type == TILE_LADDER) {
                for (int i = top_left; i <= bot_left; i += TILE_COLUMN) {
                    if (tiles[i].type == TILE_BRICK) {
                        is_stuck = true;
                        break;
                    }
                }
                if (is_stuck) {
                    box.x = (int)((box.x % TILE_COLUMN) + 1) * TILE_WIDTH;
                }else{
                    box.x -= speed;
                }
            }
            break;
        case SDLK_UP:
            //the center has to in the stair
            bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            if (tiles[bot_center].type == TILE_LADDER) {
                box.x = (int)(box.x / TILE_COLUMN) * TILE_WIDTH; 
                if ( tiles[bot_center - TILE_COLUMN].type == TILE_LADDER) {
                    box.y += speed;
                }else if(tiles[bot_center - TILE_COLUMN].type == TILE_BACKWALL){
                    box.y = (int) (bot_center / TILE_COLUMN) * TILE_HEIGHT;
                }
            }
            break;
        case SDLK_DOWN:
            top_center = get_tile_pos(box.x + box.w/2, box.y);
            if (tiles[top_center].type == TILE_LADDER) {
                box.x = (int)(box.x / TILE_COLUMN) * TILE_WIDTH;
                if ( tiles[top_center + TILE_COLUMN].type == TILE_LADDER) {
                    box.y += speed;
                }else if(tiles[top_center + TILE_COLUMN].type == TILE_BACKWALL){
                    box.y = (int) ((top_center / TILE_COLUMN) +1) * TILE_HEIGHT;
                }
            }
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

