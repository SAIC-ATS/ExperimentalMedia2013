//  Created by Abraham Avnisan on 12/8/13.

#include "Button.h"
#include "BaseHandle.h"


//--------------------------------------------------------------
Button::Button(const ofRectangle& rectangle, const string buttonText, const int fontSize):
BaseHandle(rectangle),
buttonText(buttonText),
fontSize(fontSize)
{
    buttonFont.loadFont("Verdana.ttf", fontSize, true, false, true);
    ofRectangle textBox = buttonFont.getStringBoundingBox(buttonText, x, y);
    x = textBox.x;
    y = textBox.y;
    width = textBox.width + 20;
    height = textBox.height + 10;
    // by default we draw button outlines, but this can be reset
    // manually as needed
    drawOutline = true;
}
//--------------------------------------------------------------
Button::~Button()
{
}
//--------------------------------------------------------------
void Button::draw()
{
    ofPushStyle();
    
    if (drawOutline)
    {
        if(isPressed)
        {
            ofSetColor(colorSelected);
            ofFill();
        }
        else
        {
            ofSetColor(color);
            ofNoFill();
        }
    }
    
    ofRectangle myRect(x,y,width,height);
    if (drawOutline) ofRectRounded(myRect, 5.0);
    
    float textWidth = buttonFont.stringWidth(buttonText);
    float textHeight = buttonFont.stringHeight(buttonText);
    float textXPos = x + ((width-textWidth)/2);
    float textYPos = y + ((height-textHeight)/2) + textHeight;
    buttonFont.drawString(buttonText, textXPos, textYPos);
    
    ofPopStyle();
}
//--------------------------------------------------------------