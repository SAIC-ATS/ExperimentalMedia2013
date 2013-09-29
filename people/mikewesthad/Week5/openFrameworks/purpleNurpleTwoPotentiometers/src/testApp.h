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
		void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d);
		void addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c);
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
		void generateVboMesh();
		void spinMeshVertices();
		ofVec3f rotateVectorAroundPoint(ofVec3f v, ofVec3f centerVector, float degrees, ofVec3f rotationAxis);
		void warpMeshAroundNipples(ofVec3f rotationAxis);
		void processSerial();

        bool isArduinoConnected;

		ofImage image;
		ofImage imageInterested;
		ofImage imagePleased;
		ofImage imagePissed;
		ofImage imageScrewYou;

		ofVec3f leftNipple;
		ofVec3f rightNipple;
        ofVec3f z_axis = ofVec3f(0.f,0.f,1.f);

        float mouseAngle;
        float lastMouseAngle = 0;

        ofSerial serial;
        int BAUD_RATE = 9600;
        std::string buffer = "";
        int leftPotValue;
        float leftRotation;
        int rightPotValue;
        float rightRotation;

        int meshResolution = 20;
        ofVboMesh vboMesh;
        ofVboMesh warppedVboMesh;

        float twistRange = 360 * 15;



};
