#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "127.0.0.1"
#define SEND_PORT 6666
#define RECIEVE_PORT 57131
#define NUM_MSG_STRINGS 20
#define BAUD_RATE 9600

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

		void readArduinoState();
		void sendUnityStateToArduino();
		void readUnityState();
		void sendArdunioStateToUnity();

		ofTrueTypeFont font;
		ofxOscSender sender;

		ofxOscReceiver receiver;
        string msg_string;
        int msg;

        ofSerial serial;
        int arduinoState = 0;
        int unityState = 0;

        ofColor bgColor = ofColor(0,0,0);
        ofColor ledOnColor = ofColor(255,255,0);
        ofColor ledOffColor = ofColor(153,153,0);
        ofColor ledDisconnectedColor = ofColor(0,0,0);
        ofColor outlineColor = ofColor(255,255,255);

        float numberChangeMessageSignals = 5;
        bool arduinoMessageChanged = false;
        float currentArduinoChangeMessageSignal = 0.0f;
        bool unityMessageChanged = false;
        float currentUnityChangeMessageSignal = 0.0f;

};
