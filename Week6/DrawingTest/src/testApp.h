#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofSerial serial;
    std::string buffer;
    
    int r;
    int g;
    int b;
    int x[50];
    int y[50];
    int rad;
    int x2[50];
    int y2[50];
    int i;
    int i2;
    int potValue;

		
};
