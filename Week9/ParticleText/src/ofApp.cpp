#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    font.loadFont("verdana.ttf", 40, true, true, true);

    particleSystem = std::shared_ptr<ParticleSystem>(new ParticleSystem());
    particleSystem->setup();

    currentWord = 0;

    // load our text
    std::string rawText = TextUtilities::loadFile("Lorem.txt");

    rawText = TextUtilities::stripPunctuation(rawText); // remove (some) punctuation

    words = TextUtilities::splitIntoWords(rawText);
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    particleSystem->update();
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    particleSystem->draw();

    ofDrawBitmapStringHighlight("# Particles: " + ofToString(particleSystem->getNumParticles()), 15, 15);
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    currentWord = (currentWord + 1) % words.size();

    std::string nextWord = words[currentWord];

    std::shared_ptr<BaseParticle> particle(new WordParticle(font,nextWord));

    particle->position = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    particle->velocity = ofVec2f(ofRandom(-5,5),ofRandom(-8,2));
    particle->acceleration = ofVec2f(0,.1);
    particle->maxAge = ofRandom(10,30);

    particle->particleSystem = particleSystem; // make a link back to the particle system

    particleSystem->addParticle(particle);
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
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
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
