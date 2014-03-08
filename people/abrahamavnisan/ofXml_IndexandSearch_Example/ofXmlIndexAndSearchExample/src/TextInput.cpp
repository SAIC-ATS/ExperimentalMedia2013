//  Created by Abraham Avnisan on 12/8/13.

#include "TextInput.h"
#include "BaseHandle.h"

//--------------------------------------------------------------
TextInput::TextInput(const ofRectangle& rectangle, string defaultText, bool isInteractive):
BaseHandle(rectangle),
defaultText(defaultText),
isInteractive(isInteractive),
fontSize(12)
{
    textInputFont.loadFont("Verdana.ttf", fontSize);
}
//--------------------------------------------------------------
TextInput::~TextInput()
{
}
//--------------------------------------------------------------
void TextInput::draw()
{
    
    
    // the defaultText we pass to our constructor might be quite
    // long - longer than we have room for in our text box.  So
    // here we check that and truncate it if we have to
    int maxPathToPrint = 56; // this is the length (in Verdana characters at size 12)
                             // of the longest text box in this application
    int pathLength = defaultText.length();
    string truncatedText;
    if (pathLength > maxPathToPrint)
    {
        truncatedText = "...";
        truncatedText += defaultText.substr(pathLength - maxPathToPrint, maxPathToPrint);
    }
    else
    {
        truncatedText = defaultText;
    }
    
    ofPushStyle();
    
        if(isPressed && isInteractive)
        {
            ofSetColor(colorSelected);
            defaultText = "";
        }
        else
        {
            ofSetColor(color);
        }
    
        ofNoFill();
        ofRect(x,y,width,height);
        textInputFont.drawString(truncatedText, x+10, y+ (height-fontSize)/2 + fontSize);
    
    ofPopStyle();
}
