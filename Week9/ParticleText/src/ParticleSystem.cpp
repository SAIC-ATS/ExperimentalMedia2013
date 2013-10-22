#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::setup()
{
}

void ParticleSystem::update()
{
    // create a box that defines the screen (we'll use it to test if a particle
    // is still on the screen ...
    ofRectangle theScreen(-100,-100,ofGetWidth()+200,ofGetHeight()+200);



    ofVec2f mouse(ofGetMouseX(),ofGetMouseY());

    for(int i = 0; i < _particles.size(); ++i)
    {
        float distance = _particles[i]->position.distance(mouse);
        float activeDistance = 40;
        if(distance < activeDistance)
        {
            ofVec2f oppositeDirectionvelocity = (_particles[i]->position - mouse).normalized() * ofMap(distance, 0, activeDistance, .1,.3);
            _particles[i]->velocity += oppositeDirectionvelocity;

        }
    }

    // iterate through the particles backward so we can delete items as we go.
    // this is best done with an std::vector<>::iterator, but we will do that
    // later.
    for(int i = _particles.size() - 1; i >= 0; --i)
    {
        _particles[i]->update();

        if(_particles[i]->isDead || // is the particle too old?
           !theScreen.inside(_particles[i]->position)) // or is the particle not on the screen?
        {
            _particles[i]->kill(); // call the kill function

            // if yes to either, then erase the particle
            _particles.erase(_particles.begin() + i);
        }
    }

    // these are our render groups
    // we have render groups so that we can treat particles as groups when drawing
    for(int i = _groups.size() - 1; i >= 0; --i)
    {
        _groups[i]->update(); // update the group

        if(_groups[i]->members.empty())
        {
            _groups.erase(_groups.begin() + i);
        }
    }

}

void ParticleSystem::draw()
{
    ofBackground(0);

    // draw each particle according to its draw function
    for(std::size_t i = 0; i < _particles.size(); ++i)
    {
        _particles[i]->draw();
    }

    // draw the groups as groups
    for(std::size_t i = 0; i < _groups.size(); ++i)
    {
        _groups[i]->draw();
    }
}

void ParticleSystem::addParticle(std::shared_ptr<BaseParticle> particle)
{
    _particles.push_back(particle);
}

void ParticleSystem::addParticleGroup(std::shared_ptr<BaseParticleGroup> particleGroup)
{
    // it is assumed that the particles have already been added to the
    // system.  this is a "render" group.
    _groups.push_back(particleGroup);

}

std::size_t ParticleSystem::getNumParticles() const
{
    return _particles.size();
}
