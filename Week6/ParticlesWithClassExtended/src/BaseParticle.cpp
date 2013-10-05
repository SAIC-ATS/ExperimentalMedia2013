#include "BaseParticle.h"


BaseParticle::BaseParticle():
    age(0),
    maxAge(100),
    isDead(false) // initialization list
{
}

BaseParticle::~BaseParticle()
{
}

void BaseParticle::update()
{
    lastPosition = position; // record the last position

    age++;
    
    velocity += acceleration;
    position += velocity;

    if(age > maxAge) isDead = true;
}

void BaseParticle::draw()
{
    // we can calculate the heading of the
    // particle by looking at the velocity vector.
    float heading = ofRadToDeg(atan2(velocity.y, velocity.x));

    // we will change the color based on the age
    ofSetColor(255,ofMap(age,0,maxAge,127,0));
    ofFill();

    // ofPushMatrix + ofTranslate + ofRotateZ ... + ofPopMatrix
    ofPushMatrix();
    ofTranslate(position);
    ofRotateZ(heading); // rotate z angle

    // draw the filled circle
    ofCircle(0,0,10);

    // draw the outline of the circle
    ofNoFill();
    ofSetColor(255,ofMap(age,0,maxAge,255,0));
    ofCircle(0,0,10);

    // draw a heading line (this is pointing in the right direction
    // because we used ofRotateZ above ...
    ofLine(0,0,20,0);

    // pop the transformation matrix
    ofPopMatrix();
}
