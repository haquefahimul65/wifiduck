# WiFi Duck

## Overview
WiFi Duck is a project that emulates a USB keyboard over WiFi or Bluetooth. It allows users to execute pre-defined scripts (duck scripts) for automation or penetration testing purposes. The project includes a WebUI for managing scripts and device settings.

## Features
- BLE Keyboard emulation
- WiFi Access Point for WebUI
- Web-based interface for managing scripts
- SPIFFS for file storage

## Setup Instructions

### Prerequisites
- ESP32-S3 DevKitC-1 board
- PlatformIO installed on your system
- USB cable for flashing the firmware

### Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/haquefahimul65/wifiduck.git
   cd wifiduck
   ```

2. **Install Dependencies**
   Ensure all required libraries are installed:
   ```bash
   pio lib install
   ```

3. **Build the Firmware**
   Compile the firmware for the ESP32-S3 board:
   ```bash
   pio run --environment esp32-s3-devkitc-1
   ```

4. **Upload the Firmware**
   Flash the firmware to the ESP32-S3 board:
   ```bash
   pio run --target upload --environment esp32-s3-devkitc-1
   ```

5. **Upload Web Files to SPIFFS**
   Use the SPIFFS upload script to upload the web files:
   ```bash
   pio run --target uploadfs --environment esp32-s3-devkitc-1
   ```

6. **Access the WebUI**
   - Connect to the WiFi network created by the ESP32 (SSID: `WiFiDuck`, Password: `password123`).
   - Open a browser and navigate to `http://192.168.4.1`.

## Usage
- Use the WebUI to manage scripts, view device status, and configure settings.
- The WebUI includes options to upload, edit, and execute scripts.

## Troubleshooting
- If the WebUI does not load, ensure the SPIFFS upload was successful.
- Check the serial monitor for error messages:
  ```bash
  pio device monitor
  ```

## License
This project is licensed under the MIT License. See the LICENSE file for details.