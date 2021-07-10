#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo1;
Servo myservo2;

const int irsensor1 = 2; 
const int irsensor2 = 3;

int valueirsensor1 = 0;
int valueirsensor2 = 0;

int count = 0;
int countmax = 5;

int total;

bool state = false;
bool state2 = false;

void setup() {
  
  pinMode (irsensor1, INPUT);
  pinMode (irsensor2, INPUT);
  myservo1.attach(5);
  myservo2.attach(6);
  myservo1.write(0);
  myservo2.write(0);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,1); //16 row 2 coloum
  lcd.print("AVAILABLE=");
}

void loop() {
  valueirsensor1 = digitalRead(irsensor1);
  valueirsensor2 = digitalRead(irsensor2);

  if (count > countmax){
    count = countmax;
    }

  if (count < 0){
    count = 0;
    }

  if (valueirsensor1 == LOW && state == false){
    count++;

    total = countmax - count;

    if (total >= 1){
      lcd.setCursor(2,0);
      lcd.print("           ");
      lcd.setCursor(4,0);
      lcd.print("WELCOME");
      }
    else {
      lcd.setCursor(4,0);
      lcd.print("       ");
      lcd.setCursor(2,0);
      lcd.print("PLEASE WAIT");
      }

    lcd.setCursor(12,1);
    lcd.print("  ");
    lcd.setCursor(12,1);
    lcd.print(total);
    total = 0;
    state = true;
    }
  else {
    state = false;
    }
  

  if (valueirsensor2 == LOW && state2 == false){
    count--;

    total = countmax - count;

    if (total >= 1){
      lcd.setCursor(2,0);
      lcd.print("           ");
      lcd.setCursor(4,0);
      lcd.print("WELCOME");
      }
    else {
      lcd.setCursor(4,0);
      lcd.print("       ");
      lcd.setCursor(2,0);
      lcd.print("PLEASE WAIT");
      }

    lcd.setCursor(12,1);
    lcd.print("  ");
    lcd.setCursor(12,1);
    lcd.print(total);
    total = 0;
    state2 = true;
    }

  else {
    state2 = false;
    }

  if (count < 5 && state == true){
    myservo1.write(90);
    delay (4000); //DELAY BUKAK PINTU masuk
    myservo1.write(0);   
    }

  if (state2 == true){
    myservo2.write(90);
    delay (4000); //DELAY BUKAK PINTU keluar
    myservo2.write(0);   
    }

}
