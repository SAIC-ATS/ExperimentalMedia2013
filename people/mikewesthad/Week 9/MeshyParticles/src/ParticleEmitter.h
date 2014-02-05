#pragma once

#include "ofMain.h"
#include "BaseParticle.h"

class ParticleEmitter
{
    public:
        ParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime);
        ParticleEmitter();
        virtual ~ParticleEmitter();

        virtual ofPtr<BaseParticle> createParticle();
        virtual void eraseParticle(int i);

        void update(float dt);
        void draw();
        void emitParticles(float dt);
        void updateParticles(float dt);
        void killParticles();

        void followMouse();
        void stopFollowingMouse();
        void followParticles();
        void stopFollowingParticles();

        int maxNumberParticles;
        float emissionRate;
        std::vector< ofPtr<BaseParticle> > particles;
        std::vector< int > particleTargets;
        int numberParticleTargets;
        bool isFollowingMouse;
        bool isFollowingParticles;

    protected:
    private:
};

