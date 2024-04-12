#include <LiquidCrystal_I2C.h>

// unplug D12 to upload code :(

String options = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-";
String typedIn = "";
int currentColumn = 0;

int yellowButton = 32;  // goes low when pushed
int redButton = 33;     // goes high when toggled
int upPin = 2;          // goes high when pushed
int downPin = 4;        // goes high when pushed
int leftPin = 25;       // goes to low when pushed
int rightPin = 26;      // goes low when pushed

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
  pinMode(yellowButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Password:");
}

void loop() {
  lcd.setCursor(0, 0);

  // up and down cycles through the options, left and right cycles through the typed in characters
  // if (digitalRead(upPin) == HIGH) {
  //   currentColumn = (currentColumn + 1) % options.length();
  //   lcd.setCursor(0, 1);
  //   lcd.print(options.substring(currentColumn, currentColumn + 16));
  //   delay(200);
  // } else if (digitalRead(downPin) == HIGH) {
  //   currentColumn = (currentColumn - 1 + options.length()) % options.length();
  //   lcd.setCursor(0, 1);
  //   lcd.print(options.substring(currentColumn, currentColumn + 16));
  //   delay(200);
  // } else if (digitalRead(leftPin) == LOW) {
  //   typedIn += options[currentColumn];
  //   lcd.setCursor(0, 0);
  //   lcd.print("Password: " + typedIn);
  //   delay(200);
  // } else if (digitalRead(rightPin) == LOW) {
  //   typedIn = typedIn.substring(0, typedIn.length() - 1);
  //   lcd.setCursor(0, 0);
  //   lcd.print("Password: " + typedIn);
  //   delay(200);
  // }

  // show the status of each button
  lcd.print(analogRead(redButton) > 130 ? 1 : 0);
  lcd.print(analogRead(yellowButton) < 250 ? 1 : 0);
  lcd.print(analogRead(leftPin) < 300 ? 1 : 0);
  lcd.print(analogRead(rightPin) < 400 ? 1 : 0);
  lcd.print(analogRead(upPin) > 0 ? 1 : 0);
  lcd.print(analogRead(downPin) < 250 ? 1 : 0);

  lcd.setCursor(0, 1);

  // calibration
  // lcd.print(analogRead(redButton));
  // lcd.print(" ");
  // lcd.print(analogRead(yellowButton));
  // lcd.print(" ");
  // lcd.print(analogRead(upPin));
  // lcd.print("  ");
  // lcd.print(analogRead(downPin));
  // lcd.setCursor(0, 1);
  // lcd.print(analogRead(leftPin));
  // lcd.print("  ");
  // lcd.print(analogRead(rightPin));

  delay(100);
  lcd.clear();
}
