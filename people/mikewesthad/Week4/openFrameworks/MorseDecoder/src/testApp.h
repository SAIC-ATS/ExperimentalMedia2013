#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		float estimateLEDIntensity();
		bool checkIfLEDIsOn(float intensity);
		bool approxEqual(float a, float b, float acceptableRange);
		string morseToEnglish(string m);

		void keyPressed(int key);

};
