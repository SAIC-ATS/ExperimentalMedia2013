#include "BaseTextParticle.h"


// we use initialization lists to set up our variables
BaseTextParticle::BaseTextParticle(ofTrueTypeFont& _font, const std::string& _text):
    font(_font),
    text(_text)
{
}

BaseTextParticle::~BaseTextParticle()
{
}

// this is our "Default" way of drawing.
void BaseTextParticle::draw()
{
    ofPushMatrix();
    ofTranslate(position);

    ofPushStyle();

    ofFill();
    ofSetColor(255);

    font.drawStringAsShapes(text,0,0);

    ofPopStyle();

    ofPopMatrix();
}
