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
#include <iostream>

Level::Level(std::string file_name, int row, int column){
    this->file_name = file_name;
    this->row = row;
    this->column = column;
    total_tile = row * column;
    tiles = NULL;
    exit = new Exit(10 * TILE_WIDTH, 2 * TILE_HEIGHT);
    door = new Door(7 * TILE_WIDTH, 3 * TILE_HEIGHT);
    set_clip();
    set_tile();
}

Level::~Level(){
    delete [] tiles;
    delete exit;
    delete door;
}

//It would be easier if I can just read a file
//but that will be for very very late developement
void Level::set_clip(){
   
    for (int i = WALL_C0; i < TOTAL_CLIP; i +=1) {
        clips[i].x = (int)(i % 5) * TILE_WIDTH;
        clips[i].y = (int)(i / 5) * TILE_HEIGHT;
        clips[i].w = TILE_WIDTH;
        clips[i].h = TILE_HEIGHT;
    }

}

void Level::set_tile(){
    tiles = new Level::Tile[total_tile];
    
    std::ifstream map( file_name.c_str() );
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j ++) {
            int tileType = -1;
            map >> tileType;
            if( map.fail() == true ){
                break;
            }
            
            //If the number is a valid tile number, else close
            if( ( tileType >= 0 ) && ( tileType < TOTAL_CLIP ) ){
                tiles[i * column + j].set_tile(j * TILE_HEIGHT, i * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT, tileType);
            }else{
                break;
            }
        }
    }
    
    //Close the file
    map.close();
}

void Level::show(SDL_Rect camera, SDL_Surface *tileSheet, SDL_Surface *screen){
    for (int i = 0; i < total_tile; i ++) {
        apply_surface(tiles[i].box.x,tiles[i].box.y, tileSheet, screen, &clips[tiles[i].type]);
    }
    exit->show(camera, tileSheet, screen);
    door->show(camera, tileSheet, screen);
}

//get which pos on given x and y
//special case for bottom line and right line

int Level::get_tile_pos(int x, int y){
    //std::cout<<x<<" "<<y<<std::endl;
    int m = x / TILE_WIDTH;
    int n = y / TILE_HEIGHT;
    if (x % TILE_WIDTH == 0) m -= 1 ;
    if (y % TILE_HEIGHT == 0) n -= 1;
    
    return n * column + m;
}
//TODO: boundary check
//TODO: seperate based on robot?
bool Level::move_on_level(SDL_Rect &box, int dir, int speed){
    //1st based on the box x, y w h, calculate which area it is on
    int bot_right, top_right, bot_left, top_left = 0;
    int bot_center, top_center = 0;
    bool is_stuck = false;
    bool movable = false; //do not change frame is state is not enterable
    
    switch (dir) {
        case SDLK_RIGHT:
            //check for further posistion directly
            bot_right= get_tile_pos(box.x + box.w + speed, box.y+ box.h);
            top_right = get_tile_pos(box.x + box.w + speed, box.y);
            //whether the it is actually touch on the ground
            //do air jump later
            if (door->is_block() && check_collision(door->get_rect(), box)) {
                break;
            }
            
            if ((box.y + box.h)%TILE_HEIGHT == 0 &&
                ((tiles[bot_right + column].type >= WALL_C0 &&  tiles[bot_right + column].type <= WALL_H4)
                 || tiles[bot_right + column].type == LADDER)) {
                //2nd, no obstacle for body
                    for (int i = bot_right; i > top_right; i -=column) {
                        if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) { //dirty fix
                            is_stuck = true;
                            break;
                        }
                    }
                    
                    
                    if (is_stuck ) {
                        box.x  = (top_right % column - 1) * TILE_WIDTH;
                    }else{
                        box.x += speed;
                        movable = true;
                    }
            }
            break;
        case SDLK_LEFT:
            top_left = get_tile_pos(box.x - speed, box.y);
            bot_left = get_tile_pos(box.x - speed, box.y + box.h);
            
            if (door->is_block() && check_collision(door->get_rect(), box)) {
                break;
            }
            
            if ((box.y + box.h)%TILE_HEIGHT == 0 &&
                ((tiles[bot_left + column].type >= WALL_C0 &&  tiles[bot_left + column].type <= WALL_H4) ||
                 tiles[bot_left + column].type == LADDER)) {
                for (int i = bot_left; i > top_left; i -= column) {
                    if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) {
                        is_stuck = true;
                        break;
                    }
                }
                    
                if (is_stuck) {
                    
                    box.x =  (top_left % column + 1) * TILE_WIDTH;
                    //movable = true;
                }else{
                    box.x -= speed;
                    movable = true;
                }
            }
            
            break;
        case SDLK_UP: //TODO: care about don;t stuck case latter
            //the center has to in the stair
            bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            if (tiles[bot_center].type == LADDER) {
                box.x = (bot_center % column) * TILE_WIDTH;
                if ( tiles[bot_center - column].type == LADDER) {
                    box.y -= speed;
                    movable = true;
                }else if(tiles[bot_center - column].type == BACK_WALL){
                    box.y = (int) (bot_center / column)  * TILE_HEIGHT - box.h;
                    //movable = true;
                }
            }
            break;
        case SDLK_DOWN:
            bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            if (tiles[bot_center].type == LADDER || tiles[bot_center + column].type == LADDER) {
                box.x = (int)(box.x / TILE_WIDTH) * TILE_WIDTH;
                if ( tiles[bot_center + column].type == LADDER) {
                    box.y += speed;
                    movable = true;
                }else if(tiles[bot_center + column].type >= WALL_H0 && tiles[bot_center + column].type <= WALL_H4){
                    box.y = (int) ((bot_center / column) +1)  * TILE_HEIGHT - box.h;
                   // movable = true;
                }
            }
            break;
        case SDLK_SPACE:
            bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h - speed);
            top_center = get_tile_pos(box.x + box.w/2, box.y - speed);
            if ((box.y + box.h)%TILE_HEIGHT == 0) {
                if ( tiles[bot_center + column].type >= WALL_H0 && tiles[bot_center + column].type <= WALL_H4){
                    movable = true;
                }else if(tiles[bot_center + column].type == LADDER){

                    for (int i = bot_center; i >= top_center; i -= column) {
                        if (tiles[i].type != BACK_WALL) {
                            is_stuck = true;
                            break;
                        }
                    }
                    movable = !is_stuck;
                }
            }
            break;
        default:
            break;
    }
    return movable;
}

void Level::interact_with_level(SDL_Rect box){
    if (check_collision(box, exit->get_rect())) {
        exit->animate();
    }else if(check_collision(box, door->get_rect())){
        door->animate();
    }
}

//Tile

Level::Tile::Tile(){
    type = EMPTY;
}

void Level::Tile::set_tile(int x, int y, int w, int h, int type){
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    this->type = type;
}

