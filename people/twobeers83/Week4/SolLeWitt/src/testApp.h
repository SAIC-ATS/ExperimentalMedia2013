#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
        void setup();
        void draw();

		void keyPressed(int key);
		void keyReleased(int key);
    
    bool newDrawing;
    
    
		
};
