#include "LetterParticle.h"


LetterParticle::LetterParticle(ofTrueTypeFont& font, const std::string& text):
    BaseTextParticle(font,text)
{
}

LetterParticle::~LetterParticle()
{
}

void LetterParticle::draw()
{
    ofPushMatrix();
    ofTranslate(position);

    ofPushStyle();

    ofNoFill();

    ofColor startColor = ofColor::yellow;
    ofColor endColor = ofColor::white;

    ofColor myColor = startColor;

    myColor.lerp(endColor, getLife());

    ofSetColor(myColor);

    font.drawStringAsShapes(text,0,0);

    ofPopStyle();

    ofPopMatrix();
}

void LetterParticle::kill()
{
    BaseParticle::kill(); // call the super /parent class!

    std::vector<ofTTFCharacter> paths = font.getStringAsPoints(text);

    std::vector<ofTTFCharacter>::iterator pathsIter = paths.begin();

    while(pathsIter != paths.end())
    {
        std:vector<ofPolyline> polylines = (*pathsIter).getOutline();

        std::vector<ofPolyline>::const_iterator polyIter = polylines.begin();

        while(polyIter != polylines.end())
        {
            if((*polyIter).size() > 0)
            {
                ofPolyline resampled = (*polyIter).getResampledBySpacing(2); // this number tells us how many particles

                if(resampled.size() > 0)
                {
                    const ofPolyline poly = resampled.getVertices();

                    ofVec2f centroid = poly.getCentroid2D();  // find the middle

                    // create a particle group
                    std::shared_ptr<BaseParticleGroup> particleGroup(new BaseParticleGroup());

                    // add particles to the particle system AND to the particle group
                    for(int i = 0; i < poly.size(); ++i)
                    {
                        std::shared_ptr<ParticleGroupMember> particle(new ParticleGroupMember());

                        // this is how we get the particle to move away from the center
                        // of the group (as calculated by the centroid)
                        ofVec2f newVelocity = (poly[i] - centroid).normalized() * ofRandom(.5,2);

                        particle->position = position + poly[i];
                        particle->velocity = velocity + newVelocity;
                        particle->acceleration = acceleration;
                        particle->maxAge = ofRandom(50,100);

                        particle->particleSystem = particleSystem; // make a link back to the particle system
                        
                        particleSystem->addParticle(particle);

                        particleGroup->members.push_back(particle);
                    }

                    // add the particle group to the particle system
                    particleSystem->addParticleGroup(particleGroup);
                }
            }

            ++polyIter;
        }

        ++pathsIter;
    }
}

