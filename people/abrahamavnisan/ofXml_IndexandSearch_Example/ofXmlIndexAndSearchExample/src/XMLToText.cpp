#include "XMLToText.h"

//--------------------------------------------------------------
XMLToText::XMLToText()
{
}
//--------------------------------------------------------------
XMLToText::~XMLToText()
{
}
//--------------------------------------------------------------
string XMLToText::convert(string stringToConvert)
{
    //    There are five predefined entity references in XML: "<", ">", "'", " " ", "&".
    //    The ofXml.addValue method automatically converts these for us.  This little
    //    method is a handy tool to convert them back to regular text that uses some
    //    simple Regular Expressions.
    
    string convertedString = stringToConvert;
    
    RegularExpression RegEx_lessThan("&lt;");
    RegularExpression RegEx_greaterThan("&gt;");
    RegularExpression RegEx_apostrophe("&apos;");
    RegularExpression RegEx_quotation("&quot;");
    RegularExpression RegEx_ampersand("&amp;");
    
    RegEx_lessThan.subst(convertedString, "<", RegularExpression::RE_GLOBAL);
    RegEx_greaterThan.subst(convertedString, ">", RegularExpression::RE_GLOBAL);
    RegEx_apostrophe.subst(convertedString, "'", RegularExpression::RE_GLOBAL);
    RegEx_quotation.subst(convertedString, "\"", RegularExpression::RE_GLOBAL);
    RegEx_ampersand.subst(convertedString, "&", RegularExpression::RE_GLOBAL);
    
    return convertedString;
}