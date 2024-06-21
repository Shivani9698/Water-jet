const int DIR = 9;
const int STEP = 6;
const int steps_per_rev = 5000;
int a = 100;

void setup() {
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}

void loop() {
  // Clockwise rotation
  digitalWrite(DIR, LOW); // Set direction to LOW for clockwise
  Serial.println("Spinning Clockwise...");
  
  for (int i = 0; i <steps_per_rev ; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
  delay(1000); 
  
  // Counterclockwise rotation
  digitalWrite(DIR, HIGH); // Set direction to HIGH for counterclockwise
  Serial.println("Spinning Anti-Clockwise...");

  for (int i = 0; i < steps_per_rev; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(a);
    digitalWrite(STEP, LOW);
    delayMicroseconds(a);
  }
  delay(1000);
}
