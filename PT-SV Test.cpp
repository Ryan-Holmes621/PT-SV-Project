/*Author: Ryan Holmes
 * Title: Arduino PT Reader/SV Actuator
 * Date Created: 9/4/22
 * Date Last Modified: 9/24/22
 */
#include <Arduino.h>
#include "Wire.h" //allows communication over i2c devices
#include "LiquidCrystal_I2C.h" //allows interfacing with the LCD screen

const int PressureInput = A0; //This tells the Arduino where the analog input from the PT is coming from
const int PressureZero = 102.4; //This denotes the analog value the PT gives at Zero PSI
const int PressureMax = 921.6; //This denotes the analog value the PT gives at Max PSI
const int PTMaxPSI = 1000; //Max readable value of PT being used
const int baudRate = 9600; //constant integer to set baud rate for serial monitor
const int sensorreaddelay = 250; //Tells LCD how often to update [milliseconds]
int SolenoidPressurizePin = 8; //Designates the pin for the Pressurizing SV
int SolenoidVentPin = 4; //Designates the pin for the Vent SV
float PressureValue = 0; //Variable to gather the input from PT

LiquidCrystal_I2C lcd(0x27, 20, 4); //sets the LCD I2C communication address; format(address, columns, rows)

void setup() {
  Serial.begin(baudRate);
  lcd.init(); //This turns on the LCD screen
  pinMode(SolenoidPressurizePin, OUTPUT);
  pinMode(SolenoidVentPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Actuating Pressurize and Vent SV's
  //delay(5000);
  //digitalWrite(SolenoidPressurizePin, HIGH);
  //delay (5000);
  //digitalWrite(SolenoidPressurizePin, LOW);
  //if (SolenoidPressurizePin = HIGH) 
    //{
    //(SolenoidVentPin = LOW);
    //} else {
    //(SolenoidVentPin = HIGH);
    //}

  
  //Reading data from PT and displaying it on the LCD Screen
  PressureValue = analogRead(A0); //this will read the value from the PT input pin and gives it a variable to call
  PressureValue = ((PressureValue-PressureZero)*PTMaxPSI)/(PressureMax-PressureZero); //This is used to convert Analog PT reading into correct PSI
  Serial.print(PressureValue, 1); //this prints the above line into serial
  Serial.println("psi"); //this prints a label onto the serial
  lcd.setCursor(0,0); //sets cursor to column 0, row 0
  lcd.print("Pressure:"); //prints label
  lcd.print(PressureValue, 1); //prints pressure value to lcd screen, 1 digit on the float
  lcd.print("psi"); //prints label after value
  lcd.print("   "); //to clear the display after large values or negatives
  delay(sensorreaddelay); //delay in milliseconds between read values


}