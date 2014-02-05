#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {}

ParticleEmitter::ParticleEmitter(int _maxNumberParticles, float _emissionRate, float _prewarmTime) {
    maxNumberParticles = _maxNumberParticles;
    emissionRate = _emissionRate;
    numberParticleTargets = 0.2 * maxNumberParticles;
    emitParticles(_prewarmTime);
    isFollowingMouse = false;
    isFollowingParticles = false;
}

void ParticleEmitter::emitParticles(float dt) {
    int maxToEmit = emissionRate * dt;
    int particlesGenerated = 0;
    while(particles.size()<maxNumberParticles && particlesGenerated<maxToEmit) {
        if (isFollowingParticles) particleTargets.push_back(ofRandom(numberParticleTargets));
        particles.push_back(createParticle());
        particlesGenerated++;
    }
}

void ParticleEmitter::update(float dt) {
    updateParticles(dt);
    killParticles();
    emitParticles(dt);
}

void ParticleEmitter::updateParticles(float dt) {
    for(int i=0; i<particles.size(); ++i) {
        bool targetPresent = isFollowingMouse || isFollowingParticles;
        ofVec3f target;
        if (isFollowingMouse) target = ofVec3f(ofGetMouseX()-ofGetWidth()/2, ofGetMouseY()-ofGetHeight()/2);
        else if (isFollowingParticles) target = particles[particleTargets[i]]->center;
        particles[i]->update(dt, targetPresent, target);
    }
}

void ParticleEmitter::killParticles() {
    ofRectangle theScreen(-ofGetWidth()/2,-ofGetHeight()/2,ofGetWidth()/2,ofGetHeight()/2);
    for(int i=particles.size()-1; i>=0; --i)
    {
        bool isDead = particles[i]->isDead;
        bool isOffScreen = false;//!theScreen.inside(particles[i]->center);
        bool isNotInViewableDepth = !(particles[i]->center.z < 400 && particles[i]->center.z > -400);
        if(isDead || isOffScreen || isNotInViewableDepth) eraseParticle(i);
    }
}

ofPtr<BaseParticle> ParticleEmitter::createParticle() {
    cout << "Part Emit" << endl;
    ofPtr<BaseParticle> ptr(new BaseParticle());
    ptr->center = ofVec3f(ofRandom(-50,50), ofRandom(-50,50), ofRandom(-50,50));
    ptr->velocity = ofRandom(200,400);
    return ptr;
}

void ParticleEmitter::eraseParticle(int i) {
    particles.erase(particles.begin()+i);
    if (isFollowingParticles) particleTargets.erase(particleTargets.begin()+i);
}

void ParticleEmitter::followParticles() {
    isFollowingParticles = true;
    stopFollowingMouse();
    for(int i=0; i<particles.size(); ++i) {
        int otherIndex = 0;
        while (otherIndex == i) otherIndex = ofRandom(numberParticleTargets);
        particleTargets.push_back(otherIndex);
    }
}

void ParticleEmitter::stopFollowingParticles() {
    isFollowingParticles = false;
    particleTargets.clear();
}

void ParticleEmitter::followMouse() {
    isFollowingMouse = true;
    stopFollowingParticles();
}

void ParticleEmitter::stopFollowingMouse() {
    isFollowingMouse = false;
}

void ParticleEmitter::draw() {
    for(int i=0; i<particles.size(); ++i) particles[i]->draw();
}

ParticleEmitter::~ParticleEmitter(){}
