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

int MAX_CAP = 100;
int MIN_CAP = 0;
// INCREMENT & DECREMENT
int INC = 1;

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
    
    // If the BLUE capture is greater than MIN_CAP, decrease it as the RED button was pressed.
    if (blueCapture > MIN_CAP) {
      blueCapture -= INC; 
    }
    
    // If the BLUE capture is MIN_CAP and RED capture is not MAX_CAP yet increase RED capture
    if (blueCapture == MIN_CAP && redCapture < MAX_CAP) {
      redCapture += INC;
    }
  }
  else if (blueButtonValue != 0) {
    // Blue button is being pressed
    
    blueLight();
    sound();
    
    // If the RED capture is greater than MIN_CAP, decrease it as the BLUE button was pressed.
    if (redCapture > MIN_CAP) {
      redCapture -= INC; 
    }
    
    // If the RED capture is MIN_CAP and BLUE capture is not MAX_CAP yet increase BLUE capture
    if (redCapture == MIN_CAP && blueCapture < MAX_CAP) {
      blueCapture += INC; 
    }
  } else if (greenButtonValue) {
    // Green button is being pressed
  	greenLight();
  } else {
    // No buttons are being pressed
  	noLight();
    noSound();
    
    // Decrease the RED capture
    if (redCapture > MIN_CAP && redCapture < MAX_CAP) {
      redCapture -= INC; 
    }
    
    // Decrease the BLUE capture
    if (blueCapture > MIN_CAP && blueCapture < MAX_CAP) {
      blueCapture -= INC; 
    }
  }
  
  // If RED capture is at MAX_CAP increase RED score
  if (redCapture == MAX_CAP) {
    redLight();
    redScore += INC; 
  }
  
  // If BLUE capture is at MAX_CAP increase BLUE score
  if (blueCapture == MAX_CAP) {
    blueLight();
    blueScore += INC; 
  }
  
  // Display the RED score
  lcd.setCursor(0, 0);
  lcd.print("R=");
  lcd.setCursor(2, 0);
  lcd.print(redScore);
  
  // Display the space between the SCORE and CAPTURE
  int rScoreChars = getNumberLength(redScore);
  int rCapChars = getNumberLength(redCapture);
  // Start from 'X=' + the written score
  // End after 16 chars (total) - capture - '%'
  for (int i = 2 + rScoreChars; i < 16 - rCapChars - 1; i++) {
    lcd.print("."); 
  }
  
  // Display the RED capture
  lcd.print(redCapture);
  lcd.print("%");
 
  
  // Display the BLUE score
  lcd.setCursor(0, 1);
  lcd.print("B=");
  lcd.setCursor(2, 1);
  lcd.print(blueScore);
  
  // Display the space between the SCORE and CAPTURE
  int bScoreChars = getNumberLength(blueScore);
  int bCapChars = getNumberLength(blueCapture);
  // Start from 'X=' + the written score
  // End after 16 chars (total) - capture - '%'
  for (int i = 2 + bScoreChars; i < 16 - bCapChars - 1; i++) {
    lcd.print("."); 
  }
  
  // Display the BLUE capture
  lcd.print(blueCapture);
  lcd.print("%");
 
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

int getNumberLength(int x) {
    if(x>=1000000000) return 10;
    if(x>=100000000) return 9;
    if(x>=10000000) return 8;
    if(x>=1000000) return 7;
    if(x>=100000) return 6;
    if(x>=10000) return 5;
    if(x>=1000) return 4;
    if(x>=100) return 3;
    if(x>=10) return 2;
    return 1;
}
