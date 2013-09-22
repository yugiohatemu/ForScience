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
#include "utility.h"
#include "constant.h"
#include "stopWatch.h"

//#include "level.h"
#include "text.h"
#include "menuScreen.h"
//#include "levelSelectScreen.h"
#include "screenController.h"
//#include "levelScreen.h"
//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;
SDL_Surface *robotSheet = NULL;
SDL_Surface *stickSheet = NULL;
SDL_Surface *menuSheet = NULL;
//The font and font color that's going to be used
TTF_Font *font = NULL;

//use dirty global variable to do it
bool LEVEL_PAUSE = true;

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
    
    menuSheet = load_image("/Users/wei/Desktop/ForScience/ForScience/menuTile.png" );
    if (menuSheet == NULL) return false;
    
    font = TTF_OpenFont( "/Users/wei/Desktop/ForScience/ForScience/font.ttf", 28 );
    if (font == NULL) return false;
    
    
    //If everything loaded fine
    return true;
}

void clean_up(){
    //Free the surfaces
    SDL_FreeSurface( tileSheet );
    SDL_FreeSurface( robotSheet);
    SDL_FreeSurface( stickSheet);
    SDL_FreeSurface( menuSheet);
    //Free font
    TTF_CloseFont(font);
    TTF_Quit();
   
    //Quit SDL
    SDL_Quit();
}



int main( int argc, char* args[] ){
    //Quit flag
    bool quit = false;
   
    StopWatch fps(0.2);
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
//    if(SDL_EnableKeyRepeat(200,200)<0) return 1;
    
        
    MenuScreen * menu_screen = new MenuScreen();
    ScreenController * screen_controller = new ScreenController(menu_screen);
    Text * text = new Text(0, 480, "For Science", font);
    
    //While the user hasn't quit
    fps.start();
    while( quit == false ){
        
        while( SDL_PollEvent( &event )){
            if( event.type == SDL_QUIT )quit = true;
            
        }
        
        if (fps.is_timeup()) {
            screen_controller->handle_input(event);
            screen_controller->animate();
            fps.start();
        }
        
        //While there's events to handle
        //Move the dot //myDot.move( tiles );
        //Set the camera//myDot.set_camera();
        
        screen_controller->show(camera, menuSheet, screen);

        //Update the screen
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }
        
//        //Cap the frame rate, avoid overupdatting
//        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
//            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
//        }
    }
    
    
    //Clean up
    clean_up();
    delete text;
    delete screen_controller;
    return 0;
}
