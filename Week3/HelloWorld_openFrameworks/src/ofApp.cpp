#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(1); // set our refresh / frame rate to 1 frame / second.

    delayOne = 500;
    delayTwo = 500;

    isOn = true;
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0); // set the background to black

    ofFill();  // tell the program that the next `ofSetColor` will set the FILL color

    if(isOn) {
        ofSetColor(255, 255, 0);  // set the color to yellow if `isOn` is TRUE
    } else {
        ofSetColor(255, 0, 0);  // set the color to red if `isOn` is FALSE
    }

    ofCircle(200,200,100); // draw a circle at x = 200, y = 200 with a radius of 100 pixels.

    isOn = !isOn; // toggle `isOn`.  In this case, "!" means "not".   So this can be read: isOn is equal to the opposite of what it is currently equal to.
}
