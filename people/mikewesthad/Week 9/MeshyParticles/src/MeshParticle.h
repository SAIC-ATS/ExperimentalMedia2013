#pragma once

#include "BaseParticle.h"
#include "ofMain.h"

class MeshParticle: public BaseParticle {
    public:
        MeshParticle();
        virtual ~MeshParticle();

        ofVec3f calculateNormal(bool positive, ofVec3f a, ofVec3f b, ofVec3f c);

        void draw();
        void update(float dt, bool targetPresent, ofVec3f target);

        ofVec3f lastTop;
        ofVec3f lastLeft;
        ofVec3f lastRight;

        bool drawNormals = false;

        float temporalResolution = 0.01;
        float timer = 999999999.0;

        ofMesh mesh;
        int vertNum=0;
};
