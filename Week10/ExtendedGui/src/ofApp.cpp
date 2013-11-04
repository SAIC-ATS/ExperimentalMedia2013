#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);

    theBoxBeingDragged.reset(); // this makes sure it is empty

    for(std::size_t i = 0; i < 10; ++i)
    {
        int width = ofRandom(10,50);
        int height = width;

        int x = ofRandom(width, ofGetWidth() - width);
        int y = ofRandom(height, ofGetHeight() - height);

        ofRectangle rectangle(x,        // x
                              y,        // y
                              width,    // width
                              height);  // height

        CircleHandle::SharedPtr circleHandle = CircleHandle::SharedPtr(new CircleHandle(rectangle));

        circleHandle->angle = ofRandom(360);

        boxes.push_back(circleHandle);
    }
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->update();
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->draw();
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    ofVec2f mouse(x,y);

    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        boxes[i]->isOver = boxes[i]->hitTest(mouse);
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    ofVec2f mouse(x,y);

    if(0 != theBoxBeingDragged) // check to see if our shared pointer contains a valid box
    {
        theBoxBeingDragged->setPosition(mouse - boxDragOffset);
    }
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofVec2f mouse(ofGetMouseX(),ofGetMouseY());

    for(std::size_t i = 0; i < boxes.size(); ++i)
    {
        if(boxes[i]->hitTest(mouse))
        {
            boxes[i]->isDragging = true;
            boxes[i]->isOver = true;

            boxDragOffset = mouse - boxes[i]->getPosition();

            theBoxBeingDragged = boxes[i];
            break; // break out of the for loop, you can't drag more than one at a time
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(0 != theBoxBeingDragged) // check to see if our shared pointer contains a valid box
    {
        theBoxBeingDragged->isDragging = false;
        theBoxBeingDragged.reset(); // clear our pointer
    }
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
