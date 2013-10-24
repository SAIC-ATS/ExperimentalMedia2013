#pragma once

#include "ParticleEmitter.h"
#include "MeshParticle.h"
#include "ofMain.h"

class MeshParticleEmitter: public ParticleEmitter {
    public:
        MeshParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime);
        virtual ~MeshParticleEmitter();

        ofPtr<BaseParticle> createParticle();
        void eraseParticle(int i);
        ofMesh mesh;

    protected:
    private:
};
