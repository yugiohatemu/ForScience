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
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <string>
#include <fstream>
#include "timer.h"
#include "utility.h"
#include "sprite.h"
#include "constant.h"
#include "robot.h"
#include "level.h"

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;
SDL_Surface *robotSheet = NULL;
SDL_Surface *stickSheet = NULL;

//The font and font color that's going to be used
TTF_Font *font = NULL;
SDL_Color textColor = { 255, 255, 255 };
SDL_Surface * text = NULL;


bool init(){
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) return false;
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )return false;

    //Set the window caption
    SDL_WM_SetCaption( "For Science - 0.1", NULL );
    
    if( TTF_Init() == -1 ) return false;
    
    
    //If everything initialized fine
    return true;
}

bool load_files(){
    
    //Load the tile sheet
    tileSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/tiles.png" );
    if( tileSheet == NULL ) return false;
    
    stickSheet = load_image( "/Users/wei/Desktop/ForScience/ForScience/stickman.png" );
    if (stickSheet == NULL) return false;
    
    robotSheet = load_image("/Users/wei/Desktop/ForScience/ForScience/robot.png" );
    if (robotSheet == NULL) return false;
    
    font = TTF_OpenFont( "/Users/wei/Desktop/ForScience/ForScience/font.ttf", 28 );
    if (font == NULL) return false;
    
    
    //If everything loaded fine
    return true;
}

void clean_up( ){
    //Free the surfaces
    SDL_FreeSurface( tileSheet );
    SDL_FreeSurface( robotSheet);
    SDL_FreeSurface( stickSheet);
    
    //Free font
    SDL_FreeSurface( text );
    TTF_CloseFont(font);
    TTF_Quit();
   
    //Quit SDL
    SDL_Quit();
}



int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    Timer fps;
    SDL_Event event;
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    //Initialize
    if( init() == false ) {
        std::cerr<<"Init fail"<<std::endl;
        return 1;
    }
    
    //Load the files
    if( load_files() == false ){
        std::cerr<<"Load file fail"<<std::endl;
        return 1;
    }
    
    //Continuous key press
    if(SDL_EnableKeyRepeat(300,300)<0) return 1;
    
    int last_time = 0;
    int cur_time = 0;
    int diff_time = 0;
    int accumulator = 0;
    Sprite * stick = new Sprite();
    Robot * robot = new Robot();
    Level * level = new Level();
    //
    
    text = TTF_RenderText_Solid( font, "For Sci ence", textColor );
    if (text == NULL) return 1;
    
    //While the user hasn't quit
    while( quit == false ){
        fps.start();
       
        while( SDL_PollEvent( &event )){
            if( event.type == SDL_QUIT )quit = true;

            stick->handle_input(event, level);
        }
        
        // Handle game world here
        cur_time = SDL_GetTicks();
        diff_time = cur_time - last_time;
        
        accumulator += diff_time;
        
        if(accumulator > 300){
            accumulator -= 300;
            robot->animate(level);
        }
        
        last_time = cur_time;
        
        //While there's events to handle
        //Move the dot //myDot.move( tiles );
        //Set the camera//myDot.set_camera();
        
        level->show(camera, tileSheet, screen);
        stick->show(camera, stickSheet,screen);
        robot->show(camera, robotSheet, screen);
        
        //text
        apply_surface(0, 480, text, screen);
        
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
    clean_up();
    delete stick;
    delete robot;
    delete level;
    return 0;
}
