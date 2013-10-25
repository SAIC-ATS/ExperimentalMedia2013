#pragma once

#include "ofMain.h"

class miKim6 : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void drawButton();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofColor colors[3];
    ofSerial serial;
    ofRectangle vButton[3]; // three virtual buttons on the screen
    bool isClicked[3]; // store each button's status which changes by clicking inside the button.
    int h, w;
    unsigned char vLedStateBuffer[3];


};
