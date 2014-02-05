#include "MeshParticleEmitter.h"

MeshParticleEmitter::MeshParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime){
    maxNumberParticles = _maxNumberParticles;
    emissionRate = _emissionRate;
    numberParticleTargets = 0.2 * maxNumberParticles;
    emitParticles(_prewarmTime);

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableNormals();
    mesh.enableIndices();
}

MeshParticleEmitter::~MeshParticleEmitter(){}

ofPtr<BaseParticle> MeshParticleEmitter::createParticle() {
    ofPtr<MeshParticle> ptr(new MeshParticle());
    ptr->center = ofVec3f(ofRandom(-50,50), ofRandom(-50,50), ofRandom(-50,50));
    ptr->velocity = ofRandom(200,400);
    return ptr;
}

void MeshParticleEmitter::eraseParticle(int i) {
    int vertNum = mesh.getNumIndices();

//    ofPtr<MeshParticle> p(*((MeshParticle*)&particles[i]));
    MeshParticle *p = dynamic_cast<MeshParticle*>(particles[i]);
    vector<ofMeshFace> faces = p->mesh.getUniqueFaces();
    for (int i=0; i<faces.size(); i++) {
        ofMeshFace face = faces[i];
        mesh.addVertex(face.getVertex(0));
        mesh.addIndex(vertNum);
        mesh.addVertex(face.getVertex(1));
        mesh.addIndex(vertNum+1);
        mesh.addVertex(face.getVertex(2));
        mesh.addIndex(vertNum+2);
        mesh.addTriangle(vertNum, vertNum+1, vertNum+2);
        mesh.addNormal(face.getFaceNormal());
        vertNum+=3;
    }

    particles.erase(particles.begin()+i);
    if (isFollowingParticles) particleTargets.erase(particleTargets.begin()+i);
}

