#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin Configurations
#define SS_PIN 10
#define RST_PIN 5
#define ENTRANCE_IR 2
#define SLOT1_IR 3
#define SLOT2_IR 4
#define BUZZER 6
#define RELAY1 8
#define RELAY2 7
#define SERVO_PIN 9

// Dual Current Sensor Analog Inputs
#define CURRENT_SENSOR_S1 A0  
#define CURRENT_SENSOR_S2 A1  

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo gateServo;

// Variables for the 1-second interval buzzer alarm (Station Full)
unsigned long previousMillis = 0;
const long interval = 1000; 
bool buzzerState = LOW;

// ACS712 Calibration Settings
const int sensorSensitivity = 185; 
const int vccOnBoard = 5000; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  lcd.init();
  lcd.backlight();
  
  pinMode(ENTRANCE_IR, INPUT);
  pinMode(SLOT1_IR, INPUT);
  pinMode(SLOT2_IR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  
  // Initialize Relays to OFF (Active Low: HIGH = Relays Turned Off)
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  
  gateServo.attach(SERVO_PIN);
  gateServo.write(0); 

  lcd.print("EV STATION READY");
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  delay(1000);
  lcd.clear();
}

void loop() {
  // --- 1. MONITOR SLOTS & POWER RELAYS ---
  bool s1 = digitalRead(SLOT1_IR); 
  bool s2 = digitalRead(SLOT2_IR); 

  if (s1 == LOW) {
    digitalWrite(RELAY1, LOW); 
  } else {
    digitalWrite(RELAY1, HIGH); 
  }

  if (s2 == LOW) {
    digitalWrite(RELAY2, LOW); 
  } else {
    digitalWrite(RELAY2, HIGH); 
  }

  // --- 2. AUTOMATIC ENTRANCE GATE LOGIC (VIA IR SENSOR) ---
  if (digitalRead(ENTRANCE_IR) == LOW) {
    if (s1 == LOW && s2 == LOW) {
      lcd.setCursor(0, 0);
      lcd.print("NO FREE SLOTS   ");
      lcd.setCursor(0, 1);
      lcd.print("STATION FULL    ");
      
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        buzzerState = !buzzerState; 
        digitalWrite(BUZZER, buzzerState);
      }
    } 
    else {
      digitalWrite(BUZZER, LOW); 
      openGateSequence("ENTRY GRANTED ");
      
      while(digitalRead(ENTRANCE_IR) == LOW) {
        delay(100); 
      }
    }
  } 
  // --- 3. EXITING GATE LOGIC (VIA RFID TAG SCAN) ---
  else {
    digitalWrite(BUZZER, LOW); 
    displayChargingStatus(s1, s2); 
    
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      mfrc522.PICC_HaltA(); 
      openGateSequence("EXIT GRANTED  ");
    }
  }
}

void openGateSequence(String systemMessage) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(systemMessage);
  lcd.setCursor(0, 1);
  lcd.print("GATE OPENING    ");
  
  gateServo.write(90);          
  digitalWrite(BUZZER, HIGH);   
  delay(1000);                  
  digitalWrite(BUZZER, LOW);    
  
  delay(4000);         
  
  lcd.setCursor(0, 1);
  lcd.print("GATE CLOSING    ");
  gateServo.write(0);           
  digitalWrite(BUZZER, HIGH);   
  delay(1000);                  
  digitalWrite(BUZZER, LOW);    
  
  lcd.clear();
}

float readSlotCurrent(int pin) {
  unsigned int rawReadValue = 0;
  for (int i = 0; i < 10; i++) { 
    rawReadValue += analogRead(pin);
    delay(5);
  }
  float averageRaw = (float)rawReadValue / 10.0;
  float voltage = (averageRaw / 1023.0) * vccOnBoard; 
  float amps = ((voltage - (vccOnBoard / 2.0)) / sensorSensitivity);
  
  if (abs(amps) < 0.08) amps = 0.0; 
  return abs(amps);
}

void displayChargingStatus(bool s1, bool s2) {
  lcd.setCursor(0, 0);
  if (s1 == LOW) {
    float currentS1 = readSlotCurrent(CURRENT_SENSOR_S1);
    lcd.print("S1: CHG ");
    lcd.print(currentS1, 2);
    lcd.print("A    ");
  } else {
    lcd.print("S1: AVAILABLE   ");
  }
  
  lcd.setCursor(0, 1);
  if (s2 == LOW) {
    float currentS2 = readSlotCurrent(CURRENT_SENSOR_S2);
    lcd.print("S2: CHG ");
    lcd.print(currentS2, 2);
    lcd.print("A    ");
  } else {
    lcd.print("S2: AVAILABLE   ");
  }
}
