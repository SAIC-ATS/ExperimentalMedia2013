#include "TextUtilities.h"
#include "Poco/RegularExpression.h"
#include "Poco/StringTokenizer.h"
#include "Poco/TextIterator.h"
#include "Poco/TextConverter.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/Unicode.h"
#include "ofUtils.h"
#include "ofFileUtils.h"


// a simple function for loading text into a string
std::string TextUtilities::loadFile(const std::string& textFile)
{
    ofBuffer buffer = ofBufferFromFile(textFile);
    return ofBufferFromFile(textFile).getText();
}

// a function that removes commas and periods (could be more)
std::string TextUtilities::stripPunctuation(const std::string& buffer)
{
    static Poco::RegularExpression regex("[,.]");

    std::string output = buffer;

    regex.subst(output,"",Poco::RegularExpression::RE_GLOBAL); // replace with nothing

    return output;
}

// a function that splits a long string into words (by looking for spaces)
std::vector<std::string> TextUtilities::splitIntoWords(const std::string& buffer)
{
    std::vector<std::string> output;

    Poco::StringTokenizer tokenizer(buffer, " ");

    Poco::StringTokenizer::Iterator iter = tokenizer.begin();

    while (iter != tokenizer.end())
    {
        output.push_back(*iter);
        ++iter;
    }

    return output;
}

// a function that splits a word string into a series of letters
// NOTE: this does not currently deal with unicode (multi-byte) text.
// Casting to char (char) below, effectively destroys multi-byte text.
// There are ways around this, but it's tricky.  This will be solved in the
// next version of openFrameworks.
std::vector<std::string> TextUtilities::splitIntoLetters(const std::string& buffer)
{
    std::vector<std::string> output;

    // google Poco::UTF8Encoding and take a look at
    // http:://pocoproject.org/slides/040-StringsAndFormatting.pdf
    Poco::UTF8Encoding utf8Encoding;
    std::string utf8String(buffer);
    Poco::TextIterator iter(utf8String, utf8Encoding);
    Poco::TextIterator end(utf8String);
    int n = 0;
    while (iter != end)
    {
        int unicodeCharacter = *iter;

        char asciiCharacter = (char) unicodeCharacter; // BAAAAD.  Very bad.  Very very bad.

        std::string outChar(1,asciiCharacter);

        output.push_back(outChar);

        ++n; // number of UTF8 characters
        ++iter; // iterator
    }

    return output;
}
