//
//  level.h
//  ForScience
//
//  Created by Yue on 6/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__level__
#define __ForScience__level__

#include "SDL/SDL.h"
#include <string>
#include "constant.h"
#include "sprite.h"
#include "drawable.h"

class Level{
    struct Tile{
        SDL_Rect box;
        int type;
        Tile();
        void set_tile(int x, int y, int w, int h, int type);
    };
    enum CLIP{
        WALL_C0, WALL_C1, WALL_C2, WALL_C3,WALL_C4,
        WALL_H0, WALL_H1,WALL_H2,WALL_H3, WALL_H4,
        WALL_V0,WALL_V1,WALL_V2, WALL_V3, WALL_V4,
        EMPTY,BACK_WALL,LADDER, BRICK, TUNNEL,
        TOTAL_CLIP,
    };
    
    Tile * tiles;
    Sprite ** sprite_list;
    int total_sprites;
    SDL_Rect clips[TOTAL_CLIP];
    void set_clip();
    void set_tile();
    int get_tile_pos(int x, int y);
    std::string file_name;
    int row,column, total_tile;
    Drawable * robot_master;
    Drawable * stick_master;
    SDL_Surface *robotSheet;
    SDL_Surface *stickSheet;
public:
    Level(std::string file_name, int row, int column);
    ~Level();
    void show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen);
    void interact_with_level(SDL_Rect *box);
    void set_sheet(SDL_Surface * robot, SDL_Surface * stick);
    //start to seperate stick and robot
    void handle_input(SDL_Event event);
    bool is_on_ground(SDL_Rect &box);
    HUMAN_STATE stick_on_level(SDL_Rect &box, int dir, int speed, HUMAN_STATE state);
    ROBOT_STATE robot_on_level(SDL_Rect &box, int dir, int speed, ROBOT_STATE state);
    void animate();
    enum LEVEL_STATE{
        PLAYING,
        WIN,
        LOSE,
    };
    LEVEL_STATE state;
    LEVEL_STATE get_level_state();
    
};

#endif /* defined(__ForScience__level__) */
