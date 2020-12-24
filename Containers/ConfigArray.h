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
#include "../Values/ConfigValue.h"

class DJSON_API CConfigArray : CConfigElement {
  public:
    CDList<CConfigValue *> ca_acvValues; // list of values
    
    // Constructor & Destructor
    CConfigArray(void);
    ~CConfigArray(void);
    
    // Obtain array element
    const inline CConfigValue &operator[](int iValue) const { return *ca_acvValues[iValue]; };
    inline CConfigValue &operator[](int iValue) { return *ca_acvValues[iValue]; };
    
    // Delete element from the array
    inline void Delete(int iValue) { ca_acvValues.Delete(iValue); };

    inline int Count(void) { return ca_acvValues.Count(); };
    void Clear(void); // clear the array
    
    // Add values
    int AddNull(void);
    int AddValue(const int &iValue);
    int AddValue(const float &fValue);
    int AddValue(const JSON_String &strValue);
    int AddValue(CConfigArray *caArray);
    int AddValue(CConfigBlock *cbBlock);
    // Add existing value
    int AddValue(CConfigValue *cvValue);
    
    // Print the array
    void Print(JSON_String &strValue, const int &iLevel);
};
