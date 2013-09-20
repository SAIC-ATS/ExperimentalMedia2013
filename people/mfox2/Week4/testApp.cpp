#include "testApp.h"

float xLocation [75];
float yLocation [75];

int rColor = 200;
int bColor = 120;
int gColor = 70;

float width;
float height;

bool imTired = false;

//--------------------------------------------------------------
void testApp::setup()
{
	totalPoints = 50;

	width = ofGetWidth();
	height = ofGetHeight();

	for(int fuckIt = 0; fuckIt < totalPoints; fuckIt++)
	{
		xLocation[fuckIt] = ofRandom(0, width);
		yLocation[fuckIt] = ofRandom(0, height);
	}
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	if(imTired == true)
	{
		ofBeginSaveScreenAsPDF("mfox2_Lewitt.pdf");

		ofBackground(0);
		ofSetColor(rColor, gColor, bColor);
		ofFill();

		for(int shitFace = 0; shitFace < totalPoints; shitFace++)
		{
			for(int scrap = 0; scrap < totalPoints; scrap++)
			{
				if(scrap != shitFace)
				{
					ofLine(xLocation[shitFace], yLocation[shitFace], xLocation[scrap], yLocation[scrap]);
				}
			}

			ofCircle(xLocation[shitFace], yLocation[shitFace], 5);
		}

		ofEndSaveScreenAsPDF();
		imTired = false;
	}
	
	ofBackground(0);
	ofSetColor(rColor, gColor, bColor);
	ofFill();

	for(int shitFace = 0; shitFace < totalPoints; shitFace++)
	{
		for(int scrap = 0; scrap < totalPoints; scrap++)
		{
			if(scrap != shitFace)
			{
				ofLine(xLocation[shitFace], yLocation[shitFace], xLocation[scrap], yLocation[scrap]);
			}
		}

		ofCircle(xLocation[shitFace], yLocation[shitFace], 5);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if(key == 32)
	{
		for(int fuckIt = 0; fuckIt < totalPoints; fuckIt++)
		{
			xLocation[fuckIt] = ofRandom(0, width);
			yLocation[fuckIt] = ofRandom(0, height);
		}
	}

	if(key == 's')
	{
		imTired = true;
	}
}
