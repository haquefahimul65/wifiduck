#pragma once

// Define USB HID key codes for internal use
#ifndef INTERNAL_KEY_CODES
#define INTERNAL_KEY_CODES

// Include necessary headers
#include <BleKeyboard.h>

// Map USB HID key codes to BLE key codes
#undef KEY_BACKSPACE
#undef KEY_TAB
#undef KEY_ESC
#undef KEY_INSERT
#undef KEY_DELETE
#undef KEY_HOME
#undef KEY_END
#undef KEY_F1
#undef KEY_F2
#undef KEY_F3
#undef KEY_F4
#undef KEY_F5
#undef KEY_F6
#undef KEY_F7
#undef KEY_F8
#undef KEY_F9
#undef KEY_F10
#undef KEY_F11
#undef KEY_F12
#undef KEY_F13
#undef KEY_F14
#undef KEY_F15
#undef KEY_F16
#undef KEY_F17
#undef KEY_F18
#undef KEY_F19
#undef KEY_F20
#undef KEY_F21
#undef KEY_F22
#undef KEY_F23
#undef KEY_F24
#undef KEY_MEDIA_STOP
#undef KEY_MEDIA_MUTE

// Now define our own key mappings
#define USB_KEY_BACKSPACE 0x2a
#define USB_KEY_TAB 0x2b
#define USB_KEY_ESC 0x29
#define USB_KEY_INSERT 0x49
#define USB_KEY_DELETE 0x4c
#define USB_KEY_HOME 0x4a
#define USB_KEY_END 0x4d
#define USB_KEY_F1 0x3a
#define USB_KEY_F2 0x3b
#define USB_KEY_F3 0x3c
#define USB_KEY_F4 0x3d
#define USB_KEY_F5 0x3e
#define USB_KEY_F6 0x3f
#define USB_KEY_F7 0x40
#define USB_KEY_F8 0x41
#define USB_KEY_F9 0x42
#define USB_KEY_F10 0x43
#define USB_KEY_F11 0x44
#define USB_KEY_F12 0x45
#define USB_KEY_F13 0x68
#define USB_KEY_F14 0x69
#define USB_KEY_F15 0x6a
#define USB_KEY_F16 0x6b
#define USB_KEY_F17 0x6c
#define USB_KEY_F18 0x6d
#define USB_KEY_F19 0x6e
#define USB_KEY_F20 0x6f
#define USB_KEY_F21 0x70
#define USB_KEY_F22 0x71
#define USB_KEY_F23 0x72
#define USB_KEY_F24 0x73

// Media keys
#define USB_KEY_MEDIA_STOP 0xf3
#define USB_KEY_MEDIA_MUTE 0xef

#endif // INTERNAL_KEY_CODES