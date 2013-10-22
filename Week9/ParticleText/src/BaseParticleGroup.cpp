#include "BaseParticleGroup.h"


BaseParticleGroup::BaseParticleGroup()
{
    color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

BaseParticleGroup::~BaseParticleGroup()
{
}

void BaseParticleGroup::update()
{
    // when a particle is dead, it is removed from the group
    // it is likely that it has already been removed from the
    // particle system as well.  when it is removed from both places,
    // the shared pointer will call it's destructor and free the memory.
    for(int i = members.size() - 1; i >= 0; --i)
    {
        if(members[i]->isDead)
        {
            members.erase(members.begin() + i);
        }
    }
}

void BaseParticleGroup::draw()
{
    // this is a "group" drawing feature
    ofPushStyle();
    ofNoFill();
    ofSetColor(color);
    ofBeginShape();
    for(std::size_t i = 0; i < members.size(); ++i)
    {
        ofVertex(members[i]->position.x,members[i]->position.y);
    }
    ofEndShape(true); // close it

    ofPopStyle();

}
