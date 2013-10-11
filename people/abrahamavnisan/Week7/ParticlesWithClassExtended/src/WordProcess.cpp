//
//  WordProcess.cpp
//  ParticlesWithClass
//
//  Created by Abraham Avnisan on 10/9/13.
//
//

#include "WordProcess.h"

WordProcess::WordProcess(string _fileName)
{
    fileName = _fileName;
    
}

vector<string> WordProcess::process()
{
    buffer = ofBufferFromFile(fileName);
    words = ofSplitString(buffer, " ");
    return words;
}