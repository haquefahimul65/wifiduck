/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include "Print.h"
#include "esp_event.h"
#include "duckparser.h"
#include "BleKeyboardManager.h"

// Define keyboard modes
enum KeyboardMode {
    MODE_USB_HID,
    MODE_BLE
};

ESP_EVENT_DECLARE_BASE(ARDUINO_USB_HID_KEYBOARD_EVENTS);

typedef enum {
    ARDUINO_USB_HID_KEYBOARD_ANY_EVENT = ESP_EVENT_ANY_ID,
    ARDUINO_USB_HID_KEYBOARD_LED_EVENT = 0,
    ARDUINO_USB_HID_KEYBOARD_MAX_EVENT,
} arduino_usb_hid_keyboard_event_t;

typedef union {
    struct {
            uint8_t numlock:1;
            uint8_t capslock:1;
            uint8_t scrolllock:1;
            uint8_t compose:1;
            uint8_t kana:1;
            uint8_t reserved:3;
    };
    uint8_t leds;
} arduino_usb_hid_keyboard_event_data_t;



class HIDKeyboard : public IKeyboard {
private:
  static hid_locale_t* locale;

public:
    void begin() override {
        hid.begin();
    }

    void type(const char* str, size_t len) override {
        if (str && len > 0) {
            for (size_t i = 0; i < len; i++) {
                press(&str[i], 1);
                release();
            }
        }
    }

    void press(const char* str, size_t len) override {
        if (str && len > 0 && locale) {
            uint8_t report[8] = { 0 };
            report[0] = locale->modifiers[str[0]];
            report[2] = locale->keys[str[0]];
            send(report);
        }
    }

    void release() override {
        uint8_t report[8] = { 0 };
        send(report);
    }

    void setLocale(void* l) override {
        locale = (hid_locale_t*)l;
    }

    void send(void* report) override {
        if (report) {
            hid.write(report, sizeof(uint8_t) * 8);
        }
    }

  typedef struct
  {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
  } report;

  HIDKeyboard(void);
  void begin();

  void setLocale(hid_locale_t* locale);

  void send(report* k);
  void release();

  void pressKey(uint8_t key, uint8_t modifiers = KEY_NONE);
  void pressModifier(uint8_t key);

  uint8_t press(const char* strPtr);

  uint8_t write(const char* c);
  void write(const char* str, size_t len);

  report makeReport(uint8_t modifiers = 0, uint8_t key1 = 0, uint8_t key2 = 0, uint8_t key3 = 0, uint8_t key4 = 0, uint8_t key5 = 0, uint8_t key6 = 0);

  static report prev_report;

  void onEvent(esp_event_handler_t callback);
  void onEvent(arduino_usb_hid_keyboard_event_t event, esp_event_handler_t callback);

  uint16_t _onGetDescriptor(uint8_t* buffer);
  void _onOutput(uint8_t report_id, const uint8_t* buffer, uint16_t len);
};