# 🪄 IoT Wand – ESP8266 Magic Controller

## 📖 Overview

This project is a **Harry Potter–themed IoT wand** built using an **ESP8266** microcontroller. The wand can detect gestures and trigger predefined magical effects, such as controlling lights, triggering sound effects, or interacting with other IoT-enabled devices. It was developed as part of the **EMPNEO 9.0 IEEE MEC** event.

The wand acts as a **gesture-based wireless controller**, with the ESP8266 handling communication and signal processing.

---

## ⚙️ Hardware Components

* **ESP8266 (NodeMCU 1.0 / ESP-12E module)** – main microcontroller with Wi-Fi support
* **MPU6050 (Accelerometer + Gyroscope)** – gesture/rotation detection
* **IR LED / RF Module (optional)** – for remote triggering
* **Push Buttons** – fallback input / reset
* **Battery (Li-ion / Li-Po + charging module)** – portable power supply
* **3D Printed Wand Body** – casing for aesthetics

---

## 🛠️ Software Stack

* **Arduino IDE / PlatformIO** for firmware development
* **C++ (Arduino Core for ESP8266)**
* **ESP8266WiFi & WebServer Libraries** – for Wi-Fi/AP mode hosting
* **Wire.h & MPU6050 library** – for sensor data acquisition
* **FastLED / NeoPixel library (if LEDs used)** – for visual magical effects

---

## 🔑 Features

* **Gesture Recognition:** Detects wand motions (swish, flick, circle, etc.) using the MPU6050.
* **Wi-Fi Control:** ESP8266 runs a lightweight server to interact with connected devices.
* **Real-Time Response:** Low-latency gesture-to-action pipeline.
* **Custom Spells:** Map different gestures to IoT actions (light control, sound, animations).
* **Portable & Wireless:** Powered by rechargeable battery.

---

## 📡 System Architecture

1. **Motion Capture** → MPU6050 sends raw accelerometer & gyroscope data via I2C.
2. **Processing Layer** → ESP8266 processes sensor data, applies thresholds/filters to detect gestures.
3. **Action Mapping** → Gesture ID mapped to a predefined spell/action.
4. **Output Layer** →

   * Wi-Fi packet to connected IoT device
   * GPIO trigger (LEDs, relays, sound modules)
   * IR/RF transmission (optional)

---

### Install Dependencies

* Install **Arduino IDE** or **PlatformIO**
* Add **ESP8266 board support** ([Board Manager URL](http://arduino.esp8266.com/stable/package_esp8266com_index.json))
* Install required libraries:

  * `ESP8266WiFi`
  * `ESP8266WebServer`
  * `Wire`
  * `Adafruit_MPU6050` (or Jeff Rowberg's MPU6050 library)
  * `FastLED` (optional)

###  Flash Code

* Select **NodeMCU 1.0 (ESP-12E)** board in Arduino IDE.
* Connect ESP8266 via USB and upload the codes for transmitter and receiver accordingly.

---

## 🧪 Usage

1. Power the wand (battery/USB).
2. Connect to the ESP8266 AP or configure it to join local Wi-Fi.
3. Perform a gesture (e.g., swish → lights on, flick → lights off).
4. Observe the output action (via LEDs, IoT device, or server response).

---

## 🔍 Future Improvements

* Add **machine learning gesture classification** (TinyML / TensorFlow Lite).
* Integrate **sound effects** with DFPlayer Mini.
* Expand spell set with **complex gesture combinations**.
* Add **MQTT protocol** for integration with smart home systems.

---

## 👥 Contributors

* **Gautham P Nair** – Tech Team
* **Aiswarya VM** – Tech Team
* **Reyna Mary John** – Tech Team
* Special thanks to **IEEE MEC EMPNEO 9.0 Tech & Ambience Teams** for support.

---
