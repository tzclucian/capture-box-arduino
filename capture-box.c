#include <LiquidCrystal.h>

// Button pins
int redButton = 4;
int greenButton = 3;
int blueButton = 2;

// RGB LED pins
int redPin = 7;
int greenPin = 5;
int bluePin = 6;

// Speaker pin
int speakerPin = 12;

// Button values (whether or not they are pressed)
int redButtonValue = 0;
int blueButtonValue = 0;
int greenButtonValue = 0;

// Team scores
int redScore = 0;
int blueScore = 0;

// Team captures
int redCapture = 0;
int blueCapture = 0;

String redPrefix = String();
String bluePrefix = String();

String redString = String();
String blueString = String();

// LCD
LiquidCrystal lcd(0, 1, 8, 9, 10, 11);

void setup()
{
  // INPUT from buttons
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(blueButton, INPUT);
  
  // OUTPUT to LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // OUTPUT to Speaker
  pinMode(speakerPin, OUTPUT);
  
  // INIT the LCD
  lcd.begin(16, 2);
}

void loop()
{
  // READ the INPUT from the buttons 
  redButtonValue = digitalRead(redButton);
  blueButtonValue = digitalRead(blueButton);
  greenButtonValue = digitalRead(greenButton);
  
  
  if (redButtonValue != 0) {
    // Red button is being pressed
    
    redLight();
    sound();
    
    if (blueCapture > 0) {
      blueCapture--; 
    }
    
    if (blueCapture == 0 && redCapture < 100) {
      redCapture++;
    }
  }
  else if (blueButtonValue != 0) {
    // Blue button is being pressed
    blueLight();
    sound();
    
    if (redCapture > 0) {
      redCapture--; 
    }
    
    if (redCapture == 0 && blueCapture < 100) {
      blueCapture++; 
    }
  } else if (greenButtonValue) {
    // Green button is being pressed
  	greenLight();
  } else {
    // No buttons are being pressed
  	noLight();
    noSound();
    
    if (redCapture > 0 && redCapture < 100) {
      redCapture--; 
    }
    if (blueCapture > 0 && blueCapture < 100) {
      blueCapture--; 
    }
  }
  
  if (redCapture == 100) {
    redScore++; 
  }
  
  if (blueCapture == 100) {
    blueScore++; 
  }
  
  // Display the SCORE and CAP for RED
  redString = redPrefix + "R=" + redScore + " %=" + redCapture + " ";
  lcd.setCursor(0, 0);
  lcd.print(redString);
  
  // Display the SCORE and CAP for BLUE
  blueString = bluePrefix + "B=" + blueScore + " %=" + blueCapture + " ";
  lcd.setCursor(0,1);
  lcd.print(blueString);
  
  // Delay a bit
  delay(10);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void sound() {
  analogWrite(speakerPin, 255); 
}

void noSound() {
  analogWrite(speakerPin, 0); 
}

void redLight() {
  setColor(255, 0, 0);
}

void blueLight() {
 setColor(0, 0, 255); 
}

void greenLight() {
 setColor(0, 255, 0); 
}

void noLight() {
 setColor(0,0,0); 
}
