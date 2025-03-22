#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

// Set the LCD address (0x27 is the default)
#define LCD_ADDRESS 0x27

// Your Wi-Fi credentials
const char* ssid = "AshwinPhone";
const char* password = "11111111";

// ThingSpeak API key and server details
const char* server = "api.thingspeak.com";
String apiKey = "AK2OCVFBF6W1JU8I"; // Replace with your ThingSpeak API key

// Create an instance of the LCD class
LiquidCrystal_I2C lcd(LCD_ADDRESS, 20, 4); // 20 characters, 4 lines

// Define the ultrasonic sensor pins
#define TRIG_PIN 0
#define ECHO_PIN 2

// Create an instance of the Ultrasonic class
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Define the LED pins
#define YELLOW_LED 14 
#define GREEN_LED 12

// Define the messages to be displayed on the LCD
const char* fullMessage = "Bin is full!!";

// Timing variables to control flickering
unsigned long previousMillis = 0;
const long flickerInterval = 500; // Flicker every 500ms
bool isFlickering = false;

// ThingSpeak update interval (15 seconds)
const long thingSpeakInterval = 15000;
unsigned long lastThingSpeakUpdate = 0;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize the LEDs as OUTPUT
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Set the default LED state 
  digitalWrite(GREEN_LED, HIGH); // Green ON initially
  digitalWrite(YELLOW_LED, LOW); 

  // Connect to Wi-Fi
  connectWiFi();
}

void loop() {
  // Read the ultrasonic sensor value
  int distance = ultrasonic.read();

  // Display appropriate message on LCD and control LEDs based on distance
  if (distance < 10) { // adjust the distance threshold as needed
    
    // --- LED Control ---
    digitalWrite(GREEN_LED, LOW);  // Turn OFF green LED
    digitalWrite(YELLOW_LED, HIGH); // Turn ON yellow LED

    // Flicker "Bin is full!!" message
    flickerText(fullMessage);

  } else { 
    
    // --- LED Control ---
    digitalWrite(GREEN_LED, HIGH); // Turn ON green LED
    digitalWrite(YELLOW_LED, LOW);  // Turn OFF yellow LED 

    // Display default message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Throw Waste here");
    isFlickering = false;  // Stop flickering when bin is not full
  }

  // Send data to ThingSpeak every 15 seconds
  if (millis() - lastThingSpeakUpdate > thingSpeakInterval) {
    sendToThingSpeak(distance);
    lastThingSpeakUpdate = millis();
  }

  delay(100); // Small delay to prevent excessive sensor reads
}

void flickerText(const char* text) {
  unsigned long currentMillis = millis();

  // Flicker the text at intervals
  if (currentMillis - previousMillis >= flickerInterval) {
    previousMillis = currentMillis; // Save the current time

    if (isFlickering) {
      // Clear the line (simulate flicker off)
      lcd.setCursor(0, 0);
      lcd.print("                    "); // Clear the entire line with spaces
      isFlickering = false;
    } else {
      // Clear the line and print the "Bin is full!!" message (simulate flicker on)
      lcd.setCursor(0, 0);
      lcd.print("                    "); // Clear the entire line with spaces
      lcd.setCursor(0, 0);
      lcd.print(text);
      isFlickering = true;
    }
  }
}

void connectWiFi() {
  // Attempt to connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

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