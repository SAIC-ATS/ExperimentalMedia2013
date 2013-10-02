#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetRectMode(OF_RECTMODE_CORNER);

    // Calculate the area that the series of lines will take up on the screen
    // This is used to position the drawing in the center of the screen
    lineAreaWidth = numberLines * lineWidth;

    // This is required to set up some initial variables
    // This is used to keep the drawing in the center of the screen
    windowResized(ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0,0,0);

    if (currentMode == MODE_RED_YELLOW_LINES) drawRedYellowLines();
    else if (currentMode == MODE_GRADIENT) drawGradient();
    else if (currentMode == MODE_GRADIENT_WITHOUT_LOOP) vboMesh.draw();

    drawScreenInstructions();
}

void testApp::drawRedYellowLines() {
    ofColor oddColor = ofColor(255,0,0);
    ofColor evenColor = ofColor(255,255,204);
    for (int lineNum=0; lineNum<numberLines; lineNum+=1) {
        if (lineNum%2==0) ofSetColor(evenColor);
        else ofSetColor(oddColor);
        int x = lineNum*lineWidth + startx;
        ofRect(x, starty, lineWidth, lineHeight);
    }
}

void testApp::drawGradient() {
    ofColor startColor = ofColor(255,0,0);
    ofColor endColor = ofColor(0,0,255);
    for (int lineNum=0; lineNum<numberLines; lineNum+=1) {
        // Find out how far we are along in drawing the lines as a fraction (between 0 and 1)
        float fraction = float(lineNum)/float(numberLines);

        // Use that fraction to linearly interpolate between the start color and end color
        //  NOTE: c must start out as a copy of the startColor because lerp works directly on a reference
        ofColor c = startColor;
        c.lerp(endColor, fraction);

        // Draw the 'line'
        ofSetColor(c);
        int x = lineNum*lineWidth + startx;
        ofRect(x, starty, lineWidth, lineHeight);
    }
}

void testApp::generateVboMesh() {

    // Start and end of our color gradient
    //  NOTE: Since we are creating a diagonal gradient our of four vertices,
    //        we will need a middle value
    ofColor startColor = ofColor(255,206,104);
    ofColor endColor = ofColor(182,0,200);
    ofColor middleColor = startColor;
    middleColor.lerp(endColor, 0.5);


    // Clear the current mesh and set the mode to triangle strips
    //  Triangle strings refers to how you have to order the vertices to create a face
    //  REF: http://www.openframeworks.cc/documentation/3d/ofMesh.html
    vboMesh.clear();
    vboMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    // Define the four vertices needed to generate two triangles in a strip
    ofVec2f topleft(startx, starty);
    ofVec2f topright(startx+lineAreaWidth, starty);
    ofVec2f bottomleft(startx, starty+lineHeight);
    ofVec2f bottomright(startx+lineAreaWidth, starty+lineHeight);

    // Add the vertices and color them to generate a diagonal gradient
    vboMesh.addVertex(topleft);
    vboMesh.addColor(startColor);
    vboMesh.addVertex(bottomleft);
    vboMesh.addColor(middleColor);
    vboMesh.addVertex(topright);
    vboMesh.addColor(middleColor);
    vboMesh.addVertex(bottomright);
    vboMesh.addColor(endColor);
}

// Draw instructions to the screen (with the currently selected mode highlighted)
void testApp::drawScreenInstructions() {

    // Set the color of the three text options based on the current mode
    ofColor text_color_1 = ofColor(255,255,255);
    ofColor text_color_2 = ofColor(255,255,255);
    ofColor text_color_3 = ofColor(255,255,255);
    if (currentMode == MODE_RED_YELLOW_LINES) text_color_1 = ofColor(255,0,0);
    else if (currentMode == MODE_GRADIENT) text_color_2 = ofColor(255,0,0);
    else if (currentMode == MODE_GRADIENT_WITHOUT_LOOP) text_color_3 = ofColor(255,0,0);

    // Draw the text options to the upper left of the screen
    ofSetColor(text_color_1);
    ofDrawBitmapString("press r to draw alternative red and yellow lines", 15, 30);
    ofSetColor(text_color_2);
    ofDrawBitmapString("press g to draw a gradient", 15, 60);
    ofSetColor(text_color_3);
    ofDrawBitmapString("press f to draw a gradient without a for loop", 15, 90);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

    // Update the variables used to position the lines in the center of the screen
    startx = w/2 - lineAreaWidth/2;
    starty = h/2 - lineHeight/2;

    // Regenerate the mesh so that it stays centered
    generateVboMesh();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    // Update the mode based on the key pressed
    if (key == 'r')         currentMode = MODE_RED_YELLOW_LINES;
    else if (key == 'g')    currentMode = MODE_GRADIENT;
    else if (key == 'f')    currentMode = MODE_GRADIENT_WITHOUT_LOOP;
}

//--------------------------------------------------------------
void testApp::update(){}



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
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
