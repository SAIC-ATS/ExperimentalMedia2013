//
//  BaseParticle.cpp
//  ParticlesWithClass
//
//  Created by Christopher P. Baker on 10/4/13.
//
//

#include "BaseParticle.h"


BaseParticle::BaseParticle(): age(0)
{
// age = 0;
}

void BaseParticle::update()
{
    age++; // age = age + 1;

//    velocity.x += acceleration.x;
//    velocity.y += acceleration.y;
//    velocity.z += acceleration.z;
    velocity += acceleration;

//    position.x += velocity.x;
//    position.y += velocity.y;
//    position.z += velocity.z;

    position += velocity;
}

void BaseParticle::draw()
{
    //ofSetColor(255);
    ofSetColor(ofMap(age,0,50,255,0));

    ofFill();
    ofCircle(position,10);
}
