#include "BaseParticle.h"

BaseParticle::BaseParticle():
    age(0), maxAge(10), radius(50), isDead(false) {
    center = ofVec3f(0,0,0);
    calculateEquilateralTrianglePoints();
    heading = ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
    heading.normalize();
    top.rotate(heading.x, heading.y, heading.z);
    left.rotate(heading.x, heading.y, heading.z);
    right.rotate(heading.x, heading.y, heading.z);
    velocity = 500.0f;
    noiseOffset = ofRandom(10000, 20000);
    noiseScale = 0.1;
    maxTurningRate = 180.0f;
}

BaseParticle::~BaseParticle() {}

ofVec3f BaseParticle::calculateNormal(bool positive) {
    ofVec3f a = right - top;
    ofVec3f b = left - top;
    ofVec3f normal = a.cross(b).getNormalized();
    if (positive) return normal;
    else return -normal;
}

// Assumes heading and target are both unit vectors
void BaseParticle::rotateHeadingTowardsTarget(ofVec3f target, float maxTurn, float t) {
    ofVec3f heading = calculateNormal(true);
    ofVec3f headingToTarget = target - center;
    headingToTarget.normalize();
    ofVec3f axisOfRotation  = heading.getCrossed(headingToTarget);
    float rotationDegrees = ofRadToDeg(acos(heading.dot(headingToTarget)));
    rotationDegrees = min(rotationDegrees, maxTurn);
    top.rotate(rotationDegrees, axisOfRotation);
    left.rotate(rotationDegrees, axisOfRotation);
    right.rotate(rotationDegrees, axisOfRotation);
}

void BaseParticle::rotateUsingSmoothNoise(float t, float maxTurn) {
    float i1 = ofNoise((t+noiseOffset)*noiseScale)*2.0-1.0;
    float i2 = ofNoise((t+2*noiseOffset)*noiseScale)*2.0-1.0;
    float i3 = ofNoise((t+3*noiseOffset)*noiseScale)*2.0-1.0;
    ofVec3f axisOfRotation = ofVec3f(i1, i2, i3);
    axisOfRotation.normalize();
    top.rotate(maxTurn, axisOfRotation);
    left.rotate(maxTurn, axisOfRotation);
    right.rotate(maxTurn, axisOfRotation);
}

void BaseParticle::update(float dt, bool targetPresent, ofVec3f target) {

    // Based on the time interval, figure out some variables
    maxTurn = maxTurningRate * dt;
    velocity += acceleration * dt;
    distance = velocity * dt;

    // Update the heading
    if (targetPresent) {
        rotateHeadingTowardsTarget(target, maxTurn, age);
        rotateUsingSmoothNoise(age, 0.5);
    }
    else rotateUsingSmoothNoise(age, maxTurn);

    // Move the particle
    center += calculateNormal(true) * distance;

    // Update the age
    age += dt;
    if(age > maxAge) isDead = true;

}

void BaseParticle::draw() {
    ofSetColor(ofMap(age,0,maxAge,255,25), 0, 0);
    ofFill();
    ofTriangle(center+top, center+left, center+right);

    ofSetColor(ofMap(age,0,maxAge,255,25));
    ofLine(center, center+radius*calculateNormal(true));
}

void BaseParticle::calculateEquilateralTrianglePoints() {
    // Calculate the points of an equilateral triangle from its center and a radius
    //  The radius describes a circle that circumscribes the traingle (http://en.wikipedia.org/wiki/Equilateral_triangle)
    //  Triangle is in the XY plane (i.e. z=0) and has its center at the origin
    //  The top coordinate can then be found easily by moving up in the y direction by the radius
    //  The left and right coordinates can be found by rotating the top coordinate by -120 and 120 degrees respectively
    //      Rotation formulae:  x' = x*cos(r) - y*sin(r)
    //                          y' = x*sin(r) + y*cos(r
    top = ofVec3f(0.0f, 0.0f, 0.0f);
    top.y = -radius;
    left = ofVec3f(0.0f, 0.0f, 0.0f);
    left.x = -top.y * sin(ofDegToRad(-120));
    left.y = top.y * cos(ofDegToRad(-120));
    right = ofVec3f(0.0f, 0.0f, 0.0f);
    right.x = -top.y * sin(ofDegToRad(+120));
    right.y = top.y * cos(ofDegToRad(+120));
}
