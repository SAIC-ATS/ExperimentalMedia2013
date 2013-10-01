#pragma once


#include "ofMain.h"


class ofApp: public ofBaseApp
{
public:
    // here is an example of the project with normal arrays.
    // on some older compilers, you may not be able to assign
    // the values in the header file.  Thus, for the near future,
    // it is best to define your values in the void setup() function.

    static const int numRectangles = 3;
    ofRectangle rectangles[numRectangles] = { ofRectangle(10,10,100,100), ofRectangle(120,10,100,100), ofRectangle(230,10,100,100) };
    bool rectangleState[numRectangles] = { false, false, false };
    unsigned long long rectangleDelays[numRectangles] = { 250, 500, 1000 };
    unsigned long long nextRectangleBlinkTime[numRectangles] = { 0, 0, 0 };

    void setup();
    void draw();

};
