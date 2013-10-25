//
//  BaseParticle.h
//  ParticlesWithClass
//
//  Created by Christopher P. Baker on 10/4/13.
//
//


#pragma once


// #include "ofMain.h" // or be more specific
#include "ofVec3f.h"
#include "ofGraphics.h"


class BaseParticle
{
public:
    BaseParticle();

    void update();
    void draw();

    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;

    int age;

}; // don't forget the semi-colon after your class definition
