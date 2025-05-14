#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27, 16, 2);
#define POMPE 8
#define MOISTURE A0
#define WATER_LEVEL A1
#define GREEN 5
#define RED 2
#define YELLOW 4
void setup() {
  pinMode(POMPE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(MOISTURE, INPUT);
  pinMode(WATER_LEVEL, INPUT);
  
  digitalWrite(POMPE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  LCD.init();
  LCD.backlight();
}

// Function to calculate water level percentage
int water_percentage(int L) { 
  return map(L, 100, 600, 0, 100);
}

// Function to calculate soil moisture percentage
int moisture_percentage(int M) {
  return map(M, 1023, 100, 0, 100);
}

// LCD Display Function
void l_c_d_display(int Water_P, int Moisture_P) { 
  if (digitalRead(RED) == LOW) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Water LVL: ");
    LCD.print(Water_P);
    LCD.print("%");

    LCD.setCursor(0, 1);
    LCD.print("Moisture LVL:");
    LCD.print(Moisture_P);
    LCD.print("%");
  } else {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Not enough water");
  }
}

// Check Water Tank Level
void tank(int L) {
  if (L >= 40) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  } else {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }
}
// Check Soil Moisture percentage and Control Pump
void moisture_check(int moisture_P) {
  if (moisture_P >= 30) {
    digitalWrite(YELLOW, LOW);
  
  }
  digitalWrite(YELLOW, HIGH);
  
  if (digitalRead(GREEN) == HIGH) {  // Ensure there is enough water
    digitalWrite(POMPE, HIGH);
    delay(3000);  
    digitalWrite(POMPE, LOW);
    delay(8000);  
  }
}

void loop() {
  int M = analogRead(MOISTURE); // read moisture Sensor values
  int L = analogRead(WATER_LEVEL); // read water level Sensor values

  int Water_P = water_percentage(L); // Converting water level values to percentages
  int Moisture_P = moisture_percentage(M); // Converting moisture values to percentages

  l_c_d_display(Water_P, Moisture_P);
  tank(Water_P); // checks water level in the Tank
  moisture_check(Moisture_P); // checks soil moisture percentage
}


