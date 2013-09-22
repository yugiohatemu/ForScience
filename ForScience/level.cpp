//
//  level.cpp
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "level.h"
#include "utility.h"

#include "exit.h"
#include "door.h"
#include "book.h"
#include "glassDoor.h"
#include <fstream>
#include <iostream>
#include "robotMaster.h"
#include "stickMaster.h"

Level::Level(std::string file_name, int row, int column){
    this->file_name = file_name;
    this->row = row;
    this->column = column;
    total_tile = row * column;
    tiles = NULL;
    total_sprites = 2;
    sprite_list = new Sprite*[total_sprites];
    sprite_list[0] = new Exit(10 * TILE_WIDTH, 2 * TILE_HEIGHT);
    sprite_list[1] = new GlassDoor(5 * TILE_WIDTH+ 10, 3 * TILE_HEIGHT);
    //sprite_list[2] = new Book(4 * TILE_WIDTH, 5 * TILE_HEIGHT);
    
    int pos1[2] = {80,120};
    stick_master = new StickMaster(this,1,pos1);
    int pos2[2] = {280,160};
    robot_master = new RobotMaster(this,1,pos2);
    state = PLAYING;
    set_clip();
    set_tile();
}

//return -1 if fail to read file
int Level::get_int_from_file(std::ifstream &file){
    int n = -1;
    file >> n;
    if (file.fail()) {
        debug("load map fail");
    }
    
    return n;
}

void Level::load_file_fail(std::ifstream &file, std::string s){
    debug(s);
    file.close();
}

Level::Level(std::string file_name){
    this->file_name = file_name;
    set_clip();
    tiles = NULL;
    
    std::ifstream map( file_name.c_str() );
    
    //cin row and column
    row = get_int_from_file(map);
    column = get_int_from_file(map);
    if (row < 0 || column < 0) {
        load_file_fail(map, "r & c fail");
        return ;
    }
    total_tile = row * column;
    
    
    //set_tile();
    tiles = new Level::Tile[total_tile];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j ++) {
            int tileType = get_int_from_file(map);
            if (tileType < 0) {
                load_file_fail(map, "tile fail");
                return ;
            }
            
            //If the number is a valid tile number, else close
            if( ( tileType >= 0 ) && ( tileType < TOTAL_CLIP ) ){
                tiles[i * column + j].set_tile(j * TILE_HEIGHT, i * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT, tileType);
            }else{
                break;
            }
        }
    }
    
    //1, 80 120, //1 280, 160
    int stick_count = get_int_from_file(map);
    
    if (stick_count > 0) {
        int * pos = new int[2 * stick_count];
        for (int i = 0; i < stick_count; i++) {
            int x = get_int_from_file(map);
            int y = get_int_from_file(map);
            if (x >= 0 && y >= 0) {
                pos[2 * i] = x;
                pos[2 * i + 1] = y;
               
            }else{
                load_file_fail(map, "stick fail");
                delete [] pos;
                return ;
            }
            
        }
        stick_master = new StickMaster(this,stick_count,pos);
        delete [] pos;
    }
    
    int robot_count = get_int_from_file(map);
    if (robot_count > 0) {
        int * pos = new int[2 * robot_count];
        for (int i = 0; i < robot_count; i++) {
            int x = get_int_from_file(map);
            int y = get_int_from_file(map);
            if (x >= 0 && y >= 0) {
                pos[2 * i] = x;
                pos[2 * i + 1] = y;
                
            }else{
                load_file_fail(map, "robot fail");
                delete [] pos;
                return ;
            }
            
        }
        robot_master = new RobotMaster(this,stick_count,pos);
        delete [] pos;
    }
    
    state = PLAYING;
    
    total_sprites = 2;
    //should also be loaded dynamically
    sprite_list = new Sprite*[total_sprites];
    sprite_list[0] = new Exit(10 * TILE_WIDTH, 2 * TILE_HEIGHT);
    sprite_list[1] = new GlassDoor(5 * TILE_WIDTH+ 10, 3 * TILE_HEIGHT);
    //sprite_list[2] = new Book(4 * TILE_WIDTH, 5 * TILE_HEIGHT);

    
    //Close the file
    map.close();
}



