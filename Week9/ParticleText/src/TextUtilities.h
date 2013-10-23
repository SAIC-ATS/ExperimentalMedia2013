#pragma once


#include <string>
#include <vector>


class TextUtilities
{
public:
    // This method only contains "static" functions.  We don't instantiate this
    // class.  We call the methods from anywhere in our program with a syntax
    // like:
    //
    // std::string myString = TextUtilities::loadFile("LoremIpsum.txt");

    static std::string loadFile(const std::string& textFile);
    static std::string stripPunctuation(const std::string& buffer);

    static std::vector<std::string> splitIntoWords(const std::string& buffer);
    static std::vector<std::string> splitIntoLetters(const std::string& buffer);


};