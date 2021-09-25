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
int countmax = 4;

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
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(2,1); //16 row 2 coloum
  lcd.print("AVAILABLE=");
  Serial.begin(9600);
}

void loop() {
  valueirsensor1 = digitalRead(irsensor1);
  valueirsensor2 = digitalRead(irsensor2);
  
  //Serial.print(valueirsensor1);
  //Serial.print("   ");
  //Serial.print(valueirsensor2);
  //Serial.print("   ");
  //Serial.print(state);
  //Serial.print("   ");
  //Serial.println(state2);
  //delay(1000);

  if (valueirsensor1 == LOW && state == false){
    count++;

    if (count >= 5){
    count = 5;
    }

    if (count <= 0){
    count = 0;
    }

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

    if (count >= 5){
    state = false;
    count = 5;
    }

    if (count <= 0){
    count = 0;
    }
    }
  if (valueirsensor1 == HIGH && state == true) {
    state = false;
    }
  

  if (valueirsensor2 == LOW && state2 == false){
    count--;

    if (count >= 5){
    count = 5;
    }

    if (count <= 0){
    count = 0;
    }

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

    if (count >= 5){
    state = false;
    count = 5;
    }

    if (count <= 0){
    count = 0;
    }
    }

  if (valueirsensor2 == HIGH && state2 == true) {
    state2 = false;
    }

  if (count <= 5 && state == true){
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
