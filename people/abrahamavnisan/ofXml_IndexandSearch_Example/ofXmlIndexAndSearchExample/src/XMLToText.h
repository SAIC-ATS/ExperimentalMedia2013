#pragma once 
#include "ofMain.h"

#include "Poco/RegularExpression.h"
#include "Poco/String.h"
using Poco::RegularExpression;

class XMLToText
{
    public:

    // CTOR AND DTOR (AKA CONSTRUCTOR AND DESTRUCTOR)

        XMLToText();
        ~XMLToText();

    // OUR CONVERSION METHOD
    
        static string convert(string stringToConvert);
};