#include <EEPROM.h> // Include the EEPROM library

const int DIR = 9;
const int STEP = 6;
const int steps_per_rev = 1600; // Adjusted for 1/8 microstepping
int a = 200; // Pulse width in microseconds

int max_rotations = 6;  // Maximum rotations in each direction
int current_position = 0;

void setup() {
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  
  // Get the current position from EEPROM
  EEPROM.get(0, current_position);

  Serial.print("Initial position: ");
  Serial.println(current_position);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    handleCommand(input);
  }
}

void handleCommand(String command) {
  char direction = command.charAt(0);
  int rotations = command.substring(1).toInt();

  if (rotations < 1 || rotations > max_rotations) {
    Serial.println("Invalid rotation count. Must be between 1 and 5.");
    return;
  }

  if (direction == 'L') {
    if (current_position + rotations > max_rotations) {
      Serial.println("Reached maximum limit. Cannot move further left.");
      rotations = max_rotations - current_position;
      if (rotations <= 0) {
        return;
      }
    }
    moveStepper(rotations, HIGH); // Rotate counterclockwise
    current_position += rotations;
  } else if (direction == 'R') {
    if (current_position - rotations < -max_rotations) {
      Serial.println("Reached maximum limit. Cannot move further right.");
      rotations = -(current_position + max_rotations);
      if (rotations <= 0) {
        return;
      }
    }
    moveStepper(rotations, LOW); // Rotate clockwise
    current_position -= rotations;
  } else {
    Serial.println("Invalid command. Use 'R' for clockwise and 'L' for counterclockwise.");
  }
  
  // Save the current position to EEPROM
  EEPROM.put(0, current_position);

  Serial.print("Current position: ");
  Serial.println(current_position);
}

void moveStepper(int rotations, int direction) {
  // Set direction
  digitalWrite(DIR, direction);

  // Step the motor
  int steps = rotations * steps_per_rev;
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
}
