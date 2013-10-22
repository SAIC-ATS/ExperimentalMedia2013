#include "WordParticle.h"


WordParticle::WordParticle(ofTrueTypeFont& font, const std::string& text):
    BaseTextParticle(font,text)
{
}

WordParticle::~WordParticle()
{
}

void WordParticle::kill()
{
    BaseParticle::kill(); // call the superclass

    std::vector<std::string> letters = TextUtilities::splitIntoLetters(_text);

    std::vector<std::string>::iterator iter = letters.begin();

    std::size_t offset = 0;

    while(iter != letters.end())
    {
        std::string letter = *iter;

        std::shared_ptr<BaseParticle> particle(new LetterParticle(_font,letter));

        std::string fragment(_text.begin(), _text.begin() + offset); // this will fail with some encodings

        float xOffset = _font.stringWidth(fragment);

        particle->position = position;
        particle->position.x += xOffset;
        particle->velocity = velocity + ofVec2f(ofRandom(-.4,.4),ofRandom(-.4,.4));
        particle->acceleration = acceleration;
        particle->maxAge = ofRandom(10,100);

        particle->particleSystem = particleSystem; // make a link back to the particle system

        particleSystem->addParticle(particle);

        ++iter;
        ++offset;
    }

}