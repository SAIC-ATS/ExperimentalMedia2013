#pragma once

#include "ofMain.h"

class BaseParticle
{
public:
    BaseParticle();
    virtual ~BaseParticle();

    virtual void update(float dt, bool targetPresent, ofVec3f target);
    virtual void draw();

    void printVertices();
    void calculateVertices();
    void calculateEquilateralTrianglePoints();
    void rotateHeadingTowardsTarget(ofVec3f target, float maxTurn, float t);
    void rotateUsingSmoothNoise(float t, float maxTurn);

    ofVec3f center;

    ofVec3f unrotatedHeading;
    ofVec3f heading;

    ofVec3f top;
    ofVec3f left;
    ofVec3f right;

    ofVec3f rotatedTop;
    ofVec3f rotatedLeft;
    ofVec3f rotatedRight;

    ofVec3f turningAngles;
    ofVec3f turningVelocity;

    float maxTurn;
    float distance;
    float velocity;
    float acceleration;
    float maxTurningRate;

    float radius;

    float age;
    float maxAge;
    bool isDead;

    float noiseOffset;
    float noiseScale;

};