Level::~Level(){
    delete stick_master;
    delete robot_master;
    delete [] tiles;
    for (int i = 0; i < total_sprites; i+=1) {
        delete sprite_list[i]; //???
    }
    delete [] sprite_list;
    stickSheet = NULL;
    robotSheet = NULL;
    
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
                debug("Load Tile Fail");
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

void Level::set_sheet(SDL_Surface * robot, SDL_Surface * stick){
    stickSheet = stick;
    robotSheet = robot;
}

Level::LEVEL_STATE Level::get_level_state(){
    return state;
}

void Level::show(SDL_Rect camera, SDL_Surface *tile, SDL_Surface *screen){
    SDL_FillRect(screen , NULL , 0x000000);
    for (int i = 0; i < total_tile; i ++) {
        apply_surface(tiles[i].box.x,tiles[i].box.y, tileSheet, screen, &clips[tiles[i].type]);
    }
    for (int i = 0; i < total_sprites; i +=1) {
        sprite_list[i]->show(camera, tileSheet, screen);
    }
    
    stick_master->show(camera, stickSheet,screen);
    robot_master->show(camera, robotSheet, screen);
}

void Level::animate(){
    for (int i = 0; i < total_sprites; i +=1) {
        sprite_list[i]->animate();
    }
    RobotMaster * robot = dynamic_cast<RobotMaster *>(robot_master);
    StickMaster * stick = dynamic_cast<StickMaster *>(stick_master);
    robot->react_to(stick);
    robot->animate();
    stick->animate();
}

void Level::handle_input(SDL_Event event){
    stick_master->handle_input(event);
    //update level state here
    StickMaster * stick = dynamic_cast<StickMaster *>(stick_master);
    if (stick->is_all_stick_escape()) {
        //ask the levelscreen to push
        state = WIN;
    }else if(stick->is_all_stick_dead()){
        state = LOSE;
    }
    
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


ROBOT_STATE Level::robot_on_level(SDL_Rect &box, int dir, int speed, ROBOT_STATE state){
    GlassDoor * door = dynamic_cast<GlassDoor *>(sprite_list[1]);
    if (dir == SDLK_RIGHT) {
        int bot_right= get_tile_pos(box.x + box.w + speed, box.y+ box.h);
        int top_right = get_tile_pos(box.x + box.w + speed, box.y);
        
        if ((tiles[bot_right + column].type >= WALL_C0 && tiles[bot_right + column].type <= WALL_H4)
            || tiles[bot_right + column].type == LADDER) {
            //2nd, no obstacle for body
            if (check_collision(door->get_rect(), box)) {
                
//                if (state == NORMAL) {
//                    state = TURN;
//                    box.x -= speed;
//                }else{
                
                    door->interact(box);
                    if (!door->is_block()) box.x += speed;
//                }
            }else{
                for (int i = bot_right; i > top_right; i -=column) {
                    if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) {
                        state = TURN;
                        break;
                    }
                }
                
                if (state == TURN )box.x  = (top_right % column - 1) * TILE_WIDTH;
                else box.x += speed;
            }
            
        }
    }else if(dir == SDLK_LEFT){
        int top_left = get_tile_pos(box.x - speed, box.y);
        int bot_left = get_tile_pos(box.x - speed, box.y + box.h);
        if (check_collision(door->get_rect(), box)) {
//            if (state == NORMAL) {
//                state = TURN;
//                box.x += speed; //to avoid collison on turn back
//
//            }else{
                door->interact(box);
                if (!door->is_block())  box.x -= speed;

//            }
        }else{
            
            if ((tiles[bot_left + column].type >= WALL_C0 &&  tiles[bot_left + column].type <= WALL_H4) ||
                 tiles[bot_left + column].type == LADDER) {
                    for (int i = bot_left; i > top_left; i -= column) {
                        if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) {
                            state = TURN;
                            break;
                        }
                    }
                    
                    if (state == TURN) box.x =  (top_left % column + 1) * TILE_WIDTH;
                    else box.x -= speed;
                }
        }
    }
    
    return state;
}


void Level::interact_with_level(SDL_Rect *box){
    //Suppose the first one is always the exit, haha
    Exit * exit = dynamic_cast<Exit *>(sprite_list[0]);
    exit->interact(*box);
    
//    for (int i = 0; i < total_sprites; i+=1) {
//       
//    }
//    Book * test = dynamic_cast<Book *>(sprite_list[i]);
//    if (test) { //it it is the book,
//        if (check_collision(*box, test->get_rect())) {
//            test->set_stick_rect(box);
//            
//        }
//    }

}


HUMAN_STATE Level::stick_on_level(SDL_Rect &box, int dir, int speed, HUMAN_STATE state){
    
    if (state == WALK) {
        if (dir == SDLK_RIGHT) {
            int bot_right= get_tile_pos(box.x + box.w + speed, box.y+ box.h);
            int top_right = get_tile_pos(box.x + box.w + speed, box.y);
            
            if ((box.y + box.h)%TILE_HEIGHT == 0 &&
                ((tiles[bot_right + column].type >= WALL_C0 &&  tiles[bot_right + column].type <= WALL_H4)
                 || tiles[bot_right + column].type == LADDER)) {
                    //2nd, no obstacle for body
                    for (int i = bot_right; i > top_right; i -=column) {
                        if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) { //dirty fix
                            state = STUCK;
                            break;
                        }
                    }
                    
                    if (state == STUCK )box.x  = (top_right % column - 1) * TILE_WIDTH;
                    else box.x += speed;
            }
        }else if(dir == SDLK_LEFT){
            int top_left = get_tile_pos(box.x - speed, box.y);
            int bot_left = get_tile_pos(box.x - speed, box.y + box.h);
            
            
            if ((box.y + box.h)%TILE_HEIGHT == 0 &&
                ((tiles[bot_left + column].type >= WALL_C0 &&  tiles[bot_left + column].type <= WALL_H4) ||
                 tiles[bot_left + column].type == LADDER)) {
                    for (int i = bot_left; i > top_left; i -= column) {
                        if (tiles[i].type >= WALL_C0 && tiles[i].type <= WALL_V4) {
                            state = STUCK;
                            break;
                        }
                    }
                    
                    if (state == STUCK) box.x =  (top_left % column + 1) * TILE_WIDTH;
                    else box.x -= speed;
            }
        }else if(dir == SDLK_SPACE){
            
            int top_center = get_tile_pos(box.x + box.w/2, box.y - speed);
            if (tiles[top_center].type != BACK_WALL && tiles[top_center].type != LADDER) { //- column?
                state = STUCK;
            }else {
                box.y -= speed;
                state = JUMP;
            }
        }else if(dir == SDLK_UP){
            int bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            int top_center = get_tile_pos(box.x + box.w/2, box.y-20); //why 20 here?
            if (tiles[bot_center].type == LADDER ) {
                
                if (tiles[top_center].type >= WALL_C0 && tiles[top_center].type <= WALL_H4) {
                    state = STUCK;
                }else if ( tiles[bot_center - column].type == LADDER) {
                    box.x = (bot_center % column) * TILE_WIDTH;
                    box.y -= speed;
                    state = CLIMB;
                }
            }
            
        }else if(dir == SDLK_DOWN){
            int bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            if (tiles[bot_center + column].type == LADDER) {
                box.x = (int)(box.x / TILE_WIDTH) * TILE_WIDTH;
                box.y += speed;
                state = CLIMB;
            }
        }
    }else if(state == CLIMB){
        if (dir == SDLK_UP) {
            int bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            int top_center = get_tile_pos(box.x + box.w/2, box.y-20);
            if (tiles[top_center].type >= WALL_C0 && tiles[top_center].type <= WALL_H4) {
                            
                state = STUCK;
                box.y = (int) (top_center /column + 1) * TILE_HEIGHT;
                
            }else if ( tiles[bot_center - column].type == LADDER && state != STUCK) {//&& !state == STUCK
                box.y -= speed;
            }else if(tiles[bot_center - column].type == BACK_WALL){
                box.y = (int) (bot_center / column)  * TILE_HEIGHT - box.h;
                state = WALK;
            }
        }else if(dir == SDLK_DOWN){
            int bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
            if (tiles[bot_center].type == LADDER || tiles[bot_center + column].type == LADDER) {
                box.x = (int)(box.x / TILE_WIDTH) * TILE_WIDTH;
                if ( tiles[bot_center + column].type == LADDER) {
                    box.y += speed;
                }else if(tiles[bot_center + column].type >= WALL_H0 && tiles[bot_center + column].type <= WALL_H4){
                    box.y = (int) ((bot_center / column) +1)  * TILE_HEIGHT - box.h;
                    state = WALK;
                }
            }
        }else if(dir == SDLK_RIGHT){
            int top_right = get_tile_pos(box.x + box.w , box.y) ;
            
            if (tiles[top_right+ column+1].type == TUNNEL) state = CRAWL;
            else state = STUCK;
        }else if(dir == SDLK_LEFT){
            int top_left = get_tile_pos(box.x, box.y);
            
            if (tiles[top_left+ column-1].type == TUNNEL) state = CRAWL;
            else state = STUCK;
        }
    }else if(state == CRAWL){
        if (dir == SDLK_RIGHT) {
            int top_right = get_tile_pos(box.x + box.w+ speed, box.y)+column + 1;
            
            if (tiles[top_right].type == TUNNEL) box.x += speed;
            else if (tiles[top_right].type  == BACK_WALL ) state = FALL;
            else if(tiles[top_right].type == LADDER) state = CLIMB;
            else {
                    state = STUCK;
                    box.x = (top_right % column) * TILE_WIDTH;
            }
        }else if(dir == SDLK_LEFT){
            
        }
    }else if(state == FALL){

    }
    interact_with_level(&box); //a passive interact and an active interact?
    //dirty prototype for now
    if (dir == SDLK_RETURN) {
       Exit * exit = dynamic_cast<Exit *>(sprite_list[0]);
        if (exit->is_open()) {
            state = EXIT;
        }
    }
    return state;
}


bool Level::is_on_ground(SDL_Rect &box){
    int bot_center = get_tile_pos(box.x + box.w/2, box.y + box.h);
    if (tiles[bot_center ].type == LADDER ||
       (tiles[bot_center ].type >= WALL_H0 && tiles[bot_center ].type <= WALL_H4)) {
        box.y = (int) (bot_center / column)  * TILE_HEIGHT - box.h;
        return true;
    }else{
        return false;
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

