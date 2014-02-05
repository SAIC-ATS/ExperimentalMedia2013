#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // We'll be using alpha colors, so we need to let oF know
    ofEnableAlphaBlending();

    // Load the test movie and seek to the first frame
    movie.loadMovie("Fingers.mov");
    movie.firstFrame();

    // Allocate the memory for the ofImage and ofPixels
    lastDrawnScreen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    differencePixels.allocate(movie.width, movie.height, OF_IMAGE_COLOR_ALPHA);
    image.allocate(movie.width, movie.height, OF_IMAGE_COLOR);

    // Initialize the lastDrawnScreen
    lastDrawnScreen.setColor(ofColor::black);

    // Delay between frames used to compute difference
    frameDelay = 1;

    isFinished = false;
    captureFrame = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    // No new frame
    if (movie.getTotalNumFrames()-1 < movie.getCurrentFrame()+frameDelay) isFinished = true;

    // New frame
    if (!isFinished) {
        // Store the last frame
        lastFrame = movie.getPixelsRef();

        // Seek to the next frame
        movie.setFrame(movie.getCurrentFrame()+frameDelay);
        movie.update();

        // Compute the grayscale difference in intensity between the last frame and the next frame
        currentFrame = movie.getPixelsRef();
        for (int x=0; x<movie.width; x++) {
            for (int y=0; y<movie.height; y++) {
                ofColor lastColor = lastFrame.getColor(x,y);
                ofColor currentColor = currentFrame.getColor(x,y);
                float change = (currentColor.getLightness()-lastColor.getLightness())/2.0+127.5;
                ofColor newColor(change, change, change);
                differencePixels.setColor(x, y, newColor);
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    // Draw the last screen
    //  This hack is necessary to make ofImage.grabScreen() work
    //  The easier method would be to turn off the auto-clearing of the background
    //  but when you do that, grabScreen only returns a black image
    ofBackground(0);
    ofSetColor(255,255,255,255);
    lastDrawnScreen.draw(0,0);

    if (!isFinished) {

        ofSetColor(255,255,255,255);

        // Load and draw the last frame
        image.setFromPixels(lastFrame);
        image.draw(160,0);
        ofDrawBitmapString("Last Frame", 165, 10);

        // Load and draw the current frame
        image.setFromPixels(currentFrame);
        image.draw(160+movie.width,0);
        ofDrawBitmapString("Current Frame", 165+movie.width, 10);

        // Load and draw the difference between the two frames
        image.setFromPixels(differencePixels);
        image.draw(160+2*movie.width,0);
        ofDrawBitmapString("Difference Between Frames", 165+2*movie.width, 10);

        // Draw some lines only if the difference at a particular pixel exceeds a threshold
        // So this means that pixels that changed from a dark color to a light color will change
        ofPushMatrix();
            ofTranslate(movie.width, 40+movie.height);
            for (int x=0; x<movie.width; x++) {
                for (int y=0; y<movie.height; y++) {
                    float difference = differencePixels.getColor(x,y).getLightness();
                    float threshold = 180.0f;
                    if (difference > threshold) {
                        ofColor lineColor = currentFrame.getColor(x,y);
                        lineColor.a = 30;
                        ofSetColor(lineColor);
                        ofSetLineWidth((difference-threshold)/(255.0f-threshold) * 4.0f + 1.0f);
                        float heading = ofRandom(2.0f*PI);
                        float length = (difference-threshold)/(255.0f-threshold) * 80.0f + 5.0f;
                        int x1,x2,y1,y2;
                        x1 = 2*x;
                        y1 = 2*y;
                        x2 = x1 + length * cos(heading);
                        y2 = y1 + length * sin(heading);
                        ofLine(x1,y1,x2,y2);
                    }
                }
            }
        ofPopMatrix();


        // Save the last screen
        lastDrawnScreen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        lastDrawnScreen.saveImage("fingers-"+ofToString(captureFrame)+".png");
        captureFrame++;

    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
