#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <LiquidCrystal.h>

// Power button instantiations
int power_out = 11;
int power_button = 2; 
volatile int power = LOW; // for power button interrupt

// LED instantiations
int pole_leds = 12;
int blue_leds = 3;
int green_leds = 13;
//int blue_leds_state = LOW;
//int green_leds_state = LOW;
int top_leds_state = LOW;
unsigned long previousMillis = 0; // Last time millis is instantiated

// Stepper motor instantiations
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor*motor = AFMS.getStepper(200,2);
int motor_dir = 1; // initial direction of motor is forwards

// LCD screen instantiations
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int x; //variable to store voltage value when a key is pressed
String output = "";
int mode, mode_on = LOW; // the carousel mode; defines how it is moving

void setup() {
  Serial.begin(9600);

  // LCD screen setup
  lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):

  // Power button set up (and interrupt)
  pinMode(power_button, INPUT);
  pinMode(power_out, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(power_button), power_check_ISR, RISING);

  // LED setup
  pinMode(pole_leds, OUTPUT);
  pinMode(blue_leds, OUTPUT);
  pinMode(green_leds, OUTPUT);

  // Motor setup
  AFMS.begin(); //creating w default freq 1.6kHz
  TWBR = ((F_CPU /400000l) - 16) / 2; 
  motor->setSpeed(1);
}
  
void loop() {
  Serial.println(power);
  // check if system power is on for functioning
  if (power) {
    // Detect and display if button is pressed
    x = analogRead(0);
    output = "Carousel Ready  ";
    
    if (x < 100) {
      // 'right' button
      output = "Childs Play     ";
      mode = 1;
      mode_on = HIGH;
    } 
    else if (x < 200) {
      // 'up' button
      output = "Just Chillin'  ";
      mode = 2;
      mode_on = HIGH;
    } 
    else if (x < 400) {
      // 'down' button
      output = "Rager           "; 
      mode = 3;
      mode_on = HIGH;
    } 
    else if (x < 600) {
      // 'left' button
      output = "VomCom          ";
      mode = 4;
      mode_on = HIGH;
    } 
  
    // writing information to lcd screen
    lcd.setCursor(0, 0);
    lcd.print(output + "  ");
    lcd.setCursor(0, 1);
    
    Serial.println(mode);
    Serial.println();
    digitalWrite(power_out, power);
    digitalWrite(pole_leds, mode_on);
     
    motor_dir = !motor_dir; // to avoid rotating too far in one direction 
    // alter stepper functioning based on what mode is pressed
    if (mode == 1) {
      motor->setSpeed(0.5);
      digitalWrite(blue_leds, HIGH);
      digitalWrite(green_leds, HIGH);
      motor->step(300, motor_dir, SINGLE);
    }
    else if (mode == 2) {  
      motor->setSpeed(0.75);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);
      
      motor->step(100, BACKWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);   
       
      motor->step(100, FORWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);
       
      motor->step(100, BACKWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
    }
    else if (mode == 3) {  
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
      
      motor->step(50, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);   
       
      motor->step(50, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
       
      motor->step(50, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);

      motor->step(50, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);

      motor->step(50, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);
    }
    else if (mode == 4) {
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
      
      motor->step(25, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);   
       
      motor->step(25, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
       
      motor->step(25, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);

      motor->step(25, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);

      motor->step(25, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);   
       
      motor->step(25, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state);
       
      motor->step(25, BACKWARD, SINGLE);
      digitalWrite(blue_leds, top_leds_state);
      digitalWrite(green_leds, !top_leds_state);

      motor->step(25, FORWARD, SINGLE);
      digitalWrite(blue_leds, !top_leds_state);
      digitalWrite(green_leds, top_leds_state); 
    }
  
    // changing the mode back to 0 to stop from running the case
    mode = 0;
    mode_on = LOW;
    digitalWrite(green_leds, LOW);
    digitalWrite(blue_leds, LOW);
  }

  else {
    lcd.setCursor(0,0);
    lcd.print("Turn Power On   ");
  }
}

void power_check_ISR() {
  power = !power;
}
