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

// JSON exception
struct DJSON_Exception {
  char *strError;
  DJSON_ERROR eCode;

  // Constructor
  DJSON_Exception(char *str, DJSON_ERROR e) : strError(str), eCode(e) {};
};

// Throw formatted exception
DJSON_API void DJSON_Throw(const DJSON_ERROR &eCode, const char *strFormat, ...);
// Print out formatted string
DJSON_API void DJSON_Print(const char *strFormat, ...);
// Print out an error
DJSON_API void DJSON_Error(const char *strFormat, ...);

// Load the config file
DJSON_API DJSON_String DJSON_LoadConfigFile(DJSON_String strConfigFile);
