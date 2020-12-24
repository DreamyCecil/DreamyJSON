/* Copyright (c) 2020 Dreamy Cecil

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

#include "../ConfigElement.h"
#include "../Containers/ConfigArray.h"
#include "../Containers/ConfigBlock.h"

// Value Types
enum EConfigValueType {
  CVT_NULL   = 0, // null value (invalid)
  CVT_INDEX  = 1, // index value
  CVT_FLOAT  = 2, // float value
  CVT_STRING = 3, // string value
  CVT_ARRAY  = 4, // array of values
  CVT_BLOCK  = 5, // block of values
};

// Value type names
static const char *_astrConfigValueTypes[] = {
  "NULL", "INDEX", "FLOAT", "STRING", "ARRAY", "BLOCK",
};

class DJSON_API CConfigValue : CConfigElement {
  public:
    EConfigValueType cv_eType;
    
    union {
      int cv_iValue; // index value
      float cv_fValue; // float value
      char cv_strValue[256]; // string value
      CConfigArray *cv_caValue; // array of values
      CConfigBlock *cv_cbValue; // block of values
    };
    
    // Constructors
    CConfigValue(void);
    CConfigValue(const int &iValue);
    CConfigValue(const float &fValue);
    CConfigValue(const JSON_String &strValue);
    CConfigValue(CConfigArray *caValue);
    CConfigValue(CConfigBlock *cbValue);
    
    // Set new value
    void SetNull(void);
    void SetValue(const int &iValue);
    void SetValue(const float &fValue);
    void SetValue(const JSON_String &strValue);
    void SetValue(CConfigArray *caValue);
    void SetValue(CConfigBlock *cbValue);
    
    // Destructor
    ~CConfigValue(void);
    void Clear(void);
    
    // Print the value
    void PrintValue(JSON_String &strValue, const int &iLevel, bool bHasKey);
};
