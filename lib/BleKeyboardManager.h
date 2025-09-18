#pragma once

#include <BleKeyboard.h>

class BleKeyboardManager {
public:
    BleKeyboardManager(const char* name = "WiFiDuckBLE");
    void begin();
    void end();
    bool isConnected();
    void setName(const char* name);
    void type(const char* str);
    void pressKey(uint8_t key);
    void releaseAll();
    void pressModifier(uint8_t mod);
    void sendKeyCombo(uint8_t mod, uint8_t key);
private:
    BleKeyboard* bleKeyboard;
    String deviceName;
};
