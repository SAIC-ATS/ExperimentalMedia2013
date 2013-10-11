#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

public:
	void setup();
    void draw();
    
    float r;
    
    vector<float> positionX;
    vector<float> positionY;

    };
