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
    
    ofTrueTypeFont 	verdana;
		
    bool push;
    string poem; // what's teh advantage of having this be a char array?
    string punct_array[3] = { "", "!", "?"}; // couldn't figure out how to initialize this array without specifying the number of elements in the brackets
    int i = 0;
    int i2 = 0;
};
