//Button changing colors with Arduino 
//Josephine Zenker, December 2019 
//Code adapted from Timchii's 4th of July necklace, PaintYourDragon's Adafruit_NeoPixel buttoncycler other youtube tutorials 
//I would like to implement a random ordering of the colors so it is not repetitive, with the on and off switch always coming before or after a cycle is complete 

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN 3
#define DATA_PIN   5  // Digital IO pin connected to strand
#define NUM_COUNT 50  // Number of lights on strand 

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(NUM_COUNT, DATA_PIN, NEO_GRB + NEO_KHZ800 + NEO_KHZ400);

boolean prevState = HIGH;
int mode = 0;   // Current mode on the switch statement 

void setup() {
  Serial.begin(9600); 
  Serial.print("Waiting for data..."); 
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  boolean currState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  //If button is pressed go to next color in the cycle, start off and go from red, green, etc. 
  if((currState == LOW) && (prevState == HIGH)) {
    delay(currState); //Time it takes to activate new color 
    // Check if button is still low after debounce.
    currState = digitalRead(BUTTON_PIN);
    if(currState == LOW) {      
      if(++mode > 6) mode = 0; // Advance to next mode, advance to start once cycle is complete 
      switch(mode) {           // With button press, start new animation 
        case 0:
          colorWipe(strip.Color(0, 0, 0), 50);    // Black/off    
          break;
        case 1:
          colorWipe(strip.Color(255, 0, 0), 50);  //Turn on red
          Serial.println("red"); 
          break;
        case 2:
          colorWipe(strip.Color(0, 255, 0), 50);  //Turn on green
           Serial.println("green"); 
          break;
        case 3:
          colorWipe(strip.Color(0, 0, 255), 50);  //Turn on blue
           Serial.println("blue"); 
          break;
        case 4:
          colorWipe(strip.Color(253, 253, 200), 50);  //Turn on yellow
           Serial.println("yellow"); 
          break;
        case 5:
          colorWipe(strip.Color(218, 112, 214), 50);  //Turn on purple
           Serial.println("orchid purple"); 
          break;
        
      }
    }
  }

  // Set the last-read button state to the old state.
  prevState = currState;
}

//Function from NeoPixel library by Adafruit 
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each light in the strip 
    strip.setPixelColor(i, color);         //  Set color of light in RAM
    strip.show();                          //  Show lights on the strip 
    delay(wait);                           //  Wait 
  }
}
