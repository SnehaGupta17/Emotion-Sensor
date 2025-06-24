### Supercool IoT Project ;)

# 🧠 Emotion Detection Sensor using Arduino

This project is an **Arduino-based Emotion Detection System** that estimates a person's **emotional state** in real-time by analyzing:

- 🫀 **Pulse Rate**
- 🌡️ **Body Temperature**
- ⚡ *(Optional)* **GSR (Galvanic Skin Response)**

It classifies emotions such as **Happy, Sad, Relaxed, and Angry** based on physiological data. Ideal for prototypes in **health tech, affective computing, or wearable devices**.

---

## 📌 Features

- Real-time **emotion classification** using body vitals  
- Detects and logs:
  - Heart Rate (BPM)
  - Body Temperature (°C)
  - GSR Value (Optional)
  - Pulse Wave Signal
- Emotion mapping based on BPM
- Serial output in **CSV format** for easy logging
- Pulse waveform filtering via custom digital filter

---

## 🛠️ Hardware Required

| Component              | Purpose                          | Connection |
|------------------------|----------------------------------|-------------|
| **Arduino UNO**        | Microcontroller                  | —           |
| **Pulse Sensor**       | Heart rate detection             | A0          |
| **One Wire Temp Sensor**| Body temperature measurement     | D5 (Digital)|
| **LED**                | Blinks on heartbeat              | D13         |
| **GSR Sensor**         | Measures Skin Conductivity       | A1          |
| **Breadboard**         | Mounting components              | —           |
| **Jumper Wires**       | Connections between components   | —           |
| **USB Port Cable**     | Upload code & power the board    | USB port    |

---

## 💡 Emotion Classification Logic

| Heart Rate (BPM)       | Emotion   |
|------------------------|-----------|
| 85 – 125               | 😄 Happy  |
| 80 – 90                | 😢 Sad    |
| 65 – 79                | 😌 Relaxed|
| Above 125              | 😡 Angry  |

> Threshold values can be calibrated for individual differences.

---

## 📸 Output Result

---

## 🚀 Getting Started

### 1. Circuit Setup
- Connect components on breadboard as per pin table
- Use **4.7kΩ pull-up resistor** with **DS18B20** between **D5** and **VCC**
- GSR sensor connected to **A1**
- Pulse Sensor to **A0**
- LED to **D13**

### 2. Software Setup
Install the following libraries in Arduino IDE:
- PulseSensor Playground
- OneWire
- DallasTemperature

### 3. Upload and Monitor
- Upload the `.ino` code
- Open **Serial Monitor** at **9600 baud**
- View real-time emotion prediction and vitals

---

## ⚙️ Note
- Emotion logic is based on **heart rate only** (can be extended to use **GSR + temperature**)

---
## 🖥️ Sample Serial Output

```csv
LABEL,Computer Time,Heart Rate,Body Temperature,GSR,Pulse
DATA, TIME,78,36.7,520,0.42,RELAXED

