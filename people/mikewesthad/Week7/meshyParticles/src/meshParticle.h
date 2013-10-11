#pragma once

#include "BaseParticle.h"
#include "ofMain.h"

class meshParticle: public BaseParticle {
    public:
        meshParticle();
        virtual ~meshParticle();

        void draw();
        void update(float dt);

        ofVec3f lastTop;
        ofVec3f lastLeft;
        ofVec3f lastRight;

        float temporalResolution = 0.01;
        float timer = 999999999.0;

        ofMesh mesh;
        int i=0;
};
