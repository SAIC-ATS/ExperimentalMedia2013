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
    ofSetColor(255);

    _font.drawStringAsShapes(_text,0,0);

    ofPopStyle();

    ofPopMatrix();
}

void LetterParticle::kill()
{
    BaseParticle::kill();

    std::vector<ofTTFCharacter> paths = _font.getStringAsPoints(_text);

    std::vector<ofTTFCharacter>::iterator pathsIter = paths.begin();

    while(pathsIter != paths.end())
    {
        std:vector<ofPolyline> polylines = (*pathsIter).getOutline();

        std::vector<ofPolyline>::const_iterator polyIter = polylines.begin();

        while(polyIter != polylines.end())
        {

            int groupMaxAge = 500;

            if((*polyIter).size() > 0)
            {
                ofPolyline resampled = (*polyIter).getResampledBySpacing(2);

                if(resampled.size() > 0)
                {
                    const ofPolyline poly = resampled.getVertices();

                    ofVec2f centroid = poly.getCentroid2D();  // find the middle


                    std::shared_ptr<BaseParticleGroup> particleGroup(new BaseParticleGroup());

                    for(int i = 0; i < poly.size(); ++i)
                    {
                        std::shared_ptr<ParticleGroupMember> particle(new ParticleGroupMember());

                        ofVec2f newVelocity = (poly[i] - centroid).normalized() * ofRandom(.5,1);

                        particle->position = position + poly[i];
                        particle->velocity = velocity + newVelocity;
                        particle->acceleration = acceleration;
                        particle->maxAge = groupMaxAge;

                        particle->particleSystem = particleSystem; // make a link back to the particle system
                        
                        particleSystem->addParticle(particle);

                        particleGroup->members.push_back(particle);
                    }

                    particleSystem->addParticleGroup(particleGroup);
                }
            }

            ++polyIter;
        }

        ++pathsIter;
    }
}

