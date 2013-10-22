#pragma once


#include "BaseTextParticle.h"
#include "LetterParticle.h"
#include "TextUtilities.h"


class WordParticle: public BaseTextParticle
{
public:
    WordParticle(ofTrueTypeFont& font, const std::string& text);
    virtual ~WordParticle();

    void kill();
};