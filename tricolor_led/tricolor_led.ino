const int redPin = 7; // CHANGE TO WHICHEVER PINS AVAILABLE
const int greenPin = 5;
const int bluePin = 6;

unsigned int rgbColor[3]; // Array to store RBG values

void setup() {
  setColor(0,0,0); // LED off to begin with
}

void loop() {
  // Initial loop color is red.
  rgbColor[0] = 255;
  rgbColor[1] = 0;
  rgbColor[2] = 0;  

  // Choose two colors to increase and decrease RGB values.
  for (int dec = 0; dec < 3; dec += 1) {
    int inc = (dec == 2) ? 0 : (dec + 1);

    // Cross-fade two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColor[dec] -= 1;
      rgbColor[inc] += 1;
      
      setColor(rgbColor[0], rgbColor[1], rgbColor[2]);
      delay(1); // Increase value to slow LED change down
    }
  }
}

// Function to write color of each of LEDs
void setColor(unsigned int redVal, unsigned int greenVal, unsigned int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
 }
