#pragma once


#include "BaseParticle.h"


class ParticleGroupMember: public BaseParticle
{
public:
    ParticleGroupMember();
    virtual ~ParticleGroupMember();

    virtual void draw();

};
