#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
    //ofToggleFullscreen();
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableAntiAliasing();
    ofEnableAlphaBlending();
    velocityBounds = 5;
    //maxNumberParticles = 10;
    
    myWP = new WordProcess("text.txt");
    words = myWP->process();
    addRandomParticle();

    
}

//------------------------------------------------------------------------------
void ofApp::update()
{
 
    //s1->update();
    
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

}

//------------------------------------------------------------------------------
void ofApp::draw()
{
    // monitor our FPS & other handy debugging stuff
//    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 10);
//    ofDrawBitmapString("velocity.x "+ofToString(myParticles[0]->velocity.x), 10, 20);
//    ofDrawBitmapString("velocity.y "+ofToString(myParticles[0]->velocity.y), 10, 30);
//    ofDrawBitmapString("position.x "+ofToString(myParticles[0]->position.x), 10, 40);
//    ofDrawBitmapString("position.y "+ofToString(myParticles[0]->position.y), 10, 50);
    
    //ofCircle(ofGetWidth()/2, ofGetHeight()/2, ofGetHeight()/2);

 
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
    if (key==' ')
    {
        reset();
    }
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
//{
//    ofPtr<BaseParticle> p;
//    for (int i=0; i<words.size(); i++)
//    {
//        p = ofPtr<BaseParticle>(new BaseParticle(words[i], velocityBounds));
//        p->position = ofVec2f(ofGetWidth()/3, ofGetHeight()/3);
//        p->velocity = ofVec2f(-.1,-.2);
//        p->acceleration = ofVec2f(0,0); // I want 0-gravity, so set the acceleration to 0
//        //p->maxAge = (int)ofRandom(10,100); // some particles will last longer than others.
//        
//        // we have an array of ofPtr (which holds a pointer to our base particle)
//        myParticles.push_back(p); // add the particle to the system
//    }
//}
//
//
// BELOW WORKS - ABOVE IS SANDBOX

{
    ofPtr<BaseParticle> p;
    for (int i=0; i<words.size(); i++)
    {
        p = ofPtr<BaseParticle>(new BaseParticle(words[i], velocityBounds));
        p->position = ofVec2f(ofGetWidth()/2 + ofRandom(-5,5), ofGetHeight()/3 + ofRandom(-5,5));
        p->velocity = ofVec2f(ofRandom(-velocityBounds,velocityBounds), ofRandom(-velocityBounds,velocityBounds));
        p->acceleration = ofVec2f(0,0); // I want 0-gravity, so set the acceleration to 0
        //p->maxAge = (int)ofRandom(10,100); // some particles will last longer than others.
        
        // we have an array of ofPtr (which holds a pointer to our base particle)
        myParticles.push_back(p); // add the particle to the system
    }
}
//------------------------------------------------------------------------------
void ofApp::reset()
{
    for(int i = myParticles.size() - 1; i >= 0; --i)
    {
        myParticles.erase(myParticles.begin() + i);
    }
    addRandomParticle();
}



