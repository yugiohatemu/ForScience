//
//  robotMaster.cpp
//  ForScience
//
//  Created by Yue on 7/5/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "robotMaster.h"
#include "utility.h"
#include "constant.h"

RobotMaster::RobotMaster(Level * level){
    total_robot = 2;
    
    robot_list = new Robot * [total_robot];
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i] = new Robot(level);
    }
    robot_list[1]->set_pos(TILE_WIDTH, 6*TILE_HEIGHT - ROBOT_HEIGHT);
}

RobotMaster::~RobotMaster(){
    for (int i = 0; i < total_robot; i +=1) {
        delete robot_list[i];
    }
    delete [] robot_list;
}

void RobotMaster::set_text(Text *text){
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i]->set_text(text);
    }
}

void RobotMaster::animate(){
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i]->animate();
    }

}


void RobotMaster::react_to(StickMaster *stick_master){
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i]->react_to(stick_master);
    }
}

void RobotMaster::show(SDL_Rect camera, SDL_Surface * tileSheet, SDL_Surface * screen){
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i]->show(camera, tileSheet, screen);
    }
}