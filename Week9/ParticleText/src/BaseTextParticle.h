#pragma once


#include <string>
#include "ofTrueTypeFont.h"
#include "BaseParticle.h"


class BaseTextParticle: public BaseParticle
{
public:
    BaseTextParticle(ofTrueTypeFont& font, const std::string& text);
    virtual ~BaseTextParticle();

    virtual void draw();

    std::string getText() const;
    void setText(const std::string& text);

    ofTrueTypeFont& getFontRef();

protected:
    std::string _text;
    ofTrueTypeFont& _font;

};
