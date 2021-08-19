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

#include "../Values/ConfigValue.h"
#include "../Values/ConfigBlock.h"
#include "ParserToken.h"

// Config parser
DJSON_API DJSON_ERROR ParseConfigTokens(const char *strConfigFile);

// Parse JSON block
DJSON_API DJSON_ERROR ParseConfig(const char *strConfigFile, DJSON_Block &mapConfig);
// Parse JSON array
DJSON_API DJSON_ERROR ParseConfig(const char *strConfigFile, DJSON_Array &aConfig);

// Array parser
DJSON_API int ParseArray(DJSON_Array &aArray);
// Block parser
DJSON_API int ParseBlock(DJSON_Block &mapConfig);
// Key parser
DJSON_API int ParseKey(DJSON_Block &mapConfig);
// Value parser
DJSON_API int ParseValue(CConfigValue &cvValue);

// Add one token to the list
DJSON_API void AddToken(const EParserToken &eType, const int &iLine);
DJSON_API void AddToken(const EParserToken &eType, const int &iLine, const __int64 &iValue);
DJSON_API void AddToken(const EParserToken &eType, const int &iLine, const double &fValue);
DJSON_API void AddToken(const EParserToken &eType, const int &iLine, const DJSON_String &strValue);
