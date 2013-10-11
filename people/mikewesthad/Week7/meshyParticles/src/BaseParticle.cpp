#include "BaseParticle.h"

BaseParticle::BaseParticle():
    age(0), maxAge(10), radius(30), isDead(false) {

    unrotatedHeading = ofVec3f(0,0,1);
    heading = ofVec3f(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
    heading.normalize();
    center = ofVec3f(200,200,0);
    unrotatedHeading = ofVec3f(0,0,1);
    calculateEquilateralTrianglePoints();
    calculateVertices();
    velocity = 50.0f;
    noiseOffset = ofRandom(10000, 20000);
    noiseScale = 0.1;
    maxTurningRate = 180.0f;
}

BaseParticle::~BaseParticle() {}

void BaseParticle::calculateVertices() {
    // http://stackoverflow.com/questions/15101103/euler-angles-between-two-3d-vectors
    ofVec3f axisOfRotation = heading.getCrossed(unrotatedHeading);
    float rotationDegrees = ofRadToDeg(acos(heading.dot(unrotatedHeading)));
    rotatedTop = top.getRotated(rotationDegrees, axisOfRotation);
    rotatedLeft = left.getRotated(rotationDegrees, axisOfRotation);
    rotatedRight = right.getRotated(rotationDegrees, axisOfRotation);
}

// Assumes heading and target are both unit vectors
void BaseParticle::rotateHeadingTowardsTarget(ofVec3f target, float maxTurn, float t) {
    ofVec3f headingToTarget = target - center;
    headingToTarget.normalize();
    ofVec3f axisOfRotation  = heading.getCrossed(headingToTarget);
    float rotationDegrees = ofRadToDeg(acos(heading.dot(headingToTarget)));
    rotationDegrees = min(rotationDegrees, maxTurn);
    heading.rotate(rotationDegrees, axisOfRotation);
}

void BaseParticle::rotateUsingSmoothNoise(float t, float maxTurn) {

    float i1 = ofNoise((t+noiseOffset)*noiseScale)*2.0-1.0;
    float i2 = ofNoise((t+2*noiseOffset)*noiseScale)*2.0-1.0;
    float i3 = ofNoise((t+3*noiseOffset)*noiseScale)*2.0-1.0;
    ofVec3f axisOfRotation = ofVec3f(i1, i2, i3);
    axisOfRotation.normalize();
    heading.rotate(maxTurn, axisOfRotation);
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

    // We theoretically shouldn't need to normalize the heading since
    // we are only ever rotating it (and it starts at unit length), but
    // rounding errors will eventually accumulate, so let's be safe.
    heading.normalize();

    // Move the particle
    center += heading * distance;
    calculateVertices();

    // Update the age
    age += dt;
    if(age > maxAge) isDead = true;

}

void BaseParticle::draw() {
    ofSetColor(ofMap(age,0,maxAge,255,25), 0, 0);
    ofFill();
    ofTriangle(center+rotatedTop, center+rotatedLeft, center+rotatedRight);

    ofSetColor(ofMap(age,0,maxAge,255,25));
    ofLine(center, center+20*heading);
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

void BaseParticle::printVertices() {
    cout << "Top " << center+rotatedTop << endl;
    cout << "Left " << center+rotatedLeft << endl;
    cout << "Right " << center+rotatedRight << endl;
}
