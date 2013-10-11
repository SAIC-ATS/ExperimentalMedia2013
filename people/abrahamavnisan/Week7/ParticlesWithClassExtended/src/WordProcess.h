//
//  WordProcess.h
//  ParticlesWithClass
//
//  Created by Abraham Avnisan on 10/9/13.
//
//

#pragma once
#include "ofMain.h"

// this seems like overkill for a class (though I may expand it later)
// should I have written this as a method instead?
           
class WordProcess
{
public:
    WordProcess(string _fileName);
    
    vector<string> process();
    
    string fileName;
    ofBuffer buffer;
    vector<string> words;
    
};
