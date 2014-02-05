#pragma once

#include "ofMain.h"
#include "BaseParticle.h"

class ParticleEmitter
{
    public:
        ParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime);
        virtual ~ParticleEmitter();

        void update(float dt);
        void draw();

        void emit(float dt);
        void emitParticles(float dt);
        void followMouse();
        void stopFollowingMouse();
        void followParticles();
        void stopFollowingParticles();
        void eraseParticle(int i);
        void createParticle();

        bool isFollowingMouse = false;
        bool isFollowingParticles = false;

        int maxNumberParticles;
        float emissionRate;
        std::vector< BaseParticle > particles;
        std::vector< int > particleTargets;
        int numberParticleTargets;

    protected:
    private:
};

