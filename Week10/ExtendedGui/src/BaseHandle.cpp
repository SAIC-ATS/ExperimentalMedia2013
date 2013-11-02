#include "BaseHandle.h"


BaseHandle::BaseHandle():
    ofRectangle(),
    isOver(false),
    isDragging(false),
    color(ofColor(255,127)),
    colorOver(ofColor(255,255,0,127)),
    colorDragging(ofColor(0,255,0,127))
{
}

BaseHandle::BaseHandle(const ofRectangle& rectangle):
    ofRectangle(rectangle),
    isOver(false),
    isDragging(false),
    color(ofColor(255,127)),
    colorOver(ofColor(255,255,0,127)),
    colorDragging(ofColor(0,255,0,127))
{
}

BaseHandle::~BaseHandle()
{
}

void BaseHandle::update()
{
}

void BaseHandle::draw()
{
    if(isOver)
    {
        if(isDragging)
        {
            ofSetColor(colorDragging);
        }
        else
        {
            ofSetColor(colorOver);
        }
    }
    else
    {
        ofSetColor(color);
    }


    // fill
    ofFill();
    ofRect(x,y,width,height);
}

bool BaseHandle::hitTest(const ofVec2f& mouse)
{
    return inside(mouse);
}

