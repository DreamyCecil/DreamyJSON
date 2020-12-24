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

#include "Formatting.h"

// Resize raw string
char *JSON_ResizeString(void *pMem, int ctSize) {
  char *pNew = new char[ctSize];

  memcpy(pNew, pMem, ctSize);
  delete[] pMem;

  return pNew;
};

// Format a config string
JSON_String JSON_ConfigPrintF(const char *strFormat, ...) {
  va_list arg;
  va_start(arg, strFormat);

  return JSON_VPrintF(strFormat, arg);
};

// Format some string using a list of arguments
JSON_String JSON_VPrintF(const char *strFormat, va_list arg) {
  static int _ctBufferSize = 0;
  static char *_pchBuffer = NULL;

  // allocate if buffer wasn't allocated yet
  if (_ctBufferSize == 0) {
    _ctBufferSize = 256;
    _pchBuffer = new char[_ctBufferSize];
  }

  // repeat
  int iLen;
  while (true) {
    // print to the buffer
    iLen = _vsnprintf(_pchBuffer, _ctBufferSize, strFormat, arg);

    // stop if printed ok
    if (iLen != -1) {
      break;
    }

    // increase the buffer size
    _ctBufferSize += 256;
    _pchBuffer = JSON_ResizeString(_pchBuffer, _ctBufferSize);
  }

  JSON_String strPrint = _pchBuffer;
  return strPrint;
};

// Config text tabs
JSON_String JSON_ConfigTabs(int iLevel) {
  JSON_String str = "";
  
  if (iLevel > 0) {
    for (int i = 0; i < iLevel; i++) {
      str = JSON_ConfigPrintF("%s  ", str.c_str());
    }
  }
  
  return str;
};