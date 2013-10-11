#pragma once
#include "ofMain.h"


class jaehyunParticle{

	public:
		jaehyunParticle();
		
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();		
    void keyPressed(int key);
    
    
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		std::string buffer;
    
    int age;
    ofTrueTypeFont testFont;
		vector <ofPoint> * attractPoints;
    
    ofTTFCharacter testChar;
    char letter;
    
    ofSerial serial;
    int potvalue;
    
    
};