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
    
    int lineOut;
    int yColor;
    int step;
    
    std::string buffer;
    ofTrueTypeFont	verdana30;
    ofTrueTypeFont	verdanaNumber;
    vector <string> byteLines;
    
    unsigned char lineNumber;
    bool binArray[8] = {0,0,0,0,0,0,0,0};
    bool stepArray[8] = {0,0,0,0,0,0,0,0};
    bool mouseControl;
    
		
};
