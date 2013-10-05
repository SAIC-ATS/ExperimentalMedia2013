#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);

    x = ofGetWidth() / 2;
    y = 3;

    velocityX = -10;
    velocityY = 10;

    accelerationX = 3;//0.1;
    accelerationY = 3;

}

//------------------------------------------------------------------------------
void ofApp::update()
{

    x += velocityX; // aka x = x + velocityX;
    y += velocityY; // aka x = x + velocityX;

    velocityX += accelerationX;
    velocityY += accelerationY;

    
    // check the bottom boundary
    if(y > ofGetHeight())
    {
        velocityY *= -0.90; // velocityY = velocityY * -1.0;
        y = ofGetHeight();
    }

    // check the top boundary
    if(y < 0)
    {
        velocityY *= -0.90; // velocityY = velocityY * -1.0;
        y = 0;
    }

    // check the left boundary
    if(x > ofGetWidth())
    {
        velocityX *= -0.90; // velocityY = velocityY * -1.0;
        x = ofGetWidth();
    }

    // check the top boundary
    if(x < 0)
    {
        velocityX *= -0.90; // velocityY = velocityY * -1.0;
        x = 0;
    }



}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    ofFill();
    ofSetColor(255);
    ofCircle(x,y,10);

    ofDrawBitmapString("y="+ofToString(y)+"\n"+
                       "vy="+ofToString(velocityY),20,20);

}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
