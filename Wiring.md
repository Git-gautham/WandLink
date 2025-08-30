# 🔌 Pin Diagram (as per code)

## A) Receiver (ESP8266 running TCP **server**)

Purpose: Listens on TCP port **1234**; toggles an LED on **GPIO13** based on incoming `'1'/'0'`.

* **ESP8266 NodeMCU pins**

  * **D7 (GPIO13)** → **LED+** (through a 220–1kΩ resistor)

    * LED− → **GND**
  * **3V3** → (optional if LED module has VCC; for a raw LED you don’t use 3V3)
  * **GND** → LED− (common ground)
  * **USB** → for power + Serial monitor

> In code: `const int ledPin = 13;` → **GPIO13 (D7)**

**Minimal wiring (Receiver):**

```
NodeMCU (Server)
┌─────────────┐
│ D7 (GPIO13) ├───[220–1kΩ]──►|── GND       (LED with series resistor)
│     3V3     │
│     GND     │
│     USB     │ Power + Serial
└─────────────┘
```

---

## B) Wand (ESP8266 running **client** + MPU6050 over I²C)

Purpose: Reads acceleration from **MPU6050**, detects a flick, toggles a `currentState`, and sends `'1'/'0'` via TCP to the receiver.

### ESP8266 NodeMCU ↔ MPU6050 (I²C)

* **D1 (GPIO5)** → **SCL** (MPU6050)
* **D2 (GPIO4)** → **SDA** (MPU6050)
* **3V3** → **VCC** (MPU6050)
* **GND** → **GND** (MPU6050)
* *(INT pin not used in your code; leave unconnected or wire later if you add interrupts.)*

### Status LED (as per code)

* **TX (GPIO1)** → **Status LED+** (through 220–1kΩ resistor)

  * LED− → **GND**

> In code: `const int statusLedPin = 1;` → **GPIO1 (TX)**

**Important note:** GPIO1 is the UART **TX** pin. You’re using `Serial.begin(115200)` **and** driving GPIO1 as an LED. That can cause conflicts/garbled serial output. If you want stable Serial logs, consider changing:

```cpp
// Safer alternative (optional):
const int statusLedPin = 2; // D4 (GPIO2, onboard LED on many NodeMCU boards, active LOW)
```

If you switch to D4, remember it’s often **active LOW** (write `LOW` to turn it ON).

**Wiring (Wand):**

```
NodeMCU (Client)                    MPU6050 Breakout
┌─────────────┐                     ┌───────────────┐
│ D1 (GPIO5)  ├────────────────────►│ SCL           │
│ D2 (GPIO4)  ├────────────────────►│ SDA           │
│ 3V3         ├────────────────────►│ VCC (3.3V)    │
│ GND         ├────────────────────►│ GND           │
│ TX (GPIO1)  ├──[220–1kΩ]──►|── GND  (Status LED as per code)
│ USB         │
└─────────────┘                     └───────────────┘
```

---

