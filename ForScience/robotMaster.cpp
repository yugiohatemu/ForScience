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
#include "mission.h"


RobotMaster::RobotMaster(Level * level, int total_robot, int pos[]):Drawable(){
    this->total_robot= total_robot;
    robot_list = new Robot * [total_robot];
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i] = new Robot(level);
        robot_list[i]->set_pos(pos[i*2], pos[2*i+1]);
    }
    pause = false;
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

void RobotMaster::set_pause(bool p){
    pause = p;
}

void RobotMaster::animate(){
    if(pause) return ;
    if (LEVEL_PAUSE) return ;
    for (int i = 0; i < total_robot; i +=1) {
        robot_list[i]->animate();
    }
}

void RobotMaster::handle_input(SDL_Event event){
    
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