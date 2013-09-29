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

		void drawScreenInstructions();
        void drawRedYellowLines();
        void drawGradient();
        void generateVboMesh();

		int currentMode = 0;
		const int MODE_RED_YELLOW_LINES = 0;
		const int MODE_GRADIENT = 1;
		const int MODE_GRADIENT_WITHOUT_LOOP = 2;

        int startx;
        int starty;
		int numberLines = 256;
		int lineWidth = 3;
		int lineHeight = 256;
		int lineAreaWidth;

		ofVboMesh vboMesh;
};
