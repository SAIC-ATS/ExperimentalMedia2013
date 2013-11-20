#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	cam.initGrabber(640, 480);

    // background subtraction setup
	background.setLearningTime(900);
	background.setThresholdValue(10);

    // tell the contour finder what kind of blobs we'll accept
    contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(200);

}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		background.update(cam, thresholded);
		thresholded.update();

        contourFinder.setThreshold(127);
		contourFinder.findContours(thresholded);

        polylines = contourFinder.getPolylines();
	}
}

void testApp::draw() {
    ofBackground(0);
	cam.draw(0, 0);
    ofPushMatrix();
    ofTranslate(640,0);

    ofNoFill();
    ofSetColor(255,255,0);
    for(std::size_t i = 0; i < polylines.size(); ++i)
    {
        ofPolyline poly = polylines[i];

        poly.simplify();

        poly = poly.getResampledBySpacing(25);

        for(std::size_t j = 0; j < poly.size(); ++j)
        {
            ofVec2f point = poly.getVertices()[j];

            ofCircle(point.x, point.y, 4);

        }

    }


    ofPopMatrix();
}

void testApp::keyPressed(int key) {
	if(key == ' ') {
		background.reset();
	}
}