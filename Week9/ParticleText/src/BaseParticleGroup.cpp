#include "BaseParticleGroup.h"


BaseParticleGroup::BaseParticleGroup()
{
}

BaseParticleGroup::~BaseParticleGroup()
{
}

void BaseParticleGroup::update()
{
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
    ofPushStyle();
    ofNoFill();
    ofSetColor(255,255,0,127);
    ofBeginShape();
    for(std::size_t i = 0; i < members.size(); ++i)
    {
        ofVertex(members[i]->position.x,members[i]->position.y);
    }
    ofEndShape(true); // close it

    ofPopStyle();

}
