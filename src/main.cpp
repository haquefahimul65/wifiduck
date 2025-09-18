#include <Arduino.h>
#include <BleKeyboard.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>


// WiFi credentials
const char* ssid = "WiFiDuck";
const char* password = "password123";

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);

    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }
    Serial.println("SPIFFS mounted successfully");

    // Set up WiFi Access Point
    WiFi.softAP(ssid, password);
    Serial.println("WiFi Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Serve static files from SPIFFS
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    // Start the server
    server.begin();
    Serial.println("HTTP server started");

    static BleKeyboard bleKeyboard;
    bleKeyboard.begin();
}

void loop() {
    // Placeholder for BLE command handling
}