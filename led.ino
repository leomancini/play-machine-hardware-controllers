#include <SoftPWM.h>

// RGB LED Control using SoftPWM
const int RED_PIN = 7;
const int GREEN_PIN = 8;
const int BLUE_PIN = 9;

void setup() {
  Serial.begin(9600);
  
  // Initialize SoftPWM
  SoftPWMBegin();
  
  // Set up pins
  SoftPWMSet(RED_PIN, 0);
  SoftPWMSet(GREEN_PIN, 0);
  SoftPWMSet(BLUE_PIN, 0);
  
  // Set fade rate (optional)
  SoftPWMSetFadeTime(RED_PIN, 0, 0);
  SoftPWMSetFadeTime(GREEN_PIN, 0, 0);
  SoftPWMSetFadeTime(BLUE_PIN, 0, 0);
  
  Serial.println("RGB LED Control with SoftPWM");
  Serial.println("Enter a command:");
  Serial.println("  R,G,B - Set color (0-255 for each)");
  Serial.println("  R,G,B,brt - Set color with brightness (1-10)");
  Serial.println("  r - Red only");
  Serial.println("  g - Green only");
  Serial.println("  b - Blue only");
  Serial.println("  w - White");
  Serial.println("  0 - Off");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "IDENT") {
      Serial.println("LED");
    }
    else {
      // Process comma-separated values
      processColorValues(input);
    }
  }
}

void processColorValues(String input) {
  int firstComma = input.indexOf(',');
  int secondComma = input.indexOf(',', firstComma + 1);
  int thirdComma = input.indexOf(',', secondComma + 1);
  
  // Extract values
  int r = input.substring(0, firstComma).toInt();
  int g = input.substring(firstComma + 1, secondComma).toInt();
  int b = input.substring(secondComma + 1, thirdComma).toInt();
  int brightness = input.substring(thirdComma + 1).toInt();
  
  // Constrain values
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);
  brightness = constrain(brightness, 1, 10);
  
  // Apply brightness
  float brightnessFactor = brightness / 10.0;
  r = r * brightnessFactor;
  g = g * brightnessFactor;
  b = b * brightnessFactor;
  
  // Set color
  setColor(r, g, b);
  
  // Confirm
  Serial.print("Color with brightness: R=");
  Serial.print(r);
  Serial.print(", G=");
  Serial.print(g);
  Serial.print(", B=");
  Serial.print(b);
  Serial.print(" (Brightness level: ");
  Serial.print(brightness);
  Serial.println("/10)");
}

void setColor(int red, int green, int blue) {
  // Set colors using SoftPWM
  SoftPWMSet(RED_PIN, red);
  SoftPWMSet(GREEN_PIN, green);
  SoftPWMSet(BLUE_PIN, blue);
}