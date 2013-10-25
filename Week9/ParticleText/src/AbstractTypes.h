#pragma once


class BaseParticle;
class BaseParticleGroup;


class AbstractParticleSystem
{
public:
    typedef std::shared_ptr<AbstractParticleSystem> SharedPtr;
    typedef std::weak_ptr<AbstractParticleSystem>   WeakPtr;

    AbstractParticleSystem()
    {
    }

    virtual ~AbstractParticleSystem()
    {
    }

    virtual void addParticle(std::shared_ptr<BaseParticle> particle) = 0;

    virtual void addParticleGroup(std::shared_ptr<BaseParticleGroup> particleGroup) = 0;

    virtual std::size_t getNumParticles() const = 0;
};