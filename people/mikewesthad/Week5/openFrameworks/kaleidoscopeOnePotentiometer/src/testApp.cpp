/*
kaleidoscope

This program can be controlled with the mouse or by an arduino by setting
the variable currentMode to :
    MODE_CONTROLLED_BY_ARDUINO, or
        [Animation of the kaleidoscope where the potentiometer values control speed]
    MODE_CONTROLLED_BY_MOUSE
        [Mouse controls the frame of the animation so that interesting screenshots can be searched for]

The kaleidoscope works by taking an image (preferably high resolution), sampling a
triangular sliver of it and repeating that sliver to form a pie.  The specific part of
the image you are sampling can then be changed over time to create an animation.

The specifics of how that works are:
    Define a sliver of the image as a triangle that starts from the center
        of the image and points away at a particular angle.
    Use that sliver as a texture that is applied to an ofVbo mesh that is
        also a triangular shape.
    Draw that mesh on the display window.
    Rotate, draw a flipped version of the mesh...
    Repeat until you have circled all the way back to the first mesh.

*/

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // Set the mode for the program
//    currentMode = MODE_CONTROLLED_BY_MOUSE;
    currentMode = MODE_CONTROLLED_BY_ARDUINO;

    // Find the minimum dimension of the window for scaling the graphics
    // to fit on the screen
    minWindowDimension = min(ofGetWindowWidth(), ofGetWindowHeight());

    // Load the image
    image.loadImage("TownSunset.jpg");
    imageSectionCenter = ofVec2f(image.getWidth()/2, image.getHeight()/2);
    minImageDimension = min(image.getWidth(), image.getHeight());

    // Set up the initial variables that indicate where to sample the image
    imageSectionHeading = 90;
    triangleSlices = 20;
    triangleAngularWidth = 360.0/triangleSlices;
    rotationalSpeed = 15;

    // Generate the meshes that are used to take a slice of the image and
    // display it rotated and flipped around a circle
    vboMeshOriginal.setMode(OF_PRIMITIVE_TRIANGLES);
    vboMeshMirrored.setMode(OF_PRIMITIVE_TRIANGLES);
    generateVBOs();

    if (currentMode == MODE_CONTROLLED_BY_ARDUINO) initializeSerialReading();
}

void testApp::initializeSerialReading() {
    // Prepare for reading the arduino ouupts form the serial port
    //  you must use your own port number here!
    //  to find your port number on mac/linux/windows
    //  % ls -la /dev/tty.*
    serial.setup("COM5", BAUD_RATE);
    potValue = 0; // Potentiometer value
}

void testApp::processSerial() {
    // We read as many bytes as we can
    while(serial.available() > 0)
    {
        char myByte = serial.readByte();    // Read a single byte
        if(myByte == '\r') {}               // Ignore carriage return
        else if(myByte == '\n')             // Newline signals the end of a potentiometer value
        {
            potValue = ofToInt(buffer);
            buffer.clear();
        }
        else buffer += myByte;              // Append current char to our buffer
    }
}

void testApp::generateVBOs() {
    // If the meshes have already been generated once, we need to clear their data
    vboMeshOriginal.clear();
    vboMeshMirrored.clear();

    // Shorthand to make the equations more readable
    //  r is the radius of a circle that is inscribed by the display window
    //  a is the current angle heading we will use to sample the image
    //  da is half the span of the triangle
    float r = minWindowDimension/2.0;
    float a = ofDegToRad(imageSectionHeading);
    float da = ofDegToRad(triangleAngularWidth/2);

    // Define the vertices of the triangular face
	ofVec3f triangleBottom(0, 0, 0);
	ofVec3f triangleLeft(r*cos(a+da), -r*sin(a+da), 0);     // Flip because of drawing
	ofVec3f triangleRight(r*cos(a-da), -r*sin(a-da), 0);    // Flip because of drawing

    float cx = imageSectionCenter.x;
    float cy = imageSectionCenter.y;
    r = minImageDimension/2.0;

	// Define the triangular section of the image that we want to draw on the face
	ofVec2f textureBottom(cx, cy);
	ofVec2f textureLeft(cx+r*cos(a+da), cy-r*sin(a+da));
	ofVec2f textureRight(cx+r*cos(a-da), cy-r*sin(a-da));

    // Add the vertices to the VBO mesh to form a triangle
    addFace(vboMeshOriginal, triangleBottom, triangleLeft, triangleRight);
    addFace(vboMeshMirrored, triangleBottom, triangleLeft, triangleRight);

    // Add the texture coordinates to the mesh
    addTexture(vboMeshOriginal, textureBottom, textureLeft, textureRight);
    addTexture(vboMeshMirrored, textureBottom, textureRight, textureLeft);
}

// Mesh reference must be passed in
void testApp::addFace(ofVboMesh& vboMesh, ofVec3f top, ofVec3f left, ofVec3f right) {
	vboMesh.addVertex(top);
	vboMesh.addVertex(left);
	vboMesh.addVertex(right);
}

// Mesh reference must be passed in
void testApp::addTexture(ofVboMesh& vboMesh, ofVec2f top, ofVec2f left, ofVec2f right) {
    vboMesh.addTexCoord(top);
    vboMesh.addTexCoord(left);
    vboMesh.addTexCoord(right);
}

//--------------------------------------------------------------
void testApp::update(){
    if (currentMode == MODE_CONTROLLED_BY_ARDUINO) {
        processSerial();
        rotationalSpeed = ofMap(potValue, 0, 1023, -maxSpeed, maxSpeed);
        float elapsedTime = ofGetLastFrameTime();
        imageSectionHeading += rotationalSpeed * elapsedTime;
        generateVBOs();
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0,0,0);

    image.bind();
    ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        vboMeshOriginal.draw();

        for(int i=1; i<triangleSlices; i++) {
            ofRotate(triangleAngularWidth);
            if (i%2==0) vboMeshOriginal.draw();
            else        vboMeshMirrored.draw();

        }

    ofPopMatrix();
    image.unbind();

    if (showDisplayInfo) {
        // draw runtime information in bottom left corner
        ofDrawBitmapString("press h to hide/unhide this information", 10, ofGetWindowHeight()-105);
        ofDrawBitmapString("press w/s to increase/decrease the number of slices", 10, ofGetWindowHeight()-90);
        ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " FPS", 10, ofGetWindowHeight()-75);
        ofDrawBitmapString(ofToString((int) triangleSlices) + " Slices", 10, ofGetWindowHeight()-60);
        ofDrawBitmapString(ofToString((int) triangleAngularWidth) + " Degree Slice Width", 10, ofGetWindowHeight()-45);
        ofDrawBitmapString(ofToString((int) imageSectionHeading) + " Degree Current Angle", 10, ofGetWindowHeight()-30);
        ofDrawBitmapString(ofToString((int) rotationalSpeed) + " Degrees/Second Rotational Speed", 10, ofGetWindowHeight()-15);
    }

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'w') {
        triangleSlices += 2;
        triangleAngularWidth = 360.0/triangleSlices;
    }
    else if (key == 's' && triangleSlices>=6) {
        triangleSlices -= 2;
        triangleAngularWidth = 360.0/triangleSlices;
    }
    else if (key == 'h') showDisplayInfo = !showDisplayInfo;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    if (currentMode == MODE_CONTROLLED_BY_MOUSE) {
        imageSectionHeading = ofRadToDeg(atan2(y-ofGetWindowHeight()/2, x-ofGetWindowWidth()/2));
        generateVBOs();
    }

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
