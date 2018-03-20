#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <LiquidCrystal.h>

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
int mode; // the carousel mode; defines how it is moving

// LED instantiations

// Interrupt instantiations
volatile int lcdState = LOW; 


void setup() {
  Serial.begin(9600);

  // Motor setup
  AFMS.begin(); //creating w default freq 1.6kHz

  // IMU setup
  Wire.begin();
  Wire.beginTransmission(mpu);
  Wire.write(0x6B);
  Wire.endTransmission(true);

  // LCD screen setup
  lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):
  pinMode(2, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Carousel ready");
  lcd.setCursor(0, 1);
  
  // LED setup

  // Interrupt setup
  // TO DO: correctly setup interrupt
//  attachInterrupt(digitalPinToInterrupt(interruptPin), lcd_change_ISR, CHANGE); 
}

void loop() {
  // Detect and display if button is pressed
  // TO DO: figure what each mode means and name them correctly
  x = analogRead(0);
  Serial.println(x);
//  if (x = 1023) {
//    mode = 0;
//    output = "Carousel ready";
//  }
  if (x < 100) {
    // 'right' button
    output = "Mode 1";
    mode = 1;
  } 
  else if (x < 200) {
    // 'up' button
    output = "Mode 2";
    mode = 2;
  } 
  else if (x < 400) {
    // 'down' button
    output = "Mode 3"; 
    mode = 3;
  } 
  else if (x < 600) {
    // 'left' button
    output = "Mode 4";
    mode = 4;
  } 
  else if (x < 800) {
    // 'select' button
    output = "Select a mode";
  }
  else if (x < 1000) {
    // 'reset' button
    output = "Select a mode";
  }

  // writing information to lcd screen
  lcd.setCursor(0, 0);
  lcd.print(output);
  lcd.setCursor(0, 1);

  Serial.println(mode);

  // alter stepper functioning based on what mode is pressed
  // TO DO: decide what each mode will do (currently holds test stuff)
  // TO DO: fix what the display is saying
  if (mode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Mode 1 running");
    lcd.setCursor(0, 1);
    
    motor->setSpeed(2); // 2 rpm
    motor->step(500, FORWARD,SINGLE);
  }
  else if (mode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Mode 2 running");
    lcd.setCursor(0, 1);
    
    motor->setSpeed(5); // 5 rpm
    motor->step(500, FORWARD,SINGLE);]
  }
  else if (mode == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Mode 3 running");
    lcd.setCursor(0, 1);
    
    motor->setSpeed(10); // 10 rpm
    motor->step(500, FORWARD,SINGLE);
  }
  else if (mode == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Mode 4 running");
    lcd.setCursor(0, 1);
    
    motor->setSpeed(20); // 20 rpm
    motor->step(500, FORWARD,SINGLE);
  }

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

// TO DO: correctly write interrupt code
//void lcd_change_ISR()
//{
//  // sets lcdState as high when a button is changed
//  lcdState = !lcdState;
//}
