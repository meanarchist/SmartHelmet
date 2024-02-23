#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include"gsm.h"
//#include "fingerenroll.h"
#include "fingermatch.h"
/************PIN CONFIGURATION***************/
#define motor_positive 6
#define motor_negative 7
#define buzzer 22


void gsm(String number, String data);
void crash_ISR(void);
String data = "";
int f_id = 0;
bool flag_finger = false;
boolean crash_flag = false;
//extern volatile char key_value;
uint8_t getFingerprintID();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(2), crash_ISR, FALLING);
  if (digitalRead(4) == 0)
    gps();
  Serial.println("WELCOME");
  lcd.clear();
  lcd.print("    WELCOME    ");
  pinMode(motor_positive, OUTPUT);
  pinMode(motor_negative, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //  pinMode(4, INPUT_PULLUP);
  analogWrite(motor_positive, 0);
  digitalWrite(motor_negative, LOW);
  digitalWrite(buzzer, LOW);
  finger_init();

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //  Serial.print(getFingerprintID());
  //  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("place finger");
  do {
    getFingerprintID();
    if (p == FINGERPRINT_NOTFOUND)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("UN AUTHORIZED");
      //      Serial.print("UN AUTHORIZED");
      analogWrite(motor_positive, 0);
      digitalWrite(motor_negative, LOW);
      //    key_value = 'x';
    }
  }

  while (f_id == 0);

  //  Serial.print("vanakam");
  if (f_id == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    //    Serial.print("FINGER MATCHED");
    Serial.print("FINGER MATCHED");
    lcd.print("FINGER MATCHED");
    f_id = 2;
    flag_finger = true;
  }
  //delay(2000);
  //    key_value = 'x';
  while (f_id == 2)
  {
    if (flag_finger == true)
    {
      if (Serial.available() > 0)
      {
        char inchar = Serial.read();
        Serial.println(inchar);

        switch (inchar)
        {
          case'V':
            analogWrite(motor_positive, 0);
            digitalWrite(motor_negative, LOW);
            //digitalWrite(buzzer, HIGH);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("  WEAR HELMET  ");
            //          Serial.println("WEAR HELMET");
            break;

          case'W':
            analogWrite(motor_positive, 100);
            digitalWrite(motor_negative, LOW);
            //digitalWrite(buzzer, HIGH);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    ALCHOHOL    ");
            //          Serial.println("ALCHOHOL CONSUMED");
            gsm("7092964592", "ALCHOHOL CONSUMED");
            break;

          case'X':
            analogWrite(motor_positive, 100);
            digitalWrite(motor_negative, LOW);
            digitalWrite(buzzer, HIGH);
            delay(1000);
            digitalWrite(buzzer, LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("DON'T SPEAK CALL");
            //          Serial.println("DON'T SPEAK CALL");
            break;

          case'Y':
            analogWrite(motor_positive, 100);
            digitalWrite(motor_negative, LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    ALCHOHOL    ");
            lcd.setCursor(0, 1);
            lcd.print("DON'T SPEAK CALL");
            //          Serial.println("ALCHOHOL CONSUMED AND DON'T SPEAK CALL");
            break;

          case'Z':
            analogWrite(motor_positive, 255);
            digitalWrite(motor_negative, LOW);
            lcd.clear();
            lcd.setCursor(1, 1);
            lcd.print("HAPPY JOURNEY");
            //          Serial.println("HAPPY JOURNEY MAKKA");
            break;
        }
      }
      if (crash_flag == true)
      {
        crash_flag = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ACCIDENT");
        Serial.println("ACCIDENT");
        analogWrite(motor_positive, 0);
        digitalWrite(motor_negative, LOW);
        while (1)
        {
          gsm("7092964532", "ACCIDENT");
          delay(2000);
        }
      }
    }
    delay(1000);
  }
}

void crash_ISR(void)
{
  crash_flag = true;
}
