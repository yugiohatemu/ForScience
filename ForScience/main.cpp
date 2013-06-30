//
//  main.cpp
//  ForScience
//
//  Created by Yue on 6/28/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//
// /Users/wei/Desktop/ForScience/ForScience/ current directory for loading image
// Should be replaced with relative directory dynamically in future

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include <iostream>
#include <string>
#include <fstream>
#include "timer.h"
#include "utility.h"
#include "tile.h"
#include "sprite.h"
#include "constant.h"
/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
 and may not be redistributed without written permission.*/


//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;

//Sprite from the tile sheet
SDL_Rect clips[ TILE_SPRITES ];
//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


bool init(){
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )return false;

    //Set the window caption
    SDL_WM_SetCaption( "For Science - 0.1", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    
    //Load the tile sheet
    tileSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/tiles.png" );
    if( tileSheet == NULL ) return false;
   
    //If everything loaded fine
    return true;
}

void clean_up( Tile *tiles[] )
{
    //Free the surfaces
    SDL_FreeSurface( tileSheet );
    
    //Free the tiles
    for( int t = 0; t < TOTAL_TILES; t++ ){
        delete tiles[ t ];
    }
    
    //Quit SDL
    SDL_Quit();
}

void clip_tiles(){
    //Clip the sprite sheet
    clips[ TILE_EMPTY ].x = 40;
    clips[ TILE_EMPTY  ].y = 0;
    clips[ TILE_EMPTY  ].w = TILE_WIDTH;
    clips[ TILE_EMPTY  ].h = TILE_HEIGHT;
    
    clips[ TILE_LADDER ].x = 80;
    clips[ TILE_LADDER ].y = 0;
    clips[ TILE_LADDER ].w = TILE_WIDTH;
    clips[ TILE_LADDER ].h = TILE_HEIGHT;
    
    clips[ TILE_FLOOR ].x = 120;
    clips[ TILE_FLOOR ].y = 0;
    clips[ TILE_FLOOR ].w = TILE_WIDTH;
    clips[ TILE_FLOOR ].h = TILE_HEIGHT;
    
    clips[ TILE_BACKWALL ].x = 200;
    clips[ TILE_BACKWALL ].y = 0;
    clips[ TILE_BACKWALL ].w = TILE_WIDTH;
    clips[ TILE_BACKWALL ].h = TILE_HEIGHT;
    
    clips[ TILE_BRICK ].x = 160;
    clips[ TILE_BRICK  ].y = 0;
    clips[ TILE_BRICK  ].w = TILE_WIDTH;
    clips[ TILE_BRICK  ].h = TILE_HEIGHT;

}


bool set_tiles( Tile *tiles[] ){
    //The tile offsets, use this later
    //int x = 0, y = 0;
    
    //Open the map
    std::ifstream map( "/Users/wei/Desktop/ForScience/ForScience/lazy.map" );
    
    for (int i = 0; i < TILE_ROW; i++) {
        for (int j = 0; j < TILE_COLUMN; j ++) {
            int tileType = -1;
            map >> tileType;
            if( map.fail() == true ){
                map.close();
                return false;
            }
            
            //If the number is a valid tile number, else close
            if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) ){
                tiles[ i * TILE_COLUMN + j  ] = new Tile(j * TILE_HEIGHT,i * TILE_WIDTH,  tileType );
            }else{ 
                map.close();
                return false;
            }
        }
    }
    
    //Close the file
    map.close();
    return true;
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    
    //Sprite myDot;
    Tile *tiles[ TOTAL_TILES ];
    Timer fps;
    
    //Initialize
    if( init() == false ) return 1;
    
    //Load the files
    if( load_files() == false )return 1;
    
    //Clip the tile sheet
    clip_tiles();
    
    //Set the tiles
    if( set_tiles( tiles ) == false ) return 1;
    
    //Continuous key press
    if(SDL_EnableKeyRepeat(300,300)<0) return 1;
    
    int last_time = 0;
    int cur_time = 0;
    int diff_time = 0;
    int accumulator = 0;
    Sprite * stick = new Sprite();
    //While the user hasn't quit
    while( quit == false ){
        //Start the frame timer
        //if want to process continuous key eveent, need to change this loop based on time
        
        fps.start();
        //stick->handle_input(event, tiles);
        
        while( SDL_PollEvent( &event )){
            if( event.type == SDL_QUIT )quit = true;
            //handle event
            stick->handle_input(event, tiles);
            
        }
        // Handle game world here
        cur_time = SDL_GetTicks();
        diff_time = cur_time - last_time;
        
        accumulator += diff_time;
        
        if(accumulator > 300){
            accumulator -= 300;
            stick->animate(); //change to bool maybe later
        }
        
        last_time = cur_time;
        
        //While there's events to handle
        //Move the dot //myDot.move( tiles );
        //Set the camera//myDot.set_camera();
        
        //Show 
        for( int t = 0; t < TOTAL_TILES; t++ ){
            tiles[ t ]->show(camera, tileSheet, screen, clips);
        }
        
        stick->show(camera, screen);
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }
        
        //Cap the frame rate, avoid overupdatting
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }
    
    
    //Clean up
    clean_up( tiles );
    delete stick;
    
    return 0;
}
