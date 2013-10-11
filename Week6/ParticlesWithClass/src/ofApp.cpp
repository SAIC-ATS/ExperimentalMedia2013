#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{

//    myFirstParticle.position.x = 100;
//    myFirstParticle.position.y = 100;
//
//    myFirstParticle.velocity.x = 2;
//    myFirstParticle.velocity.y = 2;
//
//    mySecondParticle.position.x = 500;
//    mySecondParticle.position.y = 100;
//
//    mySecondParticle.velocity.x = -2;
//    mySecondParticle.velocity.y = 2;


    numParticles = 500;

    for(int i = 0; i < numParticles; i++)
    {
        BaseParticle particle;

        particle.position.x = ofGetWidth()/2;//ofRandom(0,ofGetWidth());  // random x position
        particle.position.y = ofGetHeight()/2;//ofRandom(0,ofGetHeight()); // random y position

        particle.velocity.x = ofRandom(-5,5);  // random x velocity
        particle.velocity.y = ofRandom(-5);  // random y velocity

        particle.acceleration.y = .4;

        myParticles.push_back(particle); // add it to our vector
    }


}

//------------------------------------------------------------------------------
void ofApp::update()
{
//    myFirstParticle.update();
//    mySecondParticle.update();

    for(int i = 0; i < numParticles; i++)
    {
        myParticles[i].update();
    }

}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

//    myFirstParticle.draw();
//    mySecondParticle.draw();

    for(int i = 0; i < numParticles; i++)
    {
        myParticles[i].draw();
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
