//
//  tile.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "tile.h"
#include "utility.h"


Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;
    
    //Set the collision box
    box.w = 80;
    box.h = 80;
    
    //Get the tile type
    type = tileType;
}

void Tile::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen, SDL_Rect clips[]){
    
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        //Show the tile
        apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ type ] );
    }
}

int Tile::get_type(){
    return type;
}

SDL_Rect Tile::get_box(){
    return box;
}
