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

		void addFace(ofVboMesh& vboMesh, ofVec3f top, ofVec3f left, ofVec3f right);
		void addTexture(ofVboMesh& vboMesh, ofVec2f top, ofVec2f left, ofVec2f right);
		void generateVBOs();
		void initializeSerialReading();
		void processSerial();

		ofImage image;
        int minImageDimension;

        int triangleSlices;
        float triangleAngularWidth;
        float imageSectionHeading;
        ofVec2f imageSectionCenter;
        float rotationalSpeed;

        int minWindowDimension;
		ofVboMesh vboMeshOriginal;
		ofVboMesh vboMeshMirrored;

		int currentMode;
		const int MODE_CONTROLLED_BY_MOUSE = 0;
		const int MODE_CONTROLLED_BY_ARDUINO = 1;
		bool showDisplayInfo = true;

		ofSerial serial;
		int potValue;
		const int BAUD_RATE = 9600;
		std::string buffer;
		float maxSpeed = 180;
};
