#pragma once


#include "ofMain.h"

// this is the header file
class ofApp: public ofBaseApp // ofApp "extends" the ofBaseApp class, which defines basic program functionality
{
public:
    void setup();
    void draw();

    int delayOne;
    int delayTwo;

    bool isOn;
};
