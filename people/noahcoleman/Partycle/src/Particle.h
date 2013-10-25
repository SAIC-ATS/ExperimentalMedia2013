//
//  Particle.h
//  Partycle
//
//  Created by Noah Coleman on 10/7/13.
//
//
#pragma once


#include "ofMain.h"
class Particle
{
public:
    Particle();
    
    void update();
    void draw();
    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    
    int age;
    
}; // don't forget the semi-colon after your class definition