//
//  Ball.h
//  ParticleAccelerator
//
//  Created by Noah Coleman on 10/10/13.
//
//

#pragma once
#include "ofMain.h"

class Ball {
public:
    Ball();
    
    void update();
    void draw();
    
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    
    int age;
    bool alive;
    
};


