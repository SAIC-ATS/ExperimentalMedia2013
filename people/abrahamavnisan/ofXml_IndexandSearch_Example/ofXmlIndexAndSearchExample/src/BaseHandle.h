// BaseHandle class is based on an example written by Christopher Baker
// http://christopherbaker.net

#pragma once
#include "ofMain.h"

class BaseHandle: public ofRectangle
{
public:
    
    // A TYPEDEF TO MAKE THINGS A LITTLE EASIER
    
        typedef std::shared_ptr<BaseHandle> SharedPtr;
        
    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)
    
        BaseHandle(const ofRectangle& rectangle);
        virtual ~BaseHandle(); 
    
    // SOME PRETTY BASIC METHODS
    
        virtual void draw();
        virtual bool hitTest(const ofVec2f& mouse);
    
    // EVENT BOOLS
    
        bool isSelected;
        bool isPressed;
        bool isReleased;
    
    // A FEW VARS
    
        ofColor color;
        ofColor colorSelected;
};

