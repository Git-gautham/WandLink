#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "ESP_SIGNAL_NET";
const char* password = "esp123456";

WiFiServer server(1234);  // TCP Server on port 1234
const int ledPin = 13;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.softAP(ssid, password);
  server.begin();
  Serial.println("Receiver ready");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char signal = client.read();
        Serial.print("Received: "); Serial.println(signal);

        if (signal == '1') {
          digitalWrite(ledPin, HIGH);
        } else if (signal == '0') {
          digitalWrite(ledPin, LOW);
        }
      }
    }
    client.stop();
  }
}
