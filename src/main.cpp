#include <Arduino.h>
#include "duckscript.h"
#include "duckparser.h"
#include "keyboard.h"
#include <BleKeyboard.h>


void setup() {
    static BleKeyboardManager bleManager;
    static BleKeyboardAdapter bleAdapter(&bleManager);
    duckparser::setKeyboard(&bleAdapter);
    duckparser::beginKeyboard();
}

void loop() {
    // Core functionality loop
}