#pragma once


#include <string>
#include "ofTrueTypeFont.h"
#include "BaseParticle.h"


// this is our base text particle.
// all other text-related particles will extend this class.
// by creating a base class with both text and font, our sub classes
// don't have to worry about keeping their own copy of the info.


class BaseTextParticle: public BaseParticle
{
public:
    BaseTextParticle(ofTrueTypeFont& font, const std::string& text);
    virtual ~BaseTextParticle();

    virtual void draw();

    std::string text;
    ofTrueTypeFont& font;

};
