#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 8;
const int stepsPerRevolution_360 = 2048;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
Servo myServo;

int stepCount = 0;
char inByte = 0;

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(640);
  myServo.attach(7);
  myServo.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();

    // Set one step
    if (inByte == 'a') {
      myStepper.step(stepsPerRevolution);
      myServo.write(0);
      delay(100);
    }

    //Rotate 360
    if (inByte == 'b') {
      myStepper.setSpeed(1000);
      myServo.attach(7);
      myServo.write(25);
      myStepper.step(stepsPerRevolution_360 * 2);
      delay(1000);
      myServo.write(0);
    }

    //Rotate 360 reversed
    if (inByte == 'c') {
      myStepper.setSpeed(1000);
      myServo.write(25);
      myStepper.step(-stepsPerRevolution_360 * 2);
      delay(1000);
      myServo.write(0);
    }
  }
}
