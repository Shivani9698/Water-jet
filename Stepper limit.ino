const int DIR = 9;
const int STEP = 6;
const int steps_per_rev = 1600; // Adjusted for 1/8 microstepping
int a = 200; // Pulse width in microseconds

int max_rotations = 5;  // Maximum rotations in each direction
int current_position = 0;
int initial_position = 0; // Initial position of the stepper motor

void setup() {
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  
  // Move to initial position
  moveStepper(abs(current_position - initial_position), current_position < initial_position ? LOW : HIGH);
  current_position = initial_position;
  
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
