#pragma once


#include "ofVec3f.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"
#include "AbstractTypes.h"


class BaseParticle
{
public:
    BaseParticle();
    virtual ~BaseParticle();

    virtual void update();
    virtual void draw();

    virtual void kill();

    float getLife() const;

    ofVec2f position;
    ofVec2f lastPosition;
    
    ofVec2f velocity;
    ofVec2f acceleration;

    float heading;
    
    int age;
    int maxAge;
    bool isDead;

    std::shared_ptr<AbstractParticleSystem> particleSystem;


};