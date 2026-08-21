#include <AccelStepper.h>

#define STEP1 2
#define DIR1  3

#define STEP2 4
#define DIR2  5

#define STEP3 6
#define DIR3  7


AccelStepper motor1(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper motor2(AccelStepper::DRIVER, STEP2, DIR2);


AccelStepper motor3(AccelStepper::DRIVER, STEP3, DIR3);

String command;

void setup() {
  Serial.begin(115200);

  motor1.setMaxSpeed(1000);
  motor1.setAcceleration(500);

  motor2.setMaxSpeed(1000);
  motor2.setAcceleration(500);

  motor3.setMaxSpeed(1000);
  motor3.setAcceleration(500);

  motor1.setCurrentPosition(0);
  motor2.setCurrentPosition(0);
  motor3.setCurrentPosition(0);

  Serial.println("Gantry controller ready.");
  Serial.println();
  Serial.println("Commands:");
  Serial.println("X <steps>   - Move X axis (Motor 1 + Motor 2)");
  Serial.println("Y <steps>   - Move Y axis (Motor 3)");
  Serial.println("M1 <steps>  - Move Motor 1");
  Serial.println("M2 <steps>  - Move Motor 2");
  Serial.println("M3 <steps>  - Move Motor 3");
  Serial.println("ZERO        - Set all positions to 0");
  Serial.println("POS         - Show current positions");
}

void loop() {

  // Always run all motors
  motor1.run();
  motor2.run();
  motor3.run();

  if (Serial.available()) {

    command = Serial.readStringUntil('\n');
    command.trim();


    if (command.startsWith("X ")) {

      long position = command.substring(2).toInt();

      motor1.moveTo(position);
      motor2.moveTo(position);

      Serial.print("X axis moving to: ");
      Serial.println(position);
    }


    else if (command.startsWith("Y ")) {

      long position = command.substring(2).toInt();

      motor3.moveTo(position);

      Serial.print("Y axis moving to: ");
      Serial.println(position);
    }


    else if (command.startsWith("M1 ")) {

      long position = command.substring(3).toInt();

      motor1.moveTo(position);

      Serial.print("Motor 1 moving to: ");
      Serial.println(position);
    }


    else if (command.startsWith("M2 ")) {

      long position = command.substring(3).toInt();

      motor2.moveTo(position);

      Serial.print("Motor 2 moving to: ");
      Serial.println(position);
    }


    else if (command.startsWith("M3 ")) {

      long position = command.substring(3).toInt();

      motor3.moveTo(position);

      Serial.print("Motor 3 moving to: ");
      Serial.println(position);
    }

    else if (command.equalsIgnoreCase("ZERO")) {

      motor1.setCurrentPosition(0);
      motor2.setCurrentPosition(0);
      motor3.setCurrentPosition(0);

      Serial.println("All motor positions set to 0.");
    }

    else if (command.equalsIgnoreCase("POS")) {

      Serial.print("Motor 1: ");
      Serial.println(motor1.currentPosition());

      Serial.print("Motor 2: ");
      Serial.println(motor2.currentPosition());

      Serial.print("Motor 3: ");
      Serial.println(motor3.currentPosition());
    }


    else {

      Serial.println("Unknown command.");
    }
  }
}
