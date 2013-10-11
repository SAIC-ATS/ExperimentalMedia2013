#pragma once

#include "ofMain.h"

class SphereBounds
{
public:
    virtual void draw(); // does this need to be virtual?
    
    float x;
    float y;
    float r;
    
    bool isInside (float xPos, float yPos);
    
    SphereBounds(float _x, float _y, float _r);

};