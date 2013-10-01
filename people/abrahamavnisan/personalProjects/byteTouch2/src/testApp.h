#pragma once


#include "ofMain.h"
#include "TouchPad.h"


using ofx::Input::TouchPad;
using ofx::Input::TouchPadRef;


class testApp: public ofBaseApp
{
public:
    void setup();
    void draw();
    void exit();
    
    void keyPressed(int key);
    
    void touchDown(ofTouchEventArgs& touch);
    void touchMoved(ofTouchEventArgs& touch);
    void touchUp(ofTouchEventArgs& touch);
    void touchDoubleTap(ofTouchEventArgs& touch);
    void touchCancelled(ofTouchEventArgs& touch);
    
    std::string touchToString(const ofTouchEventArgs& touch);
    
};