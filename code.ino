#include <AccelStepper.h>

#define STEP1 2
#define DIR1  3


#define STEP2 4
#define DIR2  5

AccelStepper motor1(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper motor2(AccelStepper::DRIVER, STEP2, DIR2);

void setup() {
  motor1.setMaxSpeed(1000);
  motor1.setAcceleration(500);

  motor2.setMaxSpeed(1000);
  motor2.setAcceleration(500);


  motor1.moveTo(2000);
  motor2.moveTo(2000);
}

void loop() {
  motor1.run();
  motor2.run();


  if (motor1.distanceToGo() == 0 && motor2.distanceToGo() == 0) {
    motor1.moveTo(-motor1.currentPosition());
    motor2.moveTo(-motor2.currentPosition());
  }
}
