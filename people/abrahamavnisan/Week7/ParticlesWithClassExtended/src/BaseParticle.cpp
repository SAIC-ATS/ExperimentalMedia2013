#include "BaseParticle.h"
#include "SphereBounds.h"
#include "ofApp.h"

BaseParticle::BaseParticle(string _word, int _velocityBounds):
    isDead(false),
    word(_word),
    velocityBounds(_velocityBounds),
    bounce(false)
{
    //not sure if these things belong here, but it's working and not sure where else to put them?
    verdana.loadFont("verdana.ttf", 30, true, false, false);
    int relPos = 200;
    int relSize = 260;
    stringBox = verdana.getStringBoundingBox(word,0,0);
    s1 = new SphereBounds(ofGetWidth()-relPos,ofGetWindowHeight(),ofGetWindowWidth()-relSize);
    s2 = new SphereBounds(relPos,0,ofGetWindowWidth()-relSize-10);
}

BaseParticle::~BaseParticle() // what does this do?
{
}

void BaseParticle::update()
{
    bounce = false;
    lastPosition = position; // record the last position
    velocity += acceleration;
    position += velocity;
    cout << "bottom left corner "  << !(((s1->isInside(position.x,position.y))                                  && (s2->isInside(position.x,position.y))))  << endl;
    cout << "top left corner "     << !(((s1->isInside(position.x,position.y+stringBox.height))                 && (s2->isInside(position.x,position.y+stringBox.height)))) << endl;
    cout << "bottom right corner " << !(((s1->isInside(position.x+stringBox.width,position.y))                  && (s2->isInside(position.x+stringBox.width,position.y))))  << endl;
    cout << "top right corner "    << !(((s1->isInside(position.x+stringBox.width,position.y+stringBox.height)) && (s2->isInside(position.x+stringBox.width,position.y+stringBox.height )))) << endl;
    cout << "string box height " << stringBox.height << endl;
    
    //if
    
// why doesn't this work correctly?
    
    if (
         !(((s1->isInside(position.x,position.y)) && (s2->isInside(position.x,position.y))) ) ||                                      //bottom left corner
        (!(((s1->isInside(position.x,position.y+stringBox.height)) && (s2->isInside(position.x,position.y+stringBox.height))) )) ||    //top left corner
        (!(((s1->isInside(position.x+stringBox.width,position.y)) && (s2->isInside(position.x+stringBox.width,position.y))))) ||      //bottom right corner
        (!(((s1->isInside(position.x+stringBox.width,position.y+stringBox.height)) &&                                                //top right corner
           (s2->isInside(position.x+stringBox.width,position.y+stringBox.height)))))
        )
        
    {
        position -= velocity; // make sure the word doesn't get 'caught' in the wall
        if (velocity.x>0)
        {
            velocity.x = (velocity.x+ofRandom(velocityBounds/2))*ofRandom(-0.95,-1.05);
        }
        else
        {
            velocity.x = (velocity.x+ofRandom(-velocityBounds/2,0))*ofRandom(-0.95,-1.05);
        }
        if (velocity.y>0)
        {
            velocity.y = (velocity.y+ofRandom(velocityBounds/2))*ofRandom(-0.95,-1.05);

        }
        else
        {
            velocity.y = (velocity.y+ofRandom(-velocityBounds/2,0))*ofRandom(-0.95,-1.05);
        }
    }
}

void BaseParticle::draw()
{
    
    s1->draw();
    s2->draw();
    
    //cout << "stringbox.x" << stringBox.x << endl;
    
    // we can calculate the heading of the
    // particle by looking at the velocity vector.
    
    //float heading = ofRadToDeg(atan2(velocity.y, velocity.x)); // is there a way to reverse this?  translate a heading into velocity.y and velocity.x

    // we will change the color based on the age
    ofSetColor(255);
    //ofSetColor(255,ofMap(age,0,maxAge,127,0));
    ofFill();

    // ofPushMatrix + ofTranslate + ofRotateZ ... + ofPopMatrix
     ofPushMatrix();
   
    ofTranslate(position);
    
    //ofRotateZ(heading); // rotate z angle
    
    // draw the string
    verdana.drawString(word, 0,0);
//    ofNoFill();
//    ofRect(stringBox.x, stringBox.y, stringBox.width, stringBox.height);
    
    ofPopMatrix();
}
