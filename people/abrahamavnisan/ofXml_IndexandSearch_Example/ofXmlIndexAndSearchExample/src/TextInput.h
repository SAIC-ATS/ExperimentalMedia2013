#pragma once

#include "ofMain.h"
#include "BaseHandle.h"


class TextInput: public BaseHandle
{
public:

    // A TYPEDEF TO MAKE THINGS A LITTLE EASIER

        typedef std::shared_ptr<TextInput> SharedPtr;

    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)

        TextInput(const ofRectangle& rectangle, string defaultText, bool isInteractive);
        virtual ~TextInput();
    
    // A BASIC DRAW METHOD

        void draw();

    // AND SOME VARS
    
        // an bool that determines whether the TextInput is interactive, ie
        // allows for text input.  If isInteractive = false, then TextInput
        // is a way to display text (we use it to display the path to the iTunes
        // root directory in the GUI
    
        bool isInteractive;
    
        ofTrueTypeFont textInputFont;
        string defaultText;
        int fontSize;    
    
};