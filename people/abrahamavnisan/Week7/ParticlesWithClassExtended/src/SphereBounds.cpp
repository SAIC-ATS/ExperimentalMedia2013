//
//  SphereBounds.cpp
//  ParticlesWithClass
//
//  Created by Abraham Avnisan on 10/9/13.
//
//

#include "SphereBounds.h"

SphereBounds::SphereBounds(float _x, float _y, float _r)
{
    x = _x;
    y = _y;
    r = _r;
    
}

void SphereBounds::draw()
{
    ofSetColor(0);
    ofNoFill();
    ofSetCircleResolution(200);
    ofCircle(x,y,r);
}

bool SphereBounds::isInside(float xPt, float yPt)
{
    return pow((xPt - x),2) + pow((yPt - y),2) < pow(r,2);
 }