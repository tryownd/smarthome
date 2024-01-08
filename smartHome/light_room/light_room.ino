#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#define WIFI_SSID         "INDIHOME2"
#define WIFI_PASS         "bismillahdulu"
#define APP_KEY           "2fb6e62e-d8e4-4c6f-ba8c-f2f5cxxxxxxxx"
#define APP_SECRET        "61f0e396-c49e-47bd-9028-a6a8714151ae-4844ef20-1d7b-4ae7-b451-xxxxxxxxxx"
#define SWITCH_ID_1       "65981ee9ccc93539xxxxxxx"
#define RELAY_PIN_1       D5

bool onPowerState1(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_1, state ? LOW : HIGH);
  Serial.printf("Device 1 turned %s\r\n", state ? "on" : "off");
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricPro.onConnected([]() {
    Serial.printf("Connected to SinricPro\r\n");
  });
  SinricPro.onDisconnected([]() {
    Serial.printf("Disconnected from SinricPro\r\n");
  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(9600); // Ganti nilai baud rate sesuai kebutuhan
  Serial.printf("\r\n\r\n");

  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
