#include "testApp.h"

#define NUMBER_OF_POSITIONS 50
int numberPositions = NUMBER_OF_POSITIONS;
int positions[NUMBER_OF_POSITIONS][2];
ofColor lineColors[NUMBER_OF_POSITIONS];

ofColor backgroundColor = ofColor(50,50,50);
ofColor circleColor = ofColor(255,255,255);

float circleWidth = 5;
float lineWidth = 1;

bool savingScreen = false;
int screenCaptureNumber = 0;


//--------------------------------------------------------------
void testApp::setup() {
    ofEnableSmoothing();
    ofSeedRandom();
    generatePoints();
}

void testApp::generatePoints() {
    // Generate the points, but also generate the color scheme
    //  Each point has an associated color that is a variation off
    //  a randomly selected hue.
    float randomHue = ofRandom(0, 255);
    for (int i=0; i<numberPositions; i++) {
        int x = ofRandomWidth();
        int y = ofRandomHeight();
        positions[i][0] = x;
        positions[i][1] = y;
        float randomSaturation = ofRandom(0, 255);
        float randomBrightness = ofRandom(0, 255);
        lineColors[i].setHsb(randomHue, randomSaturation, randomBrightness);
    }
}

void testApp::drawLewitt() {
    // Draw a line for each pair of circles
    //  Use the first point to determine the color of the line
    ofSetLineWidth(lineWidth);
    for (int p1=0; p1<numberPositions; p1++) {
        int x1 = positions[p1][0];
        int y1 = positions[p1][1];
        ofSetColor(lineColors[p1]);
        for (int p2=p1+1; p2<numberPositions; p2++) {
            int x2 = positions[p2][0];
            int y2 = positions[p2][1];
            ofLine(x1, y1, x2, y2);
        }
    }
    // Draw the circles last so that they are ontop of the lines
    for (int p1=0; p1<numberPositions; p1++) {
        int x1 = positions[p1][0];
        int y1 = positions[p1][1];
        ofFill();
        ofSetColor(circleColor);
        ofCircle(x1, y1, circleWidth);
    }
}

//--------------------------------------------------------------
void testApp::update(){

}


//--------------------------------------------------------------
void testApp::draw(){
    if (savingScreen)
        ofBeginSaveScreenAsPDF(ofToString(screenCaptureNumber)+".pdf");

    ofBackground(backgroundColor);
    drawLewitt();

    if (savingScreen) {
        ofEndSaveScreenAsPDF();
        savingScreen = false;
    }
    else {
        ofSetColor(ofColor::white);
        ofDrawBitmapString("Press s to print to a pdf", 10, 15);
    }


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 's') {
        savingScreen = true;
        screenCaptureNumber++;
    }

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
