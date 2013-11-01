#include "BaseHandle.h"


BaseHandle::BaseHandle():
    box(ofRectangle(0,0,0,0)),
    isOver(false),
    isDragging(false)
{
}

BaseHandle::BaseHandle(const ofRectangle& rectangle):
    box(rectangle),
    isOver(false),
    isDragging(false)
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
    // fill
    ofFill();
    ofSetColor(255,255,0);
    ofRect(box);

    // outline
    ofNoFill();
    ofSetColor(255);
    ofRect(box);
}
