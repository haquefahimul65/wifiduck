; PlatformIO Project Configuration File
; Build options, upload protocols, and more.
; https://docs.platformio.org/page/projectconf.html

[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200

; Enable SPIFFS upload
extra_scripts = pre:spiffs_upload.py

lib_deps =
    spacehuhn/SimpleCLI@^1.1.4
    me-no-dev/AsyncTCP@^1.1.1
    t-vk/ESP32 BLE Keyboard@^0.3.2
    esp32async/ESPAsyncWebServer@^3.8.1