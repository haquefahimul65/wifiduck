/*
   Copyright (c) 2019 Stefan Kremser
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/SimpleCLI
 */

#pragma once

#include <stddef.h> // size_t

class IKeyboard {
public:
  virtual void begin() = 0;
  virtual void type(const char* str, size_t len) = 0;
  virtual void press(const char* str, size_t len) = 0;
  virtual void release() = 0;
  virtual void setLocale(void* locale) = 0;
};

namespace duckparser {
  void setKeyboard(IKeyboard* kbd);
  void parse(const char* str, size_t len);
  int getRepeats();
  unsigned int getDelayTime();
  void beginKeyboard();
};