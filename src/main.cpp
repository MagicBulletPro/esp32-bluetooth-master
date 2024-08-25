#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

// Create a BluetoothSerial object to handle Bluetooth communication
BluetoothSerial SerialBT;

// Define a struct to encapsulate button-related variables
struct Button
{
  const int pin; // Pin where the button is connected
  int state;     // Current button state
  int lastState; // Last button state
  bool isOn;     // ON/OFF state to represent if the button is toggled
};

// Initialize an array of Button structs with initial values for multiple buttons
Button buttons[] = {
    {4, 0, 0, false}, // Button 1: connected to pin 4
    {5, 0, 0, false}, // Button 2: connected to pin 5
    {15, 0, 0, false} // Button 3: connected to pin 15
};

// Calculate the number of buttons in the array
const int numButtons = sizeof(buttons) / sizeof(buttons[0]);

// Function prototype for looping through buttons
void loopThroughButton();

void setup()
{
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set the built-in LED pin as output
  pinMode(BUILTIN_LED, OUTPUT);

  // Set all button pins as input
  for (int i = 0; i < numButtons; i++)
  {
    pinMode(buttons[i].pin, INPUT);
  }

  // Start Bluetooth communication in Master mode with device name "ESP32_Master"
  // Passing 'true' as the second argument enables master mode
  SerialBT.begin("ESP32_Master", true);
  Serial.println("ESP32 Master Bluetooth Serial Started. Discoverable as ESP32_Master.");

  // Attempt to connect to the slave ESP32 device
  while (!SerialBT.connect("ESP32_Slave"))
  {
    Serial.println("Trying to connect to ESP32_Slave...");
    delay(1000); // Wait for 1 second before retrying
  }

  // Once connected, print a confirmation message
  Serial.println("Connected to ESP32_Slave");
  // Turn on the built-in LED to indicate a successful connection
  digitalWrite(BUILTIN_LED, HIGH);
}

void loop()
{
  // Check if data is received from the slave device
  if (SerialBT.available())
  {
    // Read the incoming data from the slave device
    String received = SerialBT.readStringUntil('\n');
    Serial.println("Received from Slave: " + received);
  }

  // Call the function to handle button state changes
  loopThroughButton();

  delay(50); // Small delay to avoid overwhelming the loop
}

void loopThroughButton()
{
  // Loop through each button in the array
  for (int i = 0; i < numButtons; i++)
  {
    // Read the current state of the button
    buttons[i].state = digitalRead(buttons[i].pin);

    // Check if the button state has changed from its last recorded state
    if (buttons[i].state != buttons[i].lastState)
    {
      // If the button state has changed to HIGH, it indicates a button press
      if (buttons[i].state == HIGH)
      {
        // Toggle the ON/OFF state of the button
        buttons[i].isOn = !buttons[i].isOn;

        // Print the current state to the Serial Monitor
        Serial.print("Button on pin ");
        Serial.print(buttons[i].pin);
        Serial.print(": ");
        Serial.println(buttons[i].isOn ? "ON" : "OFF");

        // Create a JSON document to send the button state
        JsonDocument jsonDoc; 
        // Add the pin number and its state to the JSON document
        jsonDoc["pin_number"] = buttons[i].pin;
        jsonDoc["pin_status"] = buttons[i].isOn;

        // Serialize the JSON document into a string
        String jsonString;
        serializeJson(jsonDoc, jsonString);

        // Send the JSON string to the slave device via Bluetooth
        SerialBT.println(jsonString);
      }

      // Small delay to debounce the button press
      delay(50);
    }

    // Update the last state of the button for the next loop iteration
    buttons[i].lastState = buttons[i].state;
  }
}
