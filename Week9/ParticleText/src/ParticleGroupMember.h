#pragma once


#include "BaseParticle.h"


// this is a special particle that is not drawn
// this is a kind of a hack to prevent the particle system from
// drawing anything for this particle.  instead it will save the drawing
// for when the particle group is drawn.
class ParticleGroupMember: public BaseParticle
{
public:
    ParticleGroupMember();
    virtual ~ParticleGroupMember();

    virtual void draw();

};
