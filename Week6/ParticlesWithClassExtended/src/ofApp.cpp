#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    maxNumberParticles = 500;
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    // create a box that defines the screen (we'll use it to test if a particle
    // is still on the screen ...
    ofRectangle theScreen(0,0,ofGetWidth(),ofGetHeight());


    // iterate through the particles backward so we can delete items as we go.
    // this is best done with an std::vector<>::iterator, but we will do that
    // later.
    for(int i = myParticles.size() - 1; i >= 0; --i)
    {
        myParticles[i]->update();

        if(myParticles[i]->isDead || // is the particle too old?
           !theScreen.inside(myParticles[i]->position)) // or is the particle not on the screen?
        {
            // if yes to either, then erase the particle
            myParticles.erase(myParticles.begin() + i);
        }
    }

    // here we add particles until the particles have reached our max number
    // this allows us to make sure that we always have max number of particles
    // on screen.
    while(myParticles.size() < maxNumberParticles)
    {
        addRandomParticle();
    }

}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);

    // draw each particle according to its draw function
    for(int i = 0; i < myParticles.size(); ++i)
    {
        myParticles[i]->draw();
    }


// draw from the OUTSIDE of the particle ...

//    ofVboMesh mesh;
//    mesh.setMode(OF_PRIMITIVE_LINES);
//
//    for(int i = 0; i < myParticles.size(); ++i)
//    {
//        for(int j = i; j < myParticles.size(); ++j)
//        {
//            if(i != j && myParticles[i]->age > 5 && myParticles[j]->age > 5)
//            {
//                float distance = myParticles[i]->position.distance(myParticles[j]->position);
//                if(distance < 50 )
//                {
//                    mesh.addVertex(myParticles[i]->position);
//                    mesh.addColor(ofColor(255,255,0,ofMap(myParticles[i]->age,5,myParticles[i]->maxAge,255,0)));
//                    mesh.addVertex(myParticles[j]->position);
//                    mesh.addColor(ofColor(0,255,0,ofMap(myParticles[j]->age,5,myParticles[j]->maxAge,255,0)));
//                }
//            }
//        }
//    }
//
//    mesh.draw();


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

//------------------------------------------------------------------------------
void ofApp::addRandomParticle()
{

    bool randomValue = (ofRandom(60) < 50); // random boolean value!
                                            // or range is uniform betweeo
                                            // 0-60.  so it is MORE likely that
                                            // the value will be < 50
                                            // so this will mostly be true
                                            // and occasionally false.

    ofPtr<BaseParticle> p;

    if(randomValue)
    {
        p = ofPtr<BaseParticle>(new BaseParticle());
    }
    else
    {
        p = ofPtr<SpecialParticle>(new SpecialParticle());
    }

    // both kinds of particles have the same base parameters (inherited from
    // the base particle system).
    p->position = ofVec2f(ofGetWidth()/2 + ofRandom(-5,5), // random start x
                         ofGetHeight()/3 + ofRandom(-5,5)); // random start y

    p->velocity = ofVec2f(ofRandom(-.5,.5),
                          ofRandom(-1)).getNormalized() * ofRandom(1,10);

    p->acceleration.y = 0.2;  // we just set the acceleration of the particle

    p->maxAge = (int)ofRandom(10,100); // some particles will last longer than others.

    // we have an array of ofPtr (which holds a pointer to our base particle)
    myParticles.push_back(p); // add the particle to the system
}

