# Lab-2-CS-596-IOT
Lab 2 traffic light for CS 596 IOT at SDSU.

Members(Solo): Aeron Flores 

Video Demo Link: https://youtube.com/shorts/QYKyrLP9Luw?feature=share

# 🚦 Traffic Light & Pedestrian Crossing System  

This project is an **Arduino-based traffic light and pedestrian crossing system** using an **ESP32**, a **TFT LCD display**, and an **active buzzer**. The system simulates real-world traffic signals with a pedestrian push button to request crossing.

## 📌 Features  
- **Traffic Light Control**: Green, yellow, and red lights operate in a cycle.  
- **Pedestrian Crossing System**: Pressing a button modifies the light cycle to allow safe pedestrian crossing.  
- **Buzzer Alerts**: Audible signals indicate crossing times.  
- **TFT LCD Display**: Visual representation of traffic lights.

## 🛠 Hardware Components  
- **ESP32 microcontroller**  
- **TFT LCD Display (TFT_eSPI library)**  
- **Active Buzzer**  
- **Push Button**  
- **LEDs for traffic lights**  

## 🔧 Pin Configuration  
| Component     | GPIO Pin |
|--------------|---------|
| Red LED      | 26      |
| Yellow LED   | 32      |
| Green LED    | 17      |
| Push Button  | 37      |
| Buzzer       | 15      |

## 📝 How It Works  
1. **Normal Traffic Cycle**:  
   - Green light for **10 seconds** → Yellow for **2 seconds** → Red for **10 seconds**.  
2. **Pedestrian Button Pressed**:  
   - Green light changes to **5 seconds**.  
   - Yellow light for **2 seconds**.  
   - Red light for **10 seconds** with buzzer alert.  
3. **Traffic resumes** after pedestrian crossing.


## 🚀 Getting Started  
1. Install the **TFT_eSPI** and **SPI** libraries in the **Arduino IDE**.  
2. Connect the ESP32 and components as per the **pin configuration**.  
3. Upload `main.cpp` to the ESP32.  
4. Observe the **traffic light simulation** and test the **pedestrian crossing button**.  

# ⚙️ PlatformIO Project Configuration  

This repository contains a **PlatformIO** configuration file (`platformio.ini`) for an **ESP32-based project** using the **TTGO LoRa32 V1** development board. The project is built with the **Arduino framework** and includes the **TFT_eSPI** library for display control.

## 📌 Configuration Details  

The `platformio.ini` file defines the build environment for the **TTGO LoRa32 V1** board:

```ini
[env:ttgo-lora32-v1]
platform = espressif32
board = ttgo-lora32-v1
framework = arduino
monitor_speed = 115200
lib_deps = bodmer/TFT_eSPI@^2.5.43



