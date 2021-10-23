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

#include <string>
#include <sstream>
#include <fstream>
#include <stdarg.h>

// Use standard string
typedef std::string DJSON_String;
typedef std::ostringstream DJSON_StringStream;

// For importing
#ifndef DJSON_API
#define DJSON_API _declspec(dllexport)
#endif

// Include structures if needed
#ifndef DJSON_EXCLUDE_DSTRUCT
  #include "DreamyStructures/DataStructures.h"
#endif

// Error codes
enum DJSON_ERROR {
  DJSON_OK = 0x00, // no error
  
  DJSON_LOAD   = 0x01, // couldn't load
  DJSON_CHAR   = 0x02, // unexpected character
  DJSON_STRING = 0x03, // unclosed string
  DJSON_CONST  = 0x04, // unknown constant
  DJSON_EMPTY  = 0x05, // no tokens
  DJSON_TOKEN  = 0x06, // invalid token
};

#include "Base/Formatting.h"
#include "Base/Compatibility.h"
