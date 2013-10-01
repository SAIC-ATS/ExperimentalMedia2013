#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    // get the current time
    unsigned long long now = ofGetElapsedTimeMillis();

    // cycle through the rectangles
    for(int i = 0; i < numRectangles; i++)
    {
        // if now is past the next scheduled blink time
        if(now > nextRectangleBlinkTime[i])
        {
            // schedule the next blink time
            nextRectangleBlinkTime[i] = now + rectangleDelays[i];
            // toggle the rectangle state
            rectangleState[i] = !rectangleState[i];
        }

        // draw the rectangles
        if(rectangleState[i])
        {
            // draw an unfilled rectangle if the state is "true"
            ofNoFill();
        }
        else
        {
            // draw a filled rectangle if the state is "false"
            ofFill();
        }

        ofSetColor(ofColor::yellow);
        ofRect(rectangles[i]);

        // Uncomment the following to draw based on the amount of time left
        // before the next blink happens.
        
//        unsigned long long timeUntilNextBlink = nextRectangleBlinkTime[i] - now;
//
//        float percent = ofNormalize(timeUntilNextBlink,0,rectangleDelays[i]);
//
//        ofFill();
//        ofSetColor(255,0,0);
//        ofRect(rectangles[i].x,
//               rectangles[i].y + rectangles[i].height,
//               10,
//               -rectangles[i].height * percent);



    }
}
