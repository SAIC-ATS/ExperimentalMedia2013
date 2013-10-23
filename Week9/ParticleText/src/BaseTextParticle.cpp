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

    ofColor startColor = ofColor::white;
    ofColor endColor = ofColor::yellow;

    ofColor myColor = startColor.lerp(endColor, getLife());

    ofSetColor(myColor);

    std::string::iterator iter = text.begin();

    std::size_t offset = 0;

    while(iter != text.end())
    {
        std::string fragment(text.begin(), text.begin() + offset); // this will fail with some encodings
        std::string character(text.begin()+offset,text.begin()+offset +1);
        float xOffset = font.stringWidth(fragment); // hacky
        font.drawString(character,xOffset,0); // draw as a texture!
        ++iter;
        ++offset;
    }


    ofPopStyle();

    ofPopMatrix();
}
