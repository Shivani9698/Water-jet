const int DIR = 9;
const int STEP = 6;
const int steps_per_rev = 1600; // Adjusted for 1/8 microstepping
int a = 100; // Pulse width in microseconds

void setup() {
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}

void loop() {
  // Clockwise rotation
  digitalWrite(DIR, LOW); // Set direction to LOW for clockwise
  Serial.println("Spinning CounterClockwise...");
  
  for (int i = 0; i < 6*steps_per_rev; i++) { // Two full rotations
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
  
  delay(1000); // Wait 1 second after two full rotations
  
  // Counterclockwise rotation
  digitalWrite(DIR, HIGH); // Set direction to HIGH for counterclockwise
  Serial.println("Spinning Clockwise...");

  for (int i = 0; i <  6*steps_per_rev; i++) { // Two full rotations
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }

  delay(1000); // Wait 1 second after two full rotations

  // Clockwise rotation
  digitalWrite(DIR, HIGH); // Set direction to LOW for clockwise
  Serial.println("Spinning Clockwise...");
  
  for (int i = 0; i < 6*steps_per_rev; i++) { // Two full rotations
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
  
  delay(1000); // Wait 1 second after two full rotations
  
  // Counterclockwise rotation
  digitalWrite(DIR, LOW); // Set direction to HIGH for counterclockwise
  Serial.println("Spinning CounterClockwise...");

  for (int i = 0; i <  6*steps_per_rev; i++) { // Two full rotations
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
  delay(1000);
}
