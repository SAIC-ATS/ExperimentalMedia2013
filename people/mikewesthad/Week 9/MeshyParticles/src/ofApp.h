#pragma once


#include "ofMain.h"
#include "MeshParticleEmitter.h"
#include "ParticleEmitter.h"
#include "BaseParticle.h"
#include "MeshParticle.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    MeshParticleEmitter * particleEmitter;

    bool areLightsOn = false;
    ofLight light;

    bool recording = false;
    int frame = 0;
    float recordTime = 20;
    float recordFps = 30;

    bool isPausing = false;
    bool isRotating = false;
    float rotation = 0.0f;
    float rotationSpeed = 45;

};
