/*
 * ThingSpeak Integration Example for Smart Waste Bin
 * 
 * This file demonstrates how to integrate the ThingSpeak functionality
 * with the smart waste bin monitoring system.
 */

#include <ESP8266WiFi.h>

// ThingSpeak Settings
const char* server = "api.thingspeak.com";
String apiKey = "YOUR_API_KEY"; // Replace with your ThingSpeak API key

// Function to send data to ThingSpeak
void sendToThingSpeak(int distance) {
  // Create a WiFi client
  WiFiClient client;
  
  // Connect to ThingSpeak server
  if (client.connect(server, 80)) {
    // Construct the data string
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(distance);
    postStr += "\r\n\r\n";
    
    // Send the HTTP POST request
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Connection to ThingSpeak failed");
  }
  
  // Close the connection
  client.stop();
}

/*
 * To integrate this with the main code:
 * 
 * 1. Include this function in your main sketch
 * 2. Call sendToThingSpeak(distance) in your loop function
 * 3. Add a delay after sending data to avoid exceeding ThingSpeak's rate limits
 * 
 * Example integration in loop():
 * 
 * void loop() {
 *   // Read the ultrasonic sensor value
 *   int distance = ultrasonic.read();
 *   
 *   // Rest of your existing code...
 *   
 *   // Send data to ThingSpeak every 15 seconds
 *   static unsigned long lastThingSpeakUpdate = 0;
 *   if (millis() - lastThingSpeakUpdate > 15000) {
 *     sendToThingSpeak(distance);
 *     lastThingSpeakUpdate = millis();
 *   }
 * }
 */