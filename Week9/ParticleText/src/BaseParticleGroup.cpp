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

//    ofMesh mesh;
//    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    ofMesh trails;
    trails.setMode(OF_PRIMITIVE_LINES);
    trails.enableColors();

    for(std::size_t i = 0; i < members.size(); ++i)
    {

//        ofVec2f position = members[i]->position;
//
//        ofVec2f up = position + ofVec2f(0,-4);
//        ofVec2f right = position + ofVec2f(4,4);
//        ofVec2f left = position + ofVec2f(-4,4);
//
//
//        mesh.addVertex(up);
//        mesh.addVertex(right);
//        mesh.addVertex(left);
//
//
        ofFloatColor myColor = ofFloatColor::white;

        ofFloatColor endColor(color);
        endColor.a = 0;
        myColor.lerp(color, members[i]->getLife());

//        mesh.addColor(myColor);
//        mesh.addColor(myColor);
//        mesh.addColor(myColor);


        trails.addVertex(members[i]->position);
        trails.addColor(myColor);

        ofVec2f diff = members[i]->position - members[i]->velocity;

        trails.addVertex(diff);

        ofFloatColor c = myColor;
        c.a = 0;

        trails.addColor(c);
    }

//    mesh.draw();
    trails.draw();

    ofPopStyle();

}
