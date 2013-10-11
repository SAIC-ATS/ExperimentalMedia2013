#pragma once


#include "ofMain.h"
#include "BaseParticle.h"
#include "SpecialParticle.h"
#include "WordProcess.h"

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

    void addRandomParticle();
    
    void reset();

    int maxNumberParticles;
    int velocityBounds;

    std::vector< ofPtr<BaseParticle> > myParticles;

    ofEasyCam cam;
    
    vector<string> words;
    WordProcess *myWP;
    
};
