#pragma once

#include "ofMain.h"

class BaseParticle
{
public:
    BaseParticle();
    virtual ~BaseParticle();

    virtual void update(float dt, bool targetPresent, ofVec3f target);
    virtual void draw();
    virtual ofVec3f calculateNormal(bool positive);

    void calculateVertices();
    void calculateEquilateralTrianglePoints();
    void rotateHeadingTowardsTarget(ofVec3f target, float maxTurn, float t);
    void rotateUsingSmoothNoise(float t, float maxTurn);

    ofVec3f center;

    ofVec3f heading;

    ofVec3f top;
    ofVec3f left;
    ofVec3f right;

    ofVec3f a;
    ofVec3f b;
    ofVec3f c;
    ofVec3f e;
    ofVec3f f;
    ofVec3f g;

    ofVec3f norm1;
    ofVec3f norm2;
    ofVec3f norm3;
    ofVec3f norm4;
    ofVec3f norm5;
    ofVec3f norm6;

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
