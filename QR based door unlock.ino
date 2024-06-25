#include <SoftwareSerial.h>

// Define the RX and TX pins for SoftwareSerial
const int qrScannerRX = 2;
const int qrScannerTX = 3;

// Define the pin for the solenoid lock
const int solenoidPin = 8;

// Create a SoftwareSerial object for communication with the QR code scanner
SoftwareSerial qrScanner(qrScannerRX, qrScannerTX);

// State to track the door lock status
bool isLocked = true;

void setup() {
  // Start the hardware serial communication for debugging
  Serial.begin(115200);

  // Start the software serial communication with the QR code scanner
  qrScanner.begin(9600);

  // Set the solenoid pin as an output
  pinMode(solenoidPin, OUTPUT);

  // Ensure the solenoid is locked at startup
  digitalWrite(solenoidPin, LOW);

  Serial.println("QR Code Scanner Ready. Scan a QR code.");
}

void loop() {
  // Check if data is available from the QR code scanner
  if (qrScanner.available()) {
    // Read the incoming data from the QR code scanner
    String qrCodeData = qrScanner.readStringUntil('\n');
    qrCodeData.trim(); // Remove any trailing newline characters

    // Print the scanned QR code data to the Serial Monitor
    Serial.print("Scanned QR Code: ");
    Serial.println(qrCodeData);

    // If a valid QR code is scanned, toggle the solenoid state
    if (isValidQRCode(qrCodeData)) {
      if (isLocked) {
        unlockSolenoid();
      } else {
        lockSolenoid();
      }
      // Toggle the lock state
      isLocked = !isLocked;
    }
  }
}

// Function to check if the scanned QR code is valid
bool isValidQRCode(String qrCodeData) {
  // Check if the QR code data matches the valid code "815847"
  return qrCodeData == "815847";
}

// Function to unlock the solenoid
void unlockSolenoid() {
  Serial.println("Welcome..I am your safe place");
  digitalWrite(solenoidPin, LOW); // Unlock the solenoid
  Serial.println("Solenoid unlocked.");
}

// Function to lock the solenoid
void lockSolenoid() {
  Serial.println("Goodbye.. See you again");
  digitalWrite(solenoidPin, HIGH); // Lock the solenoid
  Serial.println("Solenoid locked.");
}
