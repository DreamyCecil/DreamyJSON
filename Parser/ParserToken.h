/* Copyright (c) 2020-2021 Dreamy Cecil

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#pragma once

#include "../ConfigBase.h"

// Parser Token Type
enum EParserToken {
  EPT_UNKNOWN = -1,
  
  EPT_OPEN_C,  // opening curly bracket
  EPT_CLOSE_C, // closing curly bracket
  EPT_OPEN_S,  // opening square bracket
  EPT_CLOSE_S, // closing square bracket
  
  EPT_COLON, // colon
  EPT_COMMA, // comma
  
  EPT_NULL,   // null value
  EPT_INDEX,  // index value
  EPT_FLOAT,  // float value
  EPT_STRING, // string value
  
  EPT_END, // end of file
};

// Parser Token Template
class DJSON_API CParserToken {
  public:
    int pt_eTokenType;
    int pt_iLine; // token place
    
    union {
      float pt_fValue; // float value
      char pt_strValue[256]; // string value
    };
    
    // Constructors
    CParserToken(void) :
      pt_eTokenType(EPT_UNKNOWN), pt_iLine(0), pt_fValue(0.0f) {};
    
    CParserToken(const int &iType, const int &iLine) :
      pt_eTokenType(iType), pt_iLine(iLine), pt_fValue(0.0f) {};
      
    CParserToken(const int &iType, const int &iLine, const float &f) :
      pt_eTokenType(iType), pt_iLine(iLine), pt_fValue(f) {};
      
    CParserToken(const int &iType, const int &iLine, const DJSON_String &str) :
      pt_eTokenType(iType), pt_iLine(iLine)
    {
      strcpy(pt_strValue, str.c_str());
    };
};
