//  Created by Abraham Avnisan on 12/8/13.

#include "BaseHandle.h"

//--------------------------------------------------------------
BaseHandle::BaseHandle(const ofRectangle& rectangle):
ofRectangle(rectangle),
isReleased(false),
isSelected(false),
isPressed(false),
color(ofColor(0)),
colorSelected(ofColor(0,127))
{
}
//--------------------------------------------------------------
BaseHandle::~BaseHandle()
{
}
//--------------------------------------------------------------
void BaseHandle::draw()
{
    ofPushStyle();
    if(isPressed)
    {
        ofSetColor(colorSelected);
    }
    else
    {
        ofSetColor(color);
    }
    ofNoFill();
    ofRect(x,y,width,height);
    ofPopStyle();
}
//--------------------------------------------------------------
bool BaseHandle::hitTest(const ofVec2f& mouse)
{
    return inside(mouse);
}

