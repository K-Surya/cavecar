// CaveCar by Team : Serial Byters
// version: 1.0.1
// Authors : Surya K, Varghese K James, Sujith M

// Servo
#include<Servo.h>
Servo Myservo;
int pos;


// Motor Driver Pins
const int motor1Pin1 = 8;  // Left motor forward
const int motor1Pin2 = 9;  // Left motor backward
const int motor2Pin1 = 11;  // Right motor forward
const int motor2Pin2 = 10;  // Right motor backward

// IR Sensor Pin
const int irSensorPin = 2;

// Ultrasonic Sensor Pins
const int trigPin = 6;
const int echoPin = 5;

void setup() {
  
  // Initialize motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
 
  // Initialise IR sensor pin as input
  pinMode(irSensorPin, INPUT);

  // Initialise ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initiate servo pin
  Myservo.attach(3);
 
  // Initialize serial communication for debugging
  Serial.begin(9600);

}


void loop() {

  // Read IR sensor value
  int sensorValue = digitalRead(irSensorPin);
 
  // Map cave ceiling before moving
  stopCar();
  mapCaveCeiling();
 
  // Obstacle Detection
  if (sensorValue == 0) {  // Obstacle detected
    Serial.print("Obstacle detected - Turning right");
    Serial.println(sensorValue);
    turnRight();
    delay(2000);  // Turn for 500ms
    stopCar();
    delay(100);  // Brief pause
    return;
  } else {  // No obstacle
    Serial.println("Path clear - Moving forward");
    moveForward();
    delay(5000);
  }
}

// To move the car forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// To turn the car right
void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// To stop the car
void stopCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}


// Ultrasonic sensor function
float getDistance() {

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 
  // Send 10 microsecond pulse to trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the echo pin, return travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
 
  // Calculate distance in cm (speed of sound = 343 m/s)
  float distance = (duration * 0.0343) / 2;
 
  return distance;
}

// Map the cave profile 
void mapCaveCeiling() {

  float distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  int pos = 0;
  for (int i = 0; i < 10; i++) {

    t18();
    delay(1000);
    
    if (distance < 10.0) {
      Serial.print('#');  // Very low ceiling
    } else if (distance < 20.0) {
      Serial.print('*');  // Low ceiling
    } else if (distance < 30.0) {
      Serial.print('-');  // Medium ceiling
    } else if (distance < 40.0) {
      Serial.print('.');  // High ceiling
    } else {
      Serial.print(' ');;  // Very high ceiling
    }
  }

  //reset it by turning in -180 degress
  for (int j = 180; j >=0; j--) {
    Myservo.write(j);
    delay(15);
  }

}


// To turn the servo for 18 degrees
void t18() {
  for (int j = 0; j <= 18; j++) {
    Myservo.write(pos + j);
    delay(15);
  }
  pos += 18; // update position after movement
}
