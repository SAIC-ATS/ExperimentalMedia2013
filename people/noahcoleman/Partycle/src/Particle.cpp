//
//  Particle.cpp
//  Partycle
//
//  Created by Noah Coleman on 10/7/13.
//
//

#include "Particle.h"
Particle::Particle(): age(0)
{
    // age = 0;
}

void Particle::update()
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

void Particle::draw()

{
    //int size = ofMap(age, 0, 500, 50, 0, true);

    ofSetColor(255);
    
    ofFill();
    ofCircle(position, 10);
   
}