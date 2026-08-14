#include <Servo.h>

Servo Myservo;

#define trigPin 9
#define echoPin 8

#define MLa 6
#define MLb 7
#define MRa 4
#define MRb 5

long duration;
long straightDistance;
long rightDistance;
long leftDistance;
int maxDistance = 30;
int delayShort = 100;
int delayLong = 500;

void setup() {
  Serial.begin(9600);

  pinMode(MLa, OUTPUT);  // left go back
  pinMode(MLb, OUTPUT);  // left go front
  pinMode(MRa, OUTPUT);  // right go back
  pinMode(MRb, OUTPUT);  // right go front

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Myservo.attach(10);

  // servo starts straight
  Myservo.write(90);

  // make sure motors are stopped
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
}

void loop() {

  straightDistance = pingDistance();
  Serial.print("straight: ");
  Serial.println(straightDistance);

  // no obstruction
  if (straightDistance > maxDistance) {
    goForward();
  }

  // if obstruction
  else if (straightDistance > 0 && straightDistance <= maxDistance) {

    here:

    stopMoving();

    // measure left & right distances
    Myservo.write(180);  // left
    delay(delayLong);
    leftDistance = pingDistance();
    Serial.print("left: ");
    Serial.println(leftDistance);
    Myservo.write(0);  // right
    delay(delayLong);
    rightDistance = pingDistance();
    Serial.print("right: ");
    Serial.println(rightDistance);

    // center the servo
    Myservo.write(90);


    if (rightDistance > maxDistance && rightDistance >= leftDistance) {
      Serial.println("GOING RIGHT");
      goRight();
    }

    else if (leftDistance > maxDistance && leftDistance > rightDistance) {
      Serial.println("GOING LEFT");
      goLeft();
    }

    else {
      Serial.println("GOING BACK");
      goBackward();
      goto here;
    }
  }
}

//====================
//  ping the distance
//====================
long pingDistance() {

  long distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    distance = 0;
  } else {
    distance = duration / 58.2;
  }

  return distance;
}


//====================
// stop moving
//====================
void stopMoving() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
}


//====================
// move forward
//====================
void goForward() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
}


//====================
// move backward
//====================
void goBackward() {
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  delay(delayLong);
}


//====================
// turn right
//====================
void goRight() {
  goBackward();
  stopMoving();
  delay(delayShort);

  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  delay(delayLong);
}


//====================
// turn left
//====================
void goLeft() {
  goBackward();
  stopMoving();
  delay(delayShort);

  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  delay(delayLong);
}