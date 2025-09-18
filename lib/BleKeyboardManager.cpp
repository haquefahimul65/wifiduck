#include "BleKeyboardManager.h"

BleKeyboardManager::BleKeyboardManager(const char* name) : deviceName(name) {
    bleKeyboard = new BleKeyboard(deviceName.c_str());
}

void BleKeyboardManager::begin() {
    bleKeyboard->begin();
}

void BleKeyboardManager::end() {
    bleKeyboard->end();
}

bool BleKeyboardManager::isConnected() {
    return bleKeyboard->isConnected();
}

void BleKeyboardManager::setName(const char* name) {
    deviceName = name;
    bleKeyboard->end();
    delete bleKeyboard;
    bleKeyboard = new BleKeyboard(deviceName.c_str());
    bleKeyboard->begin();
}

void BleKeyboardManager::type(const char* str) {
    bleKeyboard->print(str);
}

void BleKeyboardManager::pressKey(uint8_t key) {
    bleKeyboard->press(key);
    delay(100);
    bleKeyboard->releaseAll();
}

void BleKeyboardManager::releaseAll() {
    bleKeyboard->releaseAll();
}

void BleKeyboardManager::pressModifier(uint8_t mod) {
    bleKeyboard->press(mod);
    delay(100);
    bleKeyboard->releaseAll();
}

void BleKeyboardManager::sendKeyCombo(uint8_t mod, uint8_t key) {
    bleKeyboard->press(mod);
    bleKeyboard->press(key);
    delay(100);
    bleKeyboard->releaseAll();
}
