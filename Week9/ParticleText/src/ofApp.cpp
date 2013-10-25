#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    // we load our font with contours (see the docs for more info on the args)
    font.loadFont("verdana.ttf", 50, true, true, true);

    // we initialize a new particles system and wrap it in a shared pointer
    // so that we don't have to worry about calling `delete`.  Remember, if
    // you use the keyword 'delete' you MUST be sure that the memory is freed
    // via a `delete` OR make sure that mechanism (like a shared pointer) will
    // call it for you.
    particleSystem = std::shared_ptr<ParticleSystem>(new ParticleSystem());

    // an init method for us.
    particleSystem->setup();

    // initialize it!
    currentWord = 0;

    // load our text using our mini text utilities class.
    std::string rawText = TextUtilities::loadFile("Lorem.txt");

    // strip puntuation
    rawText = TextUtilities::stripPunctuation(rawText); // remove (some) punctuation

    // finally, get our words
    words = TextUtilities::splitIntoWords(rawText);
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    if(ofGetFrameNum() % 10 == 0)
    {
        newParticle();
    }

    // update the particle system
    particleSystem->update();
}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    // draw the particle system
    particleSystem->draw();

    // tell us the number of particles.  watch this number!
    ofDrawBitmapStringHighlight("# Particles: " + ofToString(particleSystem->getNumParticles()), 15, 15);
}

void ofApp::newParticle()
{
    // move to the next particle (remember what modulo does?)
    if(words.empty())
    {
        ofLogError("ofApp::newParticle") << "Words were not loaded.  New particles cannot be created.";
        return;
    }

    currentWord = (currentWord + 1) % words.size();

    std::string nextWord = words[currentWord];

    // create a particle, passing it the font and the next word.
    std::shared_ptr<BaseParticle> particle(new WordParticle(font,nextWord));

    // set the particle up -- playing with these numbers makes a big difference!
    particle->position = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    particle->velocity = ofVec2f(ofRandom(-5,5),ofRandom(-12,2));
    particle->acceleration = ofVec2f(0,.1);
    particle->maxAge = ofRandom(10,80);

    // make sure the particle knows about the particle system ...
    // because when the particle is killed, it will tell the particle
    // system to spawn _more_ particles.
    particle->particleSystem = particleSystem; // make a link back to the particle system

    // add the particle the particle system
    particleSystem->addParticle(particle);
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    newParticle();
    ofToggleFullscreen();
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
