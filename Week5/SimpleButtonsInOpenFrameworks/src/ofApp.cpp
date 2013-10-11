#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    
    buttons.push_back(ofRectangle(10,10,100,100));
    buttons.push_back(ofRectangle(120,10,100,100));
    buttons.push_back(ofRectangle(230,10,100,100));

    onColors.push_back(ofColor(255,0,0));
    onColors.push_back(ofColor(255,255,0));
    onColors.push_back(ofColor(0,0,255));

    offColors.push_back(ofColor(255,0,0,80));
    offColors.push_back(ofColor(255,255,0,80));
    offColors.push_back(ofColor(0,0,255,80));

    buttonState.push_back(false);
    buttonState.push_back(false);
    buttonState.push_back(false);

}

//------------------------------------------------------------------------------
void ofApp::update()
{
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    for(int i = 0; i < buttons.size(); i++)
    {
        ofFill();
        if(buttonState[i])
        {
            ofSetColor(onColors[i]);
        }
        else
        {
            ofSetColor(offColors[i]);
        }

        // draw the rectangle
        ofRect(buttons[i]);

        // record the virtual button state
        bool isOver = buttons[i].inside(ofGetMouseX(),ofGetMouseY());

        // draw a little highlight bar if the mouse is over
        if(isOver)
        {
            // make a new highlight bar rectangle, using the dimensions
            // of the button we are working with.
            ofRectangle tempRectangle(buttons[i].x,
                                      buttons[i].y+buttons[i].height+10,
                                      buttons[i].width,
                                      -10);
            // color and fill the highlight bar
            ofSetColor(255,127);
            ofFill();
            ofRect(tempRectangle);
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    // if this function is called, then we know a mouse button was pressed!
    // we also know where it was pressed by looking at the x / y location info.
    // we can use that x / y info to check to see if we pressed our rectangles.

    for(int i = 0; i < buttons.size(); i++)
    {
        bool isOver = buttons[i].inside(ofGetMouseX(),ofGetMouseY());

        if(isOver)
        {
            buttonState[i] = !buttonState[i]; // toggle the state!
        }

    }
}

