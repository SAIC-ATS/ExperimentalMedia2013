#pragma once


#include <string>
#include <vector>


class TextUtilities
{
public:
    static std::string loadFile(const std::string& textFile);
    static std::string stripPunctuation(const std::string& buffer);

    static std::vector<std::string> splitIntoWords(const std::string& buffer);
    static std::vector<std::string> splitIntoLetters(const std::string& buffer);


};