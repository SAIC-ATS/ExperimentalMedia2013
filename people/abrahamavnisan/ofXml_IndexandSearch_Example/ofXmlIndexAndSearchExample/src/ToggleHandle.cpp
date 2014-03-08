//  Created by Abraham Avnisan on 12/8/13.

#include "ToggleHandle.h"
#include "BaseHandle.h"

//--------------------------------------------------------------
ToggleHandle::ToggleHandle(const ofRectangle& rectangle):
    BaseHandle(rectangle)
{
}
//--------------------------------------------------------------
ToggleHandle::~ToggleHandle()
{
}
//--------------------------------------------------------------
void ToggleHandle::draw()
{
    ofSetColor(color);
    
    ofNoFill();
    ofRect(x,y,width,height);
    
    if (isSelected)
    {
        ofPoint topLeft = getTopLeft();
        ofPoint topRight = getTopRight();
        ofPoint bottomLeft = getBottomLeft();
        ofPoint bottomRight = getBottomRight();
        
        ofLine(topLeft, bottomRight);
        ofLine(topRight, bottomLeft);
    }
}

