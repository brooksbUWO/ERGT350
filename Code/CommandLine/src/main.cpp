// ****************************************************************************
// Title		: Command Line Interface (CLI) Example
// File Name	: 'main.cpp'
// Revision		: 1.0
// Target MCU	: Espressif ESP32 (Doit DevKit Version 1)
//
// This program is for ERGT350 Data Protocols lab. We will be using the ESP32
// serial port to communicate with the computer using Bray's termial program.
// We will be using a usb logic analyser to capture the serial data and
// and analyse the data using PulseView.
//
// Revision History:
// When			Who			Description of change
// -----------	-----------	-----------------------
// 10-MAY-2024	brooks		program start
// *****************************************************************************

// Include Files
// ****************************************************************************
#include <Arduino.h>
#include <HardwareSerial.h> // Library for hardware serial
#include <SimpleCLI.h>      // github.com/spacehuhn/SimpleCLI

// Globals
// ****************************************************************************
#define RX2 16                         // Serial receive pin
#define TX2 17                         // Serial transmit pin
HardwareSerial serial2(2);             // Instantiate UART2
unsigned long timePrevious = millis(); // Time of last LED toggle
const uint8_t LEDPIN = LED_BUILTIN;    // Pin number connected to LED
bool ledState = false;                 // LED state false=LOW, true=HIGH
char readData[40];                     // Buffer for serial read
uint8_t readDataLen = 0;               // Length of buffer data

// Function Prototypes
// ****************************************************************************

// Begin Code
// ****************************************************************************
void setup()
{
    delay(3000);             // Wait for serial monitor to open on pc
    Serial.begin(115200);    // Start serial monitor baud rate=115200
    Serial.println();        // Blank line for readability
    pinMode(LEDPIN, OUTPUT); // Set pin digital output

    serial2.begin(115200, SERIAL_8N1, RX2, TX2, false, 20000UL, 112U);
}

// Main program
// ****************************************************************************
void loop()
{
    if (millis() - timePrevious >= 1000) // Repeats every 1sec
    {
        ledState = !ledState;                        // Toggle LED on/off
        digitalWrite(LEDPIN, ledState ? HIGH : LOW); // Set LED state
        timePrevious = millis();                     // Reset time
    }

    if (serial2.available())
    {
        String receivedData = "";            // Create a string to store data
        String dataToSend = "";              // Create a string to store data
        receivedData = serial2.readString(); // Read the incoming data
        dataToSend = receivedData + " sent"; // Append " sent" to data
        serial2.println(dataToSend);         // Transmit the data back
        serial2.flush();                     // Clear the buffer
    }
}
