#include <Arduino.h>

#include "config.h"
#include "debug.h"
#include "duckscript.h"
#include "duckparser.h"
#include "webserver.h"
#include "spiffs.h"
#include "settings.h"
#include "cli.h"
#include "USB.h"

#include <BleKeyboard.h>
#include "BleKeyboardManager.h"


void setup() {
    debug_init();
    bool useBLE = settings::get("keyboard_mode") == "ble";
    if (useBLE) {
        static BleKeyboardManager bleManager;
        static BleKeyboardAdapter bleAdapter(&bleManager);
        duckparser::setKeyboard(&bleAdapter);
        duckparser::beginKeyboard();
    } else {
        static HIDKeyboard hidKeyboard;
        duckparser::setKeyboard(&hidKeyboard);
        duckparser::beginKeyboard();
        USB.begin();
    }
    delay(200);
    spiffs::begin();
    settings::begin();
    cli::begin();
    webserver::begin();

    duckscript::run(settings::getAutorun());
}

void loop() {
    webserver::update();
    debug_update();
}