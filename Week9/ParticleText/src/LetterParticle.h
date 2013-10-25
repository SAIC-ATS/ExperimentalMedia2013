#pragma once


#include "BaseTextParticle.h"
#include "BaseParticleGroup.h"
#include "ParticleGroupMember.h"


class LetterParticle: public BaseTextParticle
{
public:
    LetterParticle(ofTrueTypeFont& font, const std::string& text);
    virtual ~LetterParticle();
    
    virtual void draw();

    virtual void kill();

};