#pragma once


#include "ofMain.h"
#include "ParticleSystem.h"
#include "TextUtilities.h"
#include "WordParticle.h"


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

    void newParticle();

    // we keep a shared pointer to our particle system
    std::shared_ptr<ParticleSystem> particleSystem;

    // this is the index of the word we will add with our next key press
    std::size_t currentWord;

    // this is a collection of words that we will emit from our particle system
    std::vector<std::string> words;

    // this is the font we will use
    ofTrueTypeFont font;
};
