/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include <BleKeyboard.h>

class BLEKeyboardAdapter {
private:
    BleKeyboard bleKeyboard;

public:
    void begin() {
        bleKeyboard.begin();
    }

    void type(const char* str) {
        bleKeyboard.print(str);
    }
};