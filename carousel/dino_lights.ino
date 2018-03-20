int ledPin = 2; // Pin LEDS are attached to, has inverter
int ledState = LOW; 
int variablePin = 3; // Pin that controls interval variable
unsigned long previousMillis = 0; // Last time millis is instantiated
volatile long interval; // Variable interval between LED lights blinking   

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(variablePin, INPUT);
  attachInterrupt(digitalPinToInterrupt(variablePin), ISR_speed, CHANGE);
  int variableState = digitalRead(variablePin);
  variableState ? (interval = 50) : (interval = 1000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    (ledState == LOW) ? (ledState = HIGH) : (ledState = LOW);
    digitalWrite(ledPin, ledState);
  }
}

void ISR_speed() {
  int variableState = digitalRead(variablePin);
  variableState ? (interval = 50) : (interval = 1000);
}
