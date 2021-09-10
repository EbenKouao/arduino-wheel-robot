/*

  Author: Smartbuilds.io
  Description: Build you own Simple Arduino Wheeled Robot
  Website: https://smartbuilds.io

*/

/*
  PWM dictates the angle of turn of the motor
  Slow Turn => 60% PWM Duty Cycle
  Hard Turn => 95% PWM Duty Cycle
*/

//Mega PWM Pins (2-13) (44-46)

#include <RobojaxBTS7960.h>

int reserved_BlutoothRX  = 0;
int reserved_BlutoothTX  = 1;

// r Motor 1
#define RPWM_L1 3 // define pin 3 for RPWM pin (output)
#define R_EN_L1 11 // define pin 2 for R_EN pin (input)
#define R_IS_L1 10 // define pin 5 for R_IS pin (output)
#define LPWM_L1 2 // define pin 6 for LPWM pin (output)
#define L_EN_L1 12 // define pin 7 for L_EN pin (input)
#define L_IS_L1 13 // define pin 8 for L_IS pin (output)

// Right Motor 2
#define RPWM_L2 7 // define pin 3 for RPWM pin (output)
#define R_EN_L2 23 // define pin 2 for R_EN pin (input)
#define R_IS_L2 22 // define pin 5 for R_IS pin (output)
#define LPWM_L2 6 // define pin 6 for LPWM pin (output)
#define L_EN_L2 24  // define pin 7 for L_EN pin (input)
#define L_IS_L2 25 // define pin 8 for L_IS pin (output)

// Left Motor 1
#define RPWM_R1 5 // define pin 3 for RPWM pin (output)
#define R_EN_R1 47 // define pin 2 for R_EN pin (input)
#define R_IS_R1 46 // define pin 5 for R_IS pin (output)
#define LPWM_R1 4 // define pin 6 for LPWM pin (output)
#define L_EN_R1 48 // define pin 7 for L_EN pin (input)
#define L_IS_R1 49 // define pin 8 for L_IS pin (output)

// l  Motor 2
#define RPWM_R2 9 // define pin 3 for RPWM pin (output)
#define R_EN_R2 51 // define pin 2 for R_EN pin (input)
#define R_IS_R2 50 // define pin 5 for R_IS pin (output)
#define LPWM_R2 8 // define pin 6 for LPWM pin (output)
#define L_EN_R2 52 // define pin 7 for L_EN pin (input)
#define L_IS_R2 53 // define pin 8 for L_IS pin (output)


#define CW 1 //do not change
#define CCW 0 //do not change
#define debug 1 //change to 0 to hide serial monitor debugging infornmation or set to 1 to view

int PWM_max = 100; //max speed of the Motor (Wheels)
int PWM_min = 80; //min speed of the Motor (Wheels)

int delay_motor = 3000;
int motor_high = 750;

RobojaxBTS7960 motor_L1(R_EN_L1, RPWM_L1, R_IS_L1, L_EN_L1, LPWM_L1, L_IS_L1, debug);
RobojaxBTS7960 motor_L2(R_EN_L2, RPWM_L2, R_IS_L2, L_EN_L2, LPWM_L2, L_IS_L2, debug);

RobojaxBTS7960 motor_R1(R_EN_R1, RPWM_R1, R_IS_R1, L_EN_R1, LPWM_R1, L_IS_R1, debug);
RobojaxBTS7960 motor_R2(R_EN_R2, RPWM_R2, R_IS_R2, L_EN_R2, LPWM_R2, L_IS_R2, debug);

void setup() {
  Serial.begin(9600);// setup Serial Monitor to display information

  //Initate Motors
  motor_L1.begin();
  motor_L2.begin();
  motor_R1.begin();
  motor_R2.begin();

}

void loop() {

  // Debug - Run Robot Test 
  //  motor_test_directions();

  //Recieve Commands via Serial Comms to control the Robot.

  //Recieve Serial commands to control the Robot
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Command Recieved: ");
    Serial.println(data);

    //Move Droiid Bot
    if (data == "Left") {
      motor_Right(60, CW, CCW);
      Serial.print("Right");
    }

    if (data == "Right") {
      motor_Left(60, CCW, CW);
      Serial.print("Left");
    }


    if (data == "Forward") {
      motor_Forward(60, CW, CCW);
      Serial.print("Forward");
    }

    if (data == "Reverse") {
      motor_Reverse(60, CCW, CW);
      Serial.print("Reverse");
    }

  }


}

void motor_Left(int PWM_pcntg, int dir, int dir_ccw) {

  motor_R1.rotate(PWM_pcntg, dir);
  motor_R2.rotate(PWM_pcntg, dir_ccw);

  delay(motor_high);

  motor_R1.stop();
  motor_R2.stop();

}

void motor_Right(int PWM_pcntg, int dir, int dir_ccw) {

  motor_L1.rotate(PWM_pcntg, dir);
  motor_L2.rotate(PWM_pcntg, dir);

  delay(motor_high);

  motor_L1.stop();
  motor_L2.stop();

}

void motor_Forward(int PWM_pcntg, int dir, int dir_ccw) {

  motor_L1.rotate(PWM_pcntg, dir);
  motor_L2.rotate(PWM_pcntg, dir);
  motor_R1.rotate(PWM_pcntg, dir_ccw);
  motor_R2.rotate(PWM_pcntg, dir_ccw);


  delay(motor_high);

  motor_L1.stop();
  motor_L2.stop();
  motor_R1.stop();
  motor_R2.stop();


}

void motor_Reverse(int PWM_pcntg, int dir, int dir_ccw) {


  motor_L1.rotate(PWM_pcntg, dir_ccw);
  motor_L2.rotate(PWM_pcntg, dir_ccw);
  motor_R1.rotate(PWM_pcntg, dir_ccw);
  motor_R2.rotate(PWM_pcntg, dir_ccw);

  delay(motor_high);

  motor_L1.stop();
  motor_L2.stop();
  motor_R1.stop();
  motor_R2.stop();

}

//Debug Motor Directions
void motor_test_directions() {
  motor_Left(60, CCW, CW);
  delay(delay_motor);
  motor_Right(60, CCW, CW);
  delay(delay_motor);
  motor_Forward(60, CCW, CCW);
  delay(delay_motor);
  motor_Reverse(60, CW, CW);
  delay(delay_motor);
}
