#pragma once


#include "ofMain.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);

    std::vector<ofRectangle> buttons;
    std::vector<ofColor> onColors;
    std::vector<ofColor> offColors;
    std::vector<bool> buttonState;

};
