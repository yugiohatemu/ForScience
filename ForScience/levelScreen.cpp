//
//  levelScreen.cpp
//  ForScience
//
//  Created by Yue on 8/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "levelScreen.h"
#include "level.h"
#include "utility.h"
#include <sstream>
#include "screenController.h"
#include "endScreen.h"
#include "pauseScreen.h"
#include "levelSelectScreen.h"


LevelScreen::LevelScreen(int selected):Screen(){
    //add a new map,hehe
    std::stringstream str;
    str<<"/Users/wei/Desktop/ForScience/ForScience/level"<<selected<<".map";
    level = new Level(str.str()); //, 7,16
}


LevelScreen::~LevelScreen(){
    delete level;
}

void LevelScreen::set_sheet(SDL_Surface * robot, SDL_Surface * stick){
    level->set_sheet(robot, stick);
}


void LevelScreen::handle_input(SDL_Event event){
    
    if( event.type == SDL_KEYDOWN ){
        int dir = event.key.keysym.sym;
        if (dir == SDLK_ESCAPE) {
            ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
            root_controller->push_controller(new PauseScreen(this));
        }else{
            level->handle_input(event);
        }
    }else if (event.type == SDL_KEYUP){
        level->handle_input(event);
    }
}

void LevelScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    level->show(camera, tileSheet, screen);
    if (level->get_level_state() == Level::WIN) {
        EndScreen * winScreen = new EndScreen(true,this);
        ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
        root_controller->push_controller(winScreen);
    }else if(level->get_level_state() == Level::LOSE){
        EndScreen * loseScreen = new EndScreen(false,this);
        ScreenController * root_controller = dynamic_cast<ScreenController *>(root);
        root_controller->push_controller(loseScreen);
    }
    //if the we have some outcome?
    //do something
}

void LevelScreen::animate(){
    level->animate();
}