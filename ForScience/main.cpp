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
SDL_Surface *dot = NULL;
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
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Move the Dot", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the dot image
    dot = load_image( "/Users/wei/Desktop/ForScience/ForScience/dot.bmp" );
    
    //If there was a problem in loading the dot
    if( dot == NULL )
    {
        return false;
    }
    
    //Load the tile sheet
    tileSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/tiles.png" );
    
    //If there was a problem in loading the tiles
    if( tileSheet == NULL )
    {
        return false;
    }
    
    //If everything loaded fine
    return true;
}

void clean_up( Tile *tiles[] )
{
    //Free the surfaces
    SDL_FreeSurface( dot );
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
    clips[ TILE_RED ].x = 0;
    clips[ TILE_RED ].y = 0;
    clips[ TILE_RED ].w = TILE_WIDTH;
    clips[ TILE_RED ].h = TILE_HEIGHT;
    
    clips[ TILE_GREEN ].x = 0;
    clips[ TILE_GREEN ].y = 80;
    clips[ TILE_GREEN ].w = TILE_WIDTH;
    clips[ TILE_GREEN ].h = TILE_HEIGHT;
    
    clips[ TILE_BLUE ].x = 0;
    clips[ TILE_BLUE ].y = 160;
    clips[ TILE_BLUE ].w = TILE_WIDTH;
    clips[ TILE_BLUE ].h = TILE_HEIGHT;
    
    clips[ TILE_TOPLEFT ].x = 80;
    clips[ TILE_TOPLEFT ].y = 0;
    clips[ TILE_TOPLEFT ].w = TILE_WIDTH;
    clips[ TILE_TOPLEFT ].h = TILE_HEIGHT;
    
    clips[ TILE_LEFT ].x = 80;
    clips[ TILE_LEFT ].y = 80;
    clips[ TILE_LEFT ].w = TILE_WIDTH;
    clips[ TILE_LEFT ].h = TILE_HEIGHT;
    
    clips[ TILE_BOTTOMLEFT ].x = 80;
    clips[ TILE_BOTTOMLEFT ].y = 160;
    clips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;
    
    clips[ TILE_TOP ].x = 160;
    clips[ TILE_TOP ].y = 0;
    clips[ TILE_TOP ].w = TILE_WIDTH;
    clips[ TILE_TOP ].h = TILE_HEIGHT;
    
    clips[ TILE_CENTER ].x = 160;
    clips[ TILE_CENTER ].y = 80;
    clips[ TILE_CENTER ].w = TILE_WIDTH;
    clips[ TILE_CENTER ].h = TILE_HEIGHT;
    
    clips[ TILE_BOTTOM ].x = 160;
    clips[ TILE_BOTTOM ].y = 160;
    clips[ TILE_BOTTOM ].w = TILE_WIDTH;
    clips[ TILE_BOTTOM ].h = TILE_HEIGHT;
    
    clips[ TILE_TOPRIGHT ].x = 240;
    clips[ TILE_TOPRIGHT ].y = 0;
    clips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
    clips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;
    
    clips[ TILE_RIGHT ].x = 240;
    clips[ TILE_RIGHT ].y = 80;
    clips[ TILE_RIGHT ].w = TILE_WIDTH;
    clips[ TILE_RIGHT ].h = TILE_HEIGHT;
    
    clips[ TILE_BOTTOMRIGHT ].x = 240;
    clips[ TILE_BOTTOMRIGHT ].y = 160;
    clips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
    clips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
}

bool set_tiles( Tile *tiles[] ){
    //The tile offsets
    int x = 0, y = 0;
    
    //Open the map
    std::ifstream map( "/Users/wei/Desktop/ForScience/ForScience/lazy.map" );
    
    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile will be made
        int tileType = -1;
        
        //Read tile from map file
        map >> tileType;
        
        //If the was a problem in reading the map Stop loading map
        if( map.fail() == true ){
            map.close();
            return false;
        }
        
        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y, tileType );
        }
        //If we don't recognize the tile type
        else{
            //Stop loading map
            map.close();
            return false;
        }
        
        //Move to next tile spot
        x += TILE_WIDTH;
        
        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;
            
            //Move to the next row
            y += TILE_HEIGHT;
        }
    }
    
    //Close the file
    map.close();
    
    //If the map was loaded fine
    return true;
}

bool touches_wall( SDL_Rect box, Tile *tiles[] ){
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() >= TILE_CENTER ) && ( tiles[ t ]->get_type() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    
    //If no wall tiles were touched
    return false;
}





int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    Sprite myDot;
    Tile *tiles[ TOTAL_TILES ];
    Timer fps;
    
    //Initialize
    if( init() == false ){
        return 1;
    }
    
    //Load the files
    if( load_files() == false ){
        return 1;
    }
    
    //Clip the tile sheet
    clip_tiles();
    
    //Set the tiles
    if( set_tiles( tiles ) == false ){
        return 1;
    }
    
    //While the user hasn't quit
    while( quit == false ){
        //Start the frame timer
        fps.start();
        
        //While there's events to handle
        while( SDL_PollEvent( &event )){
            //Handle events for the dot
            //myDot.handle_input(event);
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        
        //Move the dot //myDot.move( tiles );
        //Set the camera//myDot.set_camera();
        
        //Show 
        for( int t = 0; t < TOTAL_TILES; t++ ){
            tiles[ t ]->show(camera, tileSheet, screen, clips);
        }
        
        myDot.show(camera, dot, screen);
        
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
    
    return 0;
}
