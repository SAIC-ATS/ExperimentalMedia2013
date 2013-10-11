#pragma once

#include "ofMain.h"
#include "SphereBounds.h"
//#include "ofVec3f.h"
//#include "ofGraphics.h"
//#include "of3dGraphics.h"

class BaseParticle
{
public:
    BaseParticle(string _word, int _velocityBounds);
    virtual ~BaseParticle();

    virtual void update();
    virtual void draw();
    
    ofVec2f position;
    ofVec2f lastPosition;
    
    ofVec2f velocity;
    ofVec2f acceleration;

    //int age;
    //int maxAge;
    int isDead;
    int velocityBounds;
    bool bounce;
    ofTrueTypeFont verdana;
    string word;
    ofRectangle stringBox;
    
    SphereBounds *s1;
    SphereBounds *s2;


}; // don't forget the semi-colon after your class definition
