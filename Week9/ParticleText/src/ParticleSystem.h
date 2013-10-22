#pragma once


#include "ofMain.h"
#include "ofTypes.h"
#include "AbstractTypes.h"
#include "BaseParticle.h"
#include "BaseParticleGroup.h"


class ParticleSystem: public AbstractParticleSystem
{
public:
    typedef std::shared_ptr<ParticleSystem> SharedPtr;
    typedef std::weak_ptr<ParticleSystem> WeakPtr;

    ParticleSystem();
    virtual ~ParticleSystem();

    void setup();
    void update();
    void draw();

    void addParticle(std::shared_ptr<BaseParticle> particle);

    void addParticleGroup(std::shared_ptr<BaseParticleGroup> particleGroup);

    std::size_t getNumParticles() const;

private:
    std::vector<std::shared_ptr<BaseParticle> > _particles;
    std::vector<std::shared_ptr<BaseParticleGroup> > _groups;
    

};