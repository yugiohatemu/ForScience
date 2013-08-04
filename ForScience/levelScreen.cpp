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

LevelScreen::LevelScreen(int selected):Screen(){
    //add a new map,hehe
    std::stringstream str;
    str<<"/Users/wei/Desktop/ForScience/ForScience/level"<<selected<<".map";
    level = new Level(str.str(), 7,16);
}

LevelScreen::~LevelScreen(){
    delete level;
}

void LevelScreen::set_sheet(SDL_Surface * robot, SDL_Surface * stick){
    level->set_sheet(robot, stick);
}


void LevelScreen::handle_input(SDL_Event event){
    level->handle_input(event);
}

void LevelScreen::show(SDL_Rect camera,  SDL_Surface *tileSheet, SDL_Surface *screen){
    level->show(camera, tileSheet, screen);
}

void LevelScreen::animate(){
    level->animate();
}