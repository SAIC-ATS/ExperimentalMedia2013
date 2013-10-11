#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofSetFrameRate(60);
    glEnable(GL_DEPTH_TEST);

    particleEmitter = new ParticleEmitter(600, 100, 1);
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    float dt = ofGetLastFrameTime();
    if (recording) dt = 1.0f/recordFps;
    if (!isPausing && !isRotating) particleEmitter->update(dt);
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        if (isRotating) {
            rotation += ofGetLastFrameTime() * rotationSpeed;
            ofRotateX(rotation);
            ofRotateY(rotation);
        }
        particleEmitter->draw();
    ofPopMatrix();

    if (!recording) {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps",10,15);
        ofDrawBitmapString("Hold p to freeze the particle system",10,30);
        ofDrawBitmapString("Hold r to freeze+rotate the particle system",10,45);
        ofDrawBitmapString("Hold the left mouse to have particles follow cursor",10,60);
        ofDrawBitmapString("Hold the right mouse to have the particles follow the oldest particles",10,75);
    }

    if (recording) {
        float elapsedTime = frame*1.0f/float(recordFps);
        if (elapsedTime >= recordTime) {
            system("ffmpeg -i data/%d.png -r 30 -qscale 0 data/test.avi");
            ofExit();
        }
        else ofSaveScreen(ofToString(frame)+".png");
        frame++;
    }
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'p') isPausing = true;
    if (key == 'r') isRotating = true;
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == 'p') isPausing = false;
    if (key == 'r') {
        isRotating = false;
        rotation = 0.0f;
    }
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(button == 0) particleEmitter->followMouse();
    else if(button == 2) particleEmitter->followParticles();
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(button == 0) particleEmitter->stopFollowingMouse();
    else if(button == 2) particleEmitter->stopFollowingParticles();
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

