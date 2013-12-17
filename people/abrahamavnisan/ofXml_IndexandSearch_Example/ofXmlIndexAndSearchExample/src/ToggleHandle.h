#pragma once

#include "ofMain.h"
#include "BaseHandle.h"


class ToggleHandle: public BaseHandle
{
public:
    
    // A TYPEDEF TO MAKE THINGS A LITTLE EASIER

        typedef std::shared_ptr<ToggleHandle> SharedPtr;

    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)
    
        ToggleHandle(const ofRectangle& rectangle);
        virtual ~ToggleHandle();

    // A BASIC DRAW METHOD

        void draw();
        
};