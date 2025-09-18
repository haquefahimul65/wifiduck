/*
   Copyright (c) 2019 Stefan Kremser
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/SimpleCLI
 */

#include "duckparser.h"

#include "config.h"
#include "debug.h"
#include "keyboard.h"

namespace duckparser {
    IKeyboard* keyboard = nullptr;

    void setKeyboard(IKeyboard* kbd) {
        keyboard = kbd;
    }

    void beginKeyboard() {
        if (keyboard) keyboard->begin();
    }

    void type(const char* str, size_t len) {
        if (keyboard) keyboard->type(str, len);
    }

    void press(const char* str, size_t len) {
        if (keyboard) keyboard->press(str, len);
    }
}