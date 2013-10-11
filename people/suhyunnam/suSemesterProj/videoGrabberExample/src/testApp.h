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
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
    unsigned char * pixels;
   // unsigned char * newPixels;
    float red;
    float green;
    float blue;
    
    float totalR;
    float totalG;
    float totalB;
    
    float avR;
    float avG;
    float avB;
    
    int num;
    
    std::vector<int> pixelsR;
     std::vector<int> pixelsG;
     std::vector<int> pixelsB;
    int totalPixels;
};
