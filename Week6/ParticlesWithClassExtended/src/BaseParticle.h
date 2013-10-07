#pragma once


#include "ofVec3f.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"

class BaseParticle
{
public:
    BaseParticle();
    virtual ~BaseParticle();

    virtual void update();
    virtual void draw();

    ofVec2f position;
    ofVec2f lastPosition;
    
    ofVec2f velocity;
    ofVec2f acceleration;

    int age;
    int maxAge;
    int isDead;

}; // don't forget the semi-colon after your class definition
