int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
int trigPin = 13;
int echoPin = 12;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int frontDistance = getDistance();
  if (frontDistance < 25) {
    stopMotors();
    delay(500);
    int clearDirection = scanForClearPath();
    if (clearDirection < 0) {
      turnLeft(90);
    } else {
      turnRight(90);
    }
    moveForward();
    delay(1000);
  } else {
    moveForward();
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  Serial.print("Distance: ");
  Serial.println(duration * 0.034 / 2);
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

int scanForClearPath() {
  int maxDistance = 0;
  int clearDirection = 0;
  turnLeft(45);
  int leftDistance = getDistance();
  if (leftDistance > maxDistance) {
    maxDistance = leftDistance;
    clearDirection = -1;
  }
  turnRight(90);
  int rightDistance = getDistance();
  if (rightDistance > maxDistance) {
    maxDistance = rightDistance;
    clearDirection = 1;
  }
  turnLeft(45);
  if (maxDistance < 25) {
    moveBackward();
    delay(90);
    stopMotors();
    clearDirection = scanForClearPath();
  }
  return clearDirection;
}

void turnLeft(int degrees) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Turn Left");
  delay(degrees * 5); // Adjust the multiplier to calibrate turning
  stopMotors();
}

void turnRight(int degrees) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Turn Right");
  delay(degrees * 5); // Adjust the multiplier to calibrate turning
  stopMotors();
}
