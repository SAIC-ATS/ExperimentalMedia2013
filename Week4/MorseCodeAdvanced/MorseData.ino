// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================

// If you are running low on space, you could also use PROGMEM with char arrays.

String CODE_0 = "-----";
String CODE_1 = ".----";
String CODE_2 = "..---";
String CODE_3 = "...--";
String CODE_4 = "....-";
String CODE_5 = ".....";
String CODE_6 = "-....";
String CODE_7 = "--...";
String CODE_8 = "---..";
String CODE_9 = "-----";
String CODE_A = ".-";
String CODE_B = "-...";
String CODE_C = "-.-.";
String CODE_D = "-..";
String CODE_E = ".";
String CODE_F = "..-.";
String CODE_G = "--.";
String CODE_H = "....";
String CODE_I = "..";
String CODE_J = ".---";
String CODE_K = "-.-";
String CODE_L = ".-..";
String CODE_M = "--";
String CODE_N = "-.";
String CODE_O = "---";
String CODE_P = ".--.";
String CODE_Q = "--.-";
String CODE_R = ".-.";
String CODE_S = "...";
String CODE_T = "-";
String CODE_U = "..-";
String CODE_V = "...-";
String CODE_W = ".--";
String CODE_X = "-..-";
String CODE_Y = "-.--";
String CODE_Z = "--..";

String morseCodeTable[] = 
{
  CODE_0, // index = 0, ASCII = 48
  CODE_1, // index = 1, ASCII = 49
  CODE_2, // index = 2, ASCII = 50
  CODE_3, // index = 3, ASCII = 51
  CODE_4, // index = 4, ASCII = 52
  CODE_5, // index = 5, ASCII = 53
  CODE_6, // index = 6, ASCII = 54
  CODE_7, // index = 7, ASCII = 55
  CODE_8, // index = 8, ASCII = 56
  CODE_9, // index = 9, Ascii = 57
  CODE_A, // index = 10, ASCII = 65
  CODE_B, // index = 11, ASCII = 66
  CODE_C, // index = 11, ASCII = 67
  CODE_D, // index = 11, ASCII = 68
  CODE_E, // index = 11, ASCII = 69
  CODE_F, // index = 11, ASCII = 70
  CODE_G, // index = 11, ASCII = 71
  CODE_H, // index = 11, ASCII = 72
  CODE_I, // index = 11, ASCII = 73
  CODE_J, // index = 11, ASCII = 74
  CODE_K, // index = 11, ASCII = 75
  CODE_L, // index = 11, ASCII = 76
  CODE_M, // index = 11, ASCII = 77
  CODE_N, // index = 11, ASCII = 78
  CODE_O, // index = 11, ASCII = 79
  CODE_P, // index = 11, ASCII = 80
  CODE_Q, // index = 11, ASCII = 81
  CODE_R, // index = 11, ASCII = 82
  CODE_S, // index = 11, ASCII = 83
  CODE_T, // index = 11, ASCII = 84
  CODE_U, // index = 11, ASCII = 85
  CODE_V, // index = 11, ASCII = 86
  CODE_W, // index = 11, ASCII = 87
  CODE_X, // index = 11, ASCII = 88
  CODE_Y, // index = 11, ASCII = 89
  CODE_Z  // index = 11, ASCII = 90
};

String getMorseEncoded(String text)
{
  String morseEncoded;

  // Our our Morse Code table only supports upper
  // case letters.  Thus, we convert our string to 
  // upper case.
  text.toUpperCase();

  for(int i = 0; i < text.length(); ++i)
  {
    char currentCharacter = text[i]; // should be upper case.

    // is it a number character?
    if(currentCharacter >= '0' && currentCharacter <= '9')
    {
      int index = currentCharacter - '0';
      morseEncoded += morseCodeTable[index];
    } 
    // is it an upper case letter character?
    else if(currentCharacter >= 'A' && currentCharacter <= 'Z') 
    {
      int index = currentCharacter - 'A' + 10;
      morseEncoded += morseCodeTable[index];
    }
    // otherwise, we don't have it in our table 
    // and will convert it to a space.
    else 
    {
      morseEncoded += '/'; // add a full space
    }

    morseEncoded += ' ';  // add a character pause
  }
  
  return morseEncoded;
}

