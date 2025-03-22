# Smart Waste Bin Monitoring System

## Overview
This project implements a smart waste bin monitoring system using an ESP8266 microcontroller. The system uses an ultrasonic sensor to detect the fill level of a waste bin and provides visual feedback through LEDs and an LCD display. When the bin is nearly full, it displays a flashing alert message and changes the LED indicator from green to yellow.

## Features
- Real-time waste bin fill level monitoring
- Visual alerts via LCD display
- LED status indicators (green for available, yellow for full)
- ThingSpeak integration for remote monitoring
- Wi-Fi connectivity

## Hardware Requirements
- ESP8266 NodeMCU or similar board
- Ultrasonic sensor (HC-SR04 or similar)
- I2C LCD display (20x4 characters)
- 2 LEDs (1 green, 1 yellow)
- 2 resistors (220-330 ohm) for LEDs
- Breadboard and jumper wires
- Power supply (USB or external)

## Wiring Instructions

### Ultrasonic Sensor
- TRIG_PIN → GPIO0 (D3) on ESP8266
- ECHO_PIN → GPIO2 (D4) on ESP8266
- VCC → 5V
- GND → GND

### LCD Display (I2C)
- SDA → GPIO4 (D2) on ESP8266
- SCL → GPIO5 (D1) on ESP8266
- VCC → 5V
- GND → GND

### LEDs
- Green LED → GPIO12 (D6) on ESP8266 (with resistor)
- Yellow LED → GPIO14 (D5) on ESP8266 (with resistor)

## Software Setup

### Required Libraries
- ESP8266WiFi
- Wire
- LiquidCrystal_I2C
- Ultrasonic

Install these libraries through the Arduino IDE Library Manager or manually from their repositories.

### ThingSpeak Configuration
1. Create a free account on [ThingSpeak](https://thingspeak.com/)
2. Create a new channel with at least one field (for distance measurements)
3. Note your channel API key and replace it in the code:
   ```cpp
   String apiKey = "ThingSpeak API key"; // Replace with your ThingSpeak API key
   ```

### Wi-Fi Configuration
Update the Wi-Fi credentials in the code:
```cpp
const char* ssid = "YourNetworkName";
const char* password = "YourNetworkPassword";
```

## Usage
1. Upload the code to your ESP8266 using the Arduino IDE
2. The system will automatically connect to Wi-Fi
3. The LCD will display "Throw Waste here" when the bin has space
4. When the bin is nearly full (distance < 10cm), the LCD will flash "Bin is full!!" and the LED will change from green to yellow
5. Data is sent to ThingSpeak for remote monitoring

## Customization
- Adjust the distance threshold in the code to match your bin size:
  ```cpp
  if (distance < 10) { // adjust this value as needed
  ```
- Modify the messages displayed on the LCD by changing the string constants
- Adjust the flicker interval for the alert message:
  ```cpp
  const long flickerInterval = 500; // in milliseconds
  ```

## Troubleshooting
- If the LCD doesn't display anything, check the I2C address (default is 0x27)
- If Wi-Fi connection fails, verify your credentials and network availability
- If distance readings are inconsistent, check the ultrasonic sensor wiring and positioning

## Note
The current implementation in the code doesn't actually send data to ThingSpeak yet, although the Wi-Fi connection is established. To complete this functionality, you would need to add the code for sending HTTP requests to ThingSpeak in the loop function.
