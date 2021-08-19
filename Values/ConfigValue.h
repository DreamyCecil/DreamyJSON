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

#include "ConfigElement.h"

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
    
    // Values
    union {
      __int64 cv_iValue; // index value
      double cv_dValue; // float value
      char cv_strValue[256]; // string value
    };

    // Containers
    DJSON_Array cv_aArray; // array of values
    DJSON_Block cv_mapBlock; // block of values
    
    // Constructors
    CConfigValue(void);
    CConfigValue(const __int64 &iValue);
    CConfigValue(const double &dValue);
    CConfigValue(const DJSON_String &strValue);
    CConfigValue(const DJSON_Array &aArray);
    CConfigValue(const DJSON_Block &mapBlock);
    
    // Set new value
    void SetNull(void);
    void SetValue(const __int64 &iValue);
    void SetValue(const double &dValue);
    void SetValue(const DJSON_String &strValue);
    void SetValue(const DJSON_Array &aArray);
    void SetValue(const DJSON_Block &mapBlock);
    
    // Destructor
    ~CConfigValue(void);
    void Clear(void);

    // Get number value
    double GetNumber(void);
    
    // Print the value
    void PrintValue(DJSON_String &strValue, const int &iLevel, bool bHasKey = false);
};
