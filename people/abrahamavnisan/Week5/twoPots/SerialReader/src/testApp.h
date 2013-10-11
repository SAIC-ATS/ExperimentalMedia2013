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
    int pot1Value;
    int pot2Value;
    
    int lineOut;
    int yColor;
    
    std::string buffer;
    ofTrueTypeFont	verdana30;
    vector <string> byteLines;
    
    vector<string> serialInput;
    
		
};
