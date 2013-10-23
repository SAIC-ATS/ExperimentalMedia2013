#pragma once


#include <vector>
#include "ParticleGroupMember.h"
#include "ofGraphics.h"


class BaseParticleGroup
{
public:
    BaseParticleGroup();
    virtual ~BaseParticleGroup();

    virtual void update();
    virtual void draw();

    std::vector<std::shared_ptr<ParticleGroupMember> > members;

    ofColor color;
};