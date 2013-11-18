#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofToggleFullscreen();
    // We'll be using alpha colors, so we need to let oF know
    ofEnableAlphaBlending();

    image.allocate(1920, 1080, OF_IMAGE_COLOR);
    image.loadImage("image-1.jpeg");
    differencePixels.allocate(1920, 1080, OF_IMAGE_COLOR);
    lastDrawnScreen.allocate(1920, 1080, OF_IMAGE_COLOR_ALPHA);
    lastDrawnScreen.setColor(ofColor::black);

    isFinished = false;
    frameNum = 2;
    lastFrameNum = 100;
    captureFrame = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    if (frameNum > lastFrameNum) isFinished = true;

    if (!isFinished) {
        lastFrame = image.getPixelsRef();

        image.loadImage("image-"+ofToString(frameNum)+".jpeg");

        currentFrame = image.getPixelsRef();
        for (int x=0; x<1920; x++) {
            for (int y=0; y<1080; y++) {
                ofColor lastColor = lastFrame.getColor(x,y);
                ofColor currentColor = currentFrame.getColor(x,y);
                float change = (currentColor.getLightness()-lastColor.getLightness())/2.0+127.5;
                ofColor newColor(change, change, change);
                differencePixels.setColor(x, y, newColor);
            }
        }

        frameNum++;
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0);
    ofSetColor(255,255,255,255);
    lastDrawnScreen.draw(0,0);

    if (!isFinished) {
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for (int x=0; x<1920; x++) {
            for (int y=0; y<1080; y++) {
                float difference = differencePixels.getColor(x,y).getLightness();
                float threshold = 210.0f;

                ofColor lineColor = currentFrame.getColor(x,y);
                if (lineColor.b > lineColor.r && lineColor.b > lineColor.g) threshold = 160.0;
//                if (lineColor.getSaturation() < 5) threshold = 240.0;
//                if (lineColor.getSaturation() > 50) threshold = 160.0;

                if (difference > threshold) {
                    lineColor.a = 5;
                    ofSetColor(lineColor);
                    ofSetLineWidth((difference-threshold)/(255.0f-threshold) * 2.0f + 1.0f);
                    float heading = ofRandom(2.0f*PI);
                    float length = (difference-threshold)/(255.0f-threshold) * 80.0f + 5.0f;
                    int x1,x2,y1,y2;
                    x1 = x;
                    y1 = y;
                    x2 = x1 + length * cos(heading);
                    y2 = y1 + length * sin(heading);
                    ofLine(x1,y1,x2,y2);
                    mesh.addVertex(ofVec2f(x1, y1));
                    mesh.addColor(lineColor);
                    mesh.addVertex(ofVec2f(x2, y2));
                    mesh.addColor(lineColor);
                }
            }
        }
        mesh.draw();


        // Save the last screen
        lastDrawnScreen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        lastDrawnScreen.saveImage("gravity-"+ofToString(captureFrame)+".png");
        captureFrame++;
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
//    if (key == ' ') {
//        ofImage screenSave;
//        screenSave.allocate(1920,1080,OF_IMAGE_COLOR_ALPHA);
//        screenSave.grabScreen(0,0,1920,1080);
//        screenSave.saveImage("screenshot.png");
//    }

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
