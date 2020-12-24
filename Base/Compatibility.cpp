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
extern void (*_pJSON_PrintFunction)(const char *) = NULL;
extern void (*_pJSON_ErrorFunction)(const char *) = NULL;
extern JSON_String (*_pJSON_LoadConfigFile)(JSON_String) = NULL;

// Throw formatted exception
void JSON_Throw(const char *strFormat, const JSON_ERROR &eCode, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, eCode);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  throw JSON_Exception(strBuffer, eCode);
};

// Print out formatted string
void JSON_Print(const char *strFormat, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, strFormat);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  JSON_String strOut = strBuffer;
  
  // no output function
  if (_pJSON_PrintFunction == NULL) {
    printf(strOut.c_str());
    return;
  }
  
  _pJSON_PrintFunction(strOut.c_str());
};

// Print out an error
void JSON_Error(const char *strFormat, ...) {
  const int ctBufferSize = 256;
  char strBuffer[ctBufferSize+1];

  va_list arg;
  va_start(arg, strFormat);
  _vsnprintf(strBuffer, ctBufferSize, strFormat, arg);

  JSON_String strOut = strBuffer;
  
  // check the error function
  if (_pJSON_ErrorFunction == NULL) {
    // check the print function
    if (_pJSON_PrintFunction == NULL) {
      printf(strOut.c_str());
      return;
    }
    
    _pJSON_PrintFunction(strOut.c_str());
    return;
  }
  
  _pJSON_ErrorFunction(strOut.c_str());
};

// Load the config file
JSON_String JSON_LoadConfigFile(JSON_String strConfigFile) {
  // custom loading function
  if (_pJSON_LoadConfigFile != NULL) {
    return _pJSON_LoadConfigFile(strConfigFile);
  }
    
  JSON_String strConfig = "";

  std::ifstream strm;
  strm.open(strConfigFile.c_str());

  if (!strm) {
    JSON_Throw("Cannot open config file '%s'", DJSON_LOAD, strConfigFile.c_str());
  }

  // read until the end
  while (!strm.eof()) {
    JSON_String strLine = "";
    std::getline(strm, strLine);

    // save each line into the config string
    strConfig += strLine+"\n";
  }
  strm.close();
  
  // return config
  return strConfig;
};