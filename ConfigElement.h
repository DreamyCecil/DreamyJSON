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

#include "ConfigBase.h"

// JSON garbage collector (for debugging purposes)
//#define DREAMY_JSON_GC
  
// Config Element Base
class DJSON_API CConfigElement {
  protected:
    int ce_iGCIndex;
    
    enum EConfigElementType {
      CET_VALUE = 0,
      CET_BLOCK = 1,
      CET_ARRAY = 2,
    } ce_eElementType;
    
    CConfigElement(const EConfigElementType eType) : ce_iGCIndex(0), ce_eElementType(eType) {};
};

#ifdef DREAMY_JSON_GC
  extern CDList<CConfigElement *> _aConfigGarbage;
#endif

// Predefine the elements
class CConfigArray;
class CConfigBlock;
class CConfigValue;
