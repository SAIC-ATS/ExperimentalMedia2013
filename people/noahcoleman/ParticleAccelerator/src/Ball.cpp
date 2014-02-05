//
//  Ball.cpp
//  ParticleAccelerator
//
//  Created by Noah Coleman on 10/10/13.
//
//

#include "Ball.h"
Ball::Ball(): age(0)
{
}

void Ball::update(){
    age ++;
    velocity += acceleration;
    position += velocity;
}

void Ball::draw(){
    ofSetColor(255);
    ofFill();
    ofCircle(position, 15);
}