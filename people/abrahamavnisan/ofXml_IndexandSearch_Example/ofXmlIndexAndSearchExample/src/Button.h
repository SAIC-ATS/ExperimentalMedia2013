#pragma once

#include "ofMain.h"
#include "BaseHandle.h"


class Button: public BaseHandle
{
public:
    
    // A TYPEDEF TO MAKE THINGS A LITTLE EASIER

        typedef std::shared_ptr<Button> SharedPtr;

    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)
    
        Button(const ofRectangle& rectanble, const string buttonText, const int fontSize);
        virtual ~Button();

    // A BASIC DRAW METHOD
    
        virtual void draw();
    
    // AND A FEW VARS
        
        string buttonText;
        int fontSize;
        ofTrueTypeFont buttonFont;
        bool drawOutline;
    
};