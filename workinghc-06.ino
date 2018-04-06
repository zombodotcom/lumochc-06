//original neopixels version https://create.arduino.cc/projecthub/3Derp/programmable-stranger-things-light-wall-costume-eaa668
// original code by Michael Barretta
//Edited for FastLED, Optimized and Added Numbers.
//Created by Zombodotcom

#include <FastLED.h>
#define DATA_PIN 3
#define COLOR_ORDER GRB
int mode = 0;
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#include <SoftwareSerial.h>


#define NUM_LEDS    300
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#include "patterns.h"
String message = " ";    // Initialize default string for incoming text
String readString;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); //setting up the FastLED
  FastLED.clear();
  FastLED.show();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// Main program body, loop checks for new serial input and runs functions based on character input or default print function
void loop() {
  //   Set string to incoming text
  //expect a string like wer,qwe rty,123 456,hyre kjhg,
  //or like hello world,who are you?,bye!,
  while (Serial.available()) {
    delay(10);  //small delay to allow input buffer to fill

    char c = Serial.read();  //gets one byte from serial buffer
    if (c == ',') {
      break;
    }  //breaks out of capture loop to print readstring
    readString += c;
  } //makes the string readString

  if (readString.length() > 0) {
    Serial.println(readString); //prints string to serial port out
    
    if (readString == "off") { // Clear string using '*' input
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      readString = " off";
      mode = 0;
      message = " ";
      // erase the string so it doesnt print anything
      //set all the leds off
    }
    if (readString == "pride") { // Clear string using '*' input
 
      Serial.print("pride");
      Serial.print("we have touchdown");
           mode = 1;
    }
    else {
      mode = 0;
      message = " ";
    }
  


switch (mode) {
    case 1:  //run when var = 1
      pride();
      FastLED.show();
      Serial.print("\n Playing Pride");
      break;
      
    case 2:  //run when var = 2
      break;

    case 0:
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      break;


    default:
      // if nothing else matches, do the default
      // default is optional
    break;

  }

 readString = ""; //clears variable for new input
}





}

