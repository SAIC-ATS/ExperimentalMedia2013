#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "ofxCameraSaveLoad.h"



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
    
    ofEasyCam                   camera;
    bool                        enableEasyCam;
    
    ofxBulletWorldRigid			world;
    vector <ofxBulletBox*>		bounds;
	float						boundsWidth;
    ofxBulletBox				ground;
	ofxBulletSphere*			sphere;
    
    ofVec3f                     axis;
    float                       angle;
    
    // debug and gui tools
    bool                        displayStats;
    std::string makeInfoString(ofVec3f axis, float angle);
    
    // typography
    
    ofTrueTypeFont              font;
//    ofNode                      myNode;

};
