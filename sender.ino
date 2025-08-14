#include <Wire.h>
#include <ESP8266WiFi.h>
#include <MPU6050.h>

const char* ssid = "ESP_SIGNAL_NET";
const char* password = "esp123456";
const IPAddress receiverIP(192, 168, 4, 1);
const uint16_t port = 1234;

WiFiClient client;
MPU6050 mpu;

const int statusLedPin = 1;  // External or onboard LED

bool currentState = false;   // 'false' means sending "0", 'true' means sending "1"
bool flickedRecently = false;

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected");
    digitalWrite(statusLedPin, HIGH); // Turn ON LED when connected
  } else {
    Serial.println("\n❌ Wi-Fi connection failed. Retrying...");
    digitalWrite(statusLedPin, LOW); // Turn OFF LED if not connected
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(statusLedPin, OUTPUT);
  digitalWrite(statusLedPin, LOW);

  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("✅ MPU6050 connected successfully");
  } else {
    Serial.println("❌ MPU6050 connection failed. Check wiring.");
    while (1);
  }

  connectToWiFi();
}

void loop() {
  // Reconnect to Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(statusLedPin, LOW);
    connectToWiFi();
  }

  // Read accelerometer
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  float accMag = sqrt(ax * ax + ay * ay + az * az) / 16384.0;

  // Detect a sharp motion flick
  if (accMag > 2.0 && !flickedRecently) {
    currentState = !currentState;  // Toggle state
    Serial.print("🌀 Flick detected → State changed to ");
    Serial.println(currentState ? "1" : "0");
    flickedRecently = true;
  }

  // Reset flickedRecently after motion settles
  if (accMag < 1.2) {
    flickedRecently = false;
  }

  // Always send current state every loop
  if (client.connect(receiverIP, port)) {
    client.print(currentState ? "1" : "0");
    client.stop();
  } else {
    Serial.println("⚠ Failed to connect to receiver");
  }

  delay(200); // Send every 200ms
}

