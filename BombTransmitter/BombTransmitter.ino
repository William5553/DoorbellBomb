#include <LiquidCrystal_I2C.h>

// unplug D12 to upload code :(

String options = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-";
String typedIn = "";
int currentColumn = 0;

const int redButton = 33;     // goes high when toggled
const int yellowButton = 32;  // goes low when pushed
const int upPin = 2;          // goes high when pushed
const int downPin = 4;        // goes high when pushed
const int leftPin = 25;       // goes to low when pushed
const int rightPin = 26;      // goes low when pushed

int buttons[] = { redButton, yellowButton, upPin, downPin, leftPin, rightPin };

// int buttonState[] = { 0, 0, 0, 0, 0, 0 };
// int lastButtonState[] = { 0, 0, 0, 0, 0, 0 };
// bool buttonIsPressed[] = { false, false, false, false, false, false };

LiquidCrystal_I2C lcd(0x27, 16, 2);

// bool buttonPressed(int button) {
//   switch (button) {
//     case yellowButton:
//       return analogRead(yellowButton) < 100;
//       break;

//     case redButton:
//       return analogRead(redButton) > 1;
//       break;

//     case upPin:
//       return analogRead(upPin) > 0;
//       break;

//     case downPin:
//       return analogRead(downPin) > 0;
//       break;

//     case leftPin:
//       return analogRead(leftPin) < 100;
//       break;

//     case rightPin:
//       return analogRead(rightPin) < 50;
//       break;

//     default:
//       return false;
//       break;
//   }
// }

void setup() {
  Serial.begin(9600);
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
  // for (int currentButton = 0; currentButton < 6; currentButton++) {
  //   buttonIsPressed[currentButton] = false;  //reset the button
  //   if (buttonPressed(buttons[currentButton])) {
  //     Serial.print("button ");
  //     Serial.println(buttons[currentButton]);
  //     buttonIsPressed[currentButton] = true;  //reset the button
  //   }
  // }

  lcd.setCursor(0, 0);

  // show the status of each button
  lcd.print(analogRead(redButton) > 1 ? 1 : 0);
  lcd.print(analogRead(yellowButton) < 1 ? 1 : 0);
  lcd.print(analogRead(leftPin) < 15 ? 1 : 0);
  lcd.print(analogRead(rightPin) < 15 ? 1 : 0);
  lcd.print(analogRead(upPin) > 0 ? 1 : 0);
  lcd.print(analogRead(downPin) > 0 ? 1 : 0);

  lcd.setCursor(0, 1);

  // calibration
  lcd.print(analogRead(redButton));
  lcd.print(" ");
  lcd.print(analogRead(yellowButton));
  lcd.print(" ");
  lcd.print(analogRead(upPin));
  lcd.print(" ");
  lcd.print(analogRead(downPin));
  lcd.print(" ");
  lcd.print(analogRead(leftPin));
  lcd.print(" ");
  lcd.print(analogRead(rightPin));

  delay(100);
  lcd.clear();
}
