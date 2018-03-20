#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <LiquidCrystal.h>

// Power button instantiations
int power_out = 3;
int power_button = 2; 
volatile int power = LOW; // for power button interrupt

// LED instantiations
int pole_leds = 1;

// Stepper motor instantiations
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor*motor = AFMS.getStepper(200,2);

// IMU instantiations
int mpu = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; // only need to look at GyZ
int16_t deg_total = 0;
int16_t prev_deg = 0;
int16_t threshold = 720;

// LCD screen instantiations
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int x; //variable to store voltage value when a key is pressed
String output = "";
int mode, mode_on = LOW; // the carousel mode; defines how it is moving

void setup() {
  Serial.begin(9600);

  // LCD screen setup
  lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):
//  pinMode(2, INPUT);

  // Power button set up (and interrupt)
  pinMode(power_button, INPUT);
  pinMode(power_out, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(power_button), power_check_ISR, RISING);

  // LED setup
  pinMode(pole_leds, OUTPUT);

  // Motor setup
  AFMS.begin(); //creating w default freq 1.6kHz

  // IMU setup
  Wire.begin();
  Wire.beginTransmission(mpu);
  Wire.write(0x6B);
  Wire.endTransmission(true);
}
  
void loop() {
  Serial.println(power);
  
  // check if system power is on for functioning
  if (power_button) {
    // Detect and display if button is pressed
    // TO DO: figure what each mode means and name them correctly
    x = analogRead(0);
    output = "Carousel Ready";
    
    if (x < 100) {
      // 'right' button
      output = "Mode 1";
      mode = 1;
      mode_on = HIGH;
    } 
    else if (x < 200) {
      // 'up' button
      output = "Mode 2";
      mode = 2;
      mode_on = HIGH;
    } 
    else if (x < 400) {
      // 'down' button
      output = "Mode 3"; 
      mode = 3;
      mode_on = HIGH;
    } 
    else if (x < 600) {
      // 'left' button
      output = "Mode 4";
      mode = 4;
      mode_on = HIGH;
    } 
  
    // writing information to lcd screen
    lcd.setCursor(0, 0);
    lcd.print(output);
    lcd.setCursor(0, 1);
    
    Serial.println(x);
    Serial.println(mode);
    Serial.println();
    digitalWrite(power_out, power);
    digitalWrite(pole_leds, mode_on);
  
//    // alter stepper functioning based on what mode is pressed
//    // TO DO: decide what each mode will do (currently holds test stuff)
//    // TO DO: fix what the display is saying
//    // TO DO: fix stepper motor so lcd screen can run (drawing too much current) --> need a seperate power source
//    if (mode == 1) {
//      lcd.setCursor(0, 0);
//      lcd.print("Mode 1 running");
//      lcd.setCursor(0, 1);
//      
//  //    motor->setSpeed(2); // 2 rpm
//  //    motor->step(1000, FORWARD,SINGLE);
//    }
//    else if (mode == 2) {
//      lcd.setCursor(0, 0);
//      lcd.print("Mode 2 running");
//      lcd.setCursor(0, 1);
//      
//  //    motor->setSpeed(5); // 5 rpm
//  //    motor->step(1000, FORWARD,SINGLE);
//    }
//    else if (mode == 3) {
//      lcd.setCursor(0, 0);
//      lcd.print("Mode 3 running");
//      lcd.setCursor(0, 1);
//      
//  //    motor->setSpeed(10); // 10 rpm
//  //    motor->step(1000, FORWARD,SINGLE);
//    }
//    else if (mode == 4) {
//      lcd.setCursor(0, 0);
//      lcd.print("Mode 4 running");
//      lcd.setCursor(0, 1);
//      
//  //    motor->setSpeed(20); // 20 rpm
//  //    motor->step(1000, FORWARD,SINGLE);
//    }
  
    // changing the mode back to 0 to stop from running the case
    // TO DO: change to be more eloquent
    Serial.println(" ");
    mode = 0;
    mode_on = LOW;
  }

  else {
    lcd.clear();
  }
  
  //TO DO: turn LCD screen off (for an else statement)

//  if (!lcdState) { //meaning lcd has not changed mode
//    //read IMU data and keep stepper mode as is
//
//    // Reading IMU data
//    // TO DO: clean this up so we aren't reading all the IMU dat, just GyZ
//    Wire.beginTransmission(mpu);
//    Wire.write(0x3B);
//    Wire.endTransmission(false);
//    Wire.requestFrom(mpu,14,true);
//    AcX=Wire.read()<<8|Wire.read();
//    AcY=Wire.read()<<8|Wire.read();
//    AcZ=Wire.read()<<8|Wire.read();
//    Tmp=Wire.read()<<8|Wire.read();
//    GyX=Wire.read()<<8|Wire.read();
//    GyY=Wire.read()<<8|Wire.read();
//    GyZ=Wire.read()<<8|Wire.read();
//    delay(33);
//  
//    deg_total = deg_total + abs(GyZ - prev_deg);
//    if (deg_total >= threshold) {
//      // stop turning motor
//      motor->step(1, BACKWARD,SINGLE);
//    }
//
//    prev_deg = GyZ;
//  motor->step(500, FORWARD,SINGLE);
////  motor->step(100, BACKWARD,SINGLE);
//
//  }

}

void power_check_ISR() {
  power = !power;
}

