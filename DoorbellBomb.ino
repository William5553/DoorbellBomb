#include <LiquidCrystal_I2C.h>

char[] options = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-";
char[] typedIn = [];
int currentColumn = 0;

int yellowButton = 32;  // goes low when pushed
int redButton = 33;     // goes high when toggled
int upPin = 35;         // goes high when pushed
int downPin = 34;       // goes high when pushed
int leftPin = 25;       // goes to low when pushed
int rightPin = 26;      // goes low when pushed

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
}

void loop() {
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(analogRead(leftPin) < 100 ? "left on" : "left off");
  // set cursor to first column, second row
  lcd.setCursor(0, 1);
  lcd.print(analogRead(rightPin) < 100 ? "right on" : "right off");
  delay(100);
  lcd.clear();
}
