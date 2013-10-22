#include "BaseTextParticle.h"


BaseTextParticle::BaseTextParticle(ofTrueTypeFont& font, const std::string& text):
    _font(font),
    _text(text)
{
}

BaseTextParticle::~BaseTextParticle()
{
}

void BaseTextParticle::draw()
{
    ofPushMatrix();
    ofTranslate(position);

    ofPushStyle();

    ofFill();
    ofSetColor(255);

    _font.drawStringAsShapes(_text,0,0);

    ofPopStyle();

    ofPopMatrix();
}

std::string BaseTextParticle::getText() const
{
    return _text;
}

void BaseTextParticle::setText(const std::string& text)
{
    _text = text;
}

ofTrueTypeFont& BaseTextParticle::getFontRef()
{
    return _font;
}
