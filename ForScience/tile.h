//
//  tile.h
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef ForScience_tile_h
#define ForScience_tile_h
#include "SDL/SDL.h"

//The tile
class Tile
{
private:
    //The attributes of the tile
    SDL_Rect box;
    
    //The tile type
    int type;
    
public:
    //Initializes the variables
    Tile( int x, int y, int tileType );
    
    //Shows the tile
    void show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen, SDL_Rect clips[]);
    
    //Get the tile type
    int get_type();
    
    //Get the collision box
    SDL_Rect get_box();
};

#endif
