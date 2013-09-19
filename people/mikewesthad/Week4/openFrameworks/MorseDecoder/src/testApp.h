#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		float estimateLEDIntensity();
		bool checkIfLEDIsOn(float intensity);
		string morseToEnglish(string m);
		float roundDotTime(float t);
		void drawEstimatedLED();

		void keyPressed(int key);

};
