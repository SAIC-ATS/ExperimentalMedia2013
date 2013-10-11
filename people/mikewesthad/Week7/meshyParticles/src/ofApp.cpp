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

    particleEmitter->update(dt);
}

//------------------------------------------------------------------------------
void ofApp::draw()
{

    ofBackground(0);

    particleEmitter->draw();

    if (!recording) ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps",10,15);

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
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
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

