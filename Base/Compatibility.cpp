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

#include "Compatibility.h"

// Custom functions
extern void (*DJSON_pPrintFunction)(const char *) = NULL;
extern void (*DJSON_pErrorFunction)(const char *) = NULL;
extern DJSON_String (*DJSON_pLoadConfigFile)(DJSON_String) = NULL;

// Throw formatted exception
void DJSON_Throw(const DJSON_ERROR &eCode, const char *strFormat, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, strFormat);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  throw DJSON_Exception(strBuffer, eCode);
};

// Print out formatted string
void DJSON_Print(const char *strFormat, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, strFormat);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  DJSON_String strOut = strBuffer;
  
  // no output function
  if (DJSON_pPrintFunction == NULL) {
    printf(strOut.c_str());
    return;
  }
  
  DJSON_pPrintFunction(strOut.c_str());
};

// Print out an error
void DJSON_Error(const char *strFormat, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, strFormat);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  DJSON_String strOut = strBuffer;
  
  // check the error function
  if (DJSON_pErrorFunction == NULL) {
    // check the print function
    if (DJSON_pPrintFunction == NULL) {
      printf(strOut.c_str());
      return;
    }
    
    DJSON_pPrintFunction(strOut.c_str());
    return;
  }
  
  DJSON_pErrorFunction(strOut.c_str());
};

// Load the config file
DJSON_String DJSON_LoadConfigFile(DJSON_String strConfigFile) {
  // custom loading function
  if (DJSON_pLoadConfigFile != NULL) {
    return DJSON_pLoadConfigFile(strConfigFile);
  }
    
  DJSON_String strConfig = "";

  std::ifstream strm;
  strm.open(strConfigFile.c_str());

  if (!strm) {
    DJSON_Throw(DJSON_LOAD, "Cannot open config file '%s'", strConfigFile.c_str());
  }

  // read until the end
  while (!strm.eof()) {
    DJSON_String strLine = "";
    std::getline(strm, strLine);

    // save each line into the config string
    strConfig += strLine+"\n";
  }
  strm.close();
  
  // return config
  return strConfig;
};