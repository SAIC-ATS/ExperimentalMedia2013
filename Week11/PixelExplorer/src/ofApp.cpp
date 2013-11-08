#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    image.loadImage("image.png");
//    pixels = image.getPixelsRef(); // copy my pixels
//    pixels.resize(pixels.getWidth()*.05, pixels.getHeight()*.05); // resize my pixels

    ofEnableAlphaBlending();
    ofEnableDepthTest();

    grabber.initGrabber(40,30);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();

    if(grabber.isFrameNew())
    {
        pixels = grabber.getPixelsRef();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    camera.begin();

    ofPushMatrix();
    ofScale(1,-1);
    ofTranslate(- (pixels.getWidth() * 10) / 2, - (pixels.getHeight() * 10) / 2);

    for(std::size_t x = 0; x < pixels.getWidth(); ++x)
    {
        for(std::size_t y = 0; y < pixels.getHeight(); ++y)
        {
            ofColor color = pixels.getColor(x, y);

            float z = ofMap(color.getBrightness(), 0, 255, 0, 1024);

            ofVec3f position(x * 10, y * 10, z);

            ofFill();
            ofSetColor(color);
            ofEllipse(position, 10, 10);
        }
    }

    ofPopMatrix();

    camera.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
