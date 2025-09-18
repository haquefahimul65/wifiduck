# Cleanup Plan for Simplification

## 1. Remove USB-related Code
- Delete the `custom_usb_descriptors` folder.
- Remove `usb_hid_keys.h` from `src/locale`.
- Remove all references to `USBHID`, `USBHIDDevice`, and `ESPUSB`.
- Remove USB-related code in `keyboard.h` and `keyboard.cpp`.
- Update `platformio.ini` to remove USB-related build flags.

## 2. Simplify Web UI
- Remove USB-related options from `settings.html` and `settings.js`.
- Retain BLE-related functionality.

## 3. Clean Up Unused Files
- Delete unused test scripts and redundant files.
- Ensure only BLE and Web UI functionality remains.

## Next Steps
- Implement the above changes step by step.
- Test the BLE functionality and Web UI to ensure everything works as expected.