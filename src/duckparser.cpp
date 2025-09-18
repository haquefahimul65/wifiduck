/*
   Copyright (c) 2019 Stefan Kremser
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/SimpleCLI
 */

#include "duckparser.h"

#include "config.h"
#include "debug.h"
#include "keyboard.h"
#include "led.h"

extern "C" {
 #include "parser.h" // parse_lines1
}

#define CASE_INSENSETIVE 0
#define CASE_SENSETIVE 1




namespace duckparser {
    // ====== PRIVATE ===== //
    bool inString  = false;
    bool inComment = false;

    int defaultDelay = 5;
    int repeatNum    = 0;

    unsigned long interpretTime  = 0;
    unsigned long sleepStartTime = 0;
    unsigned long sleepTime      = 0;

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

    void release() {
        if (keyboard) keyboard->release();
    }

    unsigned int toInt(const char* str, size_t len) {
        if (!str || (len == 0)) return 0;

        unsigned int val = 0;

        // HEX
        if ((len > 2) && (str[0] == '0') && (str[1] == 'x')) {
            for (size_t i = 2; i < len; ++i) {
                uint8_t b = str[i];

                if ((b >= '0') && (b <= '9')) b = b - '0';
                else if ((b >= 'a') && (b <= 'f')) b = b - 'a' + 10;
                else if ((b >= 'A') && (b <= 'F')) b = b - 'A' + 10;

                val = (val << 4) | (b & 0xF);
            }
        }
        // DECIMAL
        else {
            for (size_t i = 0; i < len; ++i) {
                if ((str[i] >= '0') && (str[i] <= '9')) {
                    val = val * 10 + (str[i] - '0');
                }
            }
        }

        return val;
    }

    void sleep(unsigned long time) {
        unsigned long offset = millis() - interpretTime;

        if (time > offset) {
            sleepStartTime = millis();
            sleepTime      = time - offset;

            delay(sleepTime);
        }
    }

    // ====== PUBLIC ===== //

    void parse(const char* str, size_t len) {
        interpretTime = millis();

        // Split str into a list of lines
        line_list* l = parse_lines1(str, len);

        // Go through all lines
        line_node* n = l->first;

        // Flag, no default delay after this command
        bool ignore_delay;

        while (n) {
            ignore_delay = false;

            word_list* wl  = n->words;
            word_node* cmd = wl->first;

            const char* line_str = cmd->str + cmd->len + 1;
            size_t line_str_len  = n->len - cmd->len - 1;

            char last_char = n->str[n->len];
            bool line_end  = last_char == '\r' || last_char == '\n';

            // REM (= Comment -> do nothing)
            if (inComment || compare1(cmd->str, cmd->len, "REM", CASE_SENSETIVE)) {
                inComment    = !line_end;
                ignore_delay = true;
            }

            // LOCALE (-> change keyboard layout)
            if (compare1(cmd->str, cmd->len, "LOCALE", CASE_SENSETIVE)) {
                // Only supported for USB HID
                word_node* w = cmd->next;
                if (keyboard) keyboard->setLocale(nullptr); // BLE: no-op
                ignore_delay = true;
            }

            // DELAY (-> sleep for x ms)
            else if (compare1(cmd->str, cmd->len, "DELAY", CASE_SENSETIVE)) {
                sleep(toInt(line_str, line_str_len));
                ignore_delay = true;
            }

            // DEFAULTDELAY/DEFAULT_DELAY (set default delay per command)
            else if (compare1(cmd->str, cmd->len, "DEFAULTDELAY", CASE_SENSETIVE) || compare1(cmd->str, cmd->len, "DEFAULT_DELAY", CASE_SENSETIVE)) {
                defaultDelay = toInt(line_str, line_str_len);
                ignore_delay = true;
            }

//            // REPEAT (-> repeat last command n times)
//            else if (compare1(cmd->str, cmd->len, "REPEAT", CASE_SENSETIVE) || compare1(cmd->str, cmd->len, "REPLAY", CASE_SENSETIVE)) {
//                repeatNum    = toInt(line_str, line_str_len) + 1;
//                ignore_delay = true;
//            }

            // STRING (-> type each character)
            else if (inString || compare1(cmd->str, cmd->len, "STRING", CASE_SENSETIVE)) {
                if (inString) {
                    type(n->str, n->len);
                } else {
                    type(line_str, line_str_len);
                }

                inString = !line_end;
            }

            // LED
            else if (compare1(cmd->str, cmd->len, "LED", CASE_SENSETIVE)) {
                word_node* w = cmd->next;

                int c[3];

                for (uint8_t i = 0; i<3; ++i) {
                    if (w) {
                        c[i] = toInt(w->str, w->len);
                        w    = w->next;
                    } else {
                        c[i] = 0;
                    }
                }

                led::setColor(c[0], c[1], c[2]);
            }

            // KEYCODE
            else if (compare1(cmd->str, cmd->len, "KEYCODE", CASE_SENSETIVE)) {
                word_node* w = cmd->next;
                if (w) {
                    HIDKeyboard::report k;

                    k.modifiers = (uint8_t)toInt(w->str, w->len);
                    k.reserved  = 0;
                    w           = w->next;

                    for (uint8_t i = 0; i<6; ++i) {
                        if (w) {
                            k.keys[i] = (uint8_t)toInt(w->str, w->len);
                            w         = w->next;
                        } else {
                            k.keys[i] = 0;
                        }
                    }

                    keyboard->send(&k);
                    keyboard->release();
                }
            }

            // Otherwise go through words and look for keys to press
            else {
                word_node* w = wl->first;

                while (w) {
                    press(w->str, w->len);
                    w = w->next;
                }

                if (line_end) release();
            }

            n = n->next;

            if (!inString && !inComment && !ignore_delay) sleep(defaultDelay);

            if (line_end && (repeatNum > 0)) --repeatNum;

            interpretTime = millis();
        }

        line_list_destroy1(l);
    }

    int getRepeats() {
        return repeatNum;
    }

    unsigned int getDelayTime() {
        unsigned long finishTime  = sleepStartTime + sleepTime;
        unsigned long currentTime = millis();

        if (currentTime > finishTime) {
            return 0;
        } else {
            unsigned long remainingTime = finishTime - currentTime;
            return (unsigned int)remainingTime;
        }
    }
}