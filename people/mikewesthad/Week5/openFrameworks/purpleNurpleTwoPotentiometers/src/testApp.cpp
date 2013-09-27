/*
Purple Nurple Emulator

WARNING: Nurple only in good conscience.

The code loads an image and creates an ofVboMesh from it.
Two nipple positions are defined.
The potentiometers (or keyboard presses [z/x and n/m]) adjusts the pressure on the left and right nipples.
The mesh vertices are rotated around the nipples.

Nipples.  I feel like I can't comment this code seriously.
*/


#include "testApp.h"

void testApp::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

//--------------------------------------------------------------
void testApp::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

//--------------------------------------------------------------
void testApp::addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c) {
	mesh.addTexCoord(a);
	mesh.addTexCoord(b);
	mesh.addTexCoord(c);
}

//--------------------------------------------------------------
void testApp::addTexCoords(ofMesh& mesh, ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d) {
	addTexCoords(mesh, a, b, c);
	addTexCoords(mesh, a, c, d);
}

void testApp::generateVboMesh() {
    vboMesh.clear();
	vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);

    int w = image.width;
    int h = image.height;
	int s = meshResolution;

    for(int y=0; y < h-s; y+=s) {
		for(int x=0; x < w-s; x+=s) {
            float d = 0;
			ofVec3f nw(x, y, d);
			ofVec3f ne(x+s, y, d);
			ofVec3f sw(x, y+s, d);
			ofVec3f se(x+s, y+s, d);
			ofVec2f nwi(x, y);
			ofVec2f nei(x+s, y);
			ofVec2f swi(x, y+s);
			ofVec2f sei(x+s, y+s);

			addFace(vboMesh, nw, ne, se, sw);
            addTexCoords(vboMesh, nwi, nei, sei, swi);

		}
	}
	warppedVboMesh = vboMesh;
}

//--------------------------------------------------------------
void testApp::setup(){
    image.loadImage("GorillaSmall.jpg");
    imageInterested.loadImage("GorillaFace1.jpg");
    imagePleased.loadImage("GorillaFace2.jpg");
    imagePissed.loadImage("GorillaFace3.jpg");
    imageScrewYou.loadImage("GorillaFace4.jpg");

    leftPotValue = 0;
    rightPotValue = 0;
    serial.setup("COM5", BAUD_RATE);
    isArduinoConnected = false;

    leftNipple.set(380.f, 490.f, 0.f);
    rightNipple.set(575.f, 510.f, 0.f);

    generateVboMesh();
}

//--------------------------------------------------------------
void testApp::update(){

    if (isArduinoConnected) {
        processSerial();
        leftRotation = ofMap(leftPotValue,0,1023,-twistRange,twistRange);
        rightRotation = ofMap(rightPotValue,0,1023,-twistRange,twistRange);
    }

    warpMeshAroundNipples(z_axis);
}

void testApp::warpMeshAroundNipples(ofVec3f rotationAxis) {
    float maxDistance = ofDist(0, 0, image.width, image.height);

    int numVertices = vboMesh.getNumVertices();
    for (int i=0; i<numVertices; i++) {
        ofVec3f v = vboMesh.getVertex(i);

        float distance = ofDist(leftNipple.x, leftNipple.y, v.x, v.y);
        float rotation = leftRotation * pow(0.95, distance);
        v = rotateVectorAroundPoint(v, leftNipple, rotation, z_axis);

        distance = ofDist(rightNipple.x, rightNipple.y, v.x, v.y);
        rotation = rightRotation * pow(0.95, distance);
        v = rotateVectorAroundPoint(v, rightNipple, rotation, z_axis);

        warppedVboMesh.setVertex(i, v);
    }
}


ofVec3f testApp::rotateVectorAroundPoint(ofVec3f v, ofVec3f centerVector, float degrees, ofVec3f rotationAxis) {
    ofVec3f rotated = v - centerVector;
    rotated = rotated.getRotated(degrees, rotationAxis);
    rotated = rotated + centerVector;
    return rotated;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(ofColor::black);

    image.bind();
    warppedVboMesh.draw();
    image.unbind();

    // Update the gorilla's face depending on how acceptable he finds
    // your purple nurple abilities
    float currentTwist = abs(leftRotation)+abs(rightRotation);
    float maxTwist = 2*twistRange;
    if (currentTwist<maxTwist/5) { /* Leave original face */ }
    else if (currentTwist<2*maxTwist/5) imageInterested.draw(300, 0);
    else if (currentTwist<3*maxTwist/5) imagePleased.draw(300, 0);
    else if (currentTwist<4*maxTwist/5) imagePissed.draw(300, 0);
    else imageScrewYou.draw(300, 0);
}


void testApp::processSerial() {
    // We read as many bytes as we can
    while(serial.available() > 0)
    {
        char myByte = serial.readByte();    // Read a single byte
        if(myByte == '\r') {}               // Ignore carriage return
        else if(myByte == '\n')             // Newline signals the end of a potentiometer value
        {
            vector<string> line = ofSplitString(buffer, ",");
            if (line.size()==2) {
                leftPotValue = ofToInt(line[0]);
                rightPotValue = ofToInt(line[1]);
            }
            buffer.clear();
        }
        else buffer += myByte;              // Append current char to our buffer
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key=='e') leftPotValue -= 1;
    else if (key=='r') leftPotValue += 1;
    else if (key=='u') leftPotValue -= 1;
    else if (key=='i') leftPotValue += 1;
    else if (key==OF_KEY_RETURN) {
        ofImage screenshot;
        int w, h = ofGetWindowWidth(), ofGetWindowHeight();
        screenshot.allocate(w, h, OF_IMAGE_COLOR);
        screenshot.grabScreen(0, 0, w, h);
        screenshot.saveImage("screenshot_"+ofGetTimestampString()+".png");
    }

    if (key=='x') leftRotation += 90;
    if (key=='z') leftRotation -= 90;
    if (key=='m') rightRotation += 90;
    if (key=='n') rightRotation -= 90;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

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
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
