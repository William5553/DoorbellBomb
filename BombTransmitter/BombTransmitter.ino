#include <LiquidCrystal_I2C.h>

// unplug D12 to upload code :(

String options = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-";
String typedIn = "";
int currentColumn = 0;

int redButton = 33;     // goes high when toggled
int yellowButton = 32;  // goes low when pushed
int upPin = 4;          // goes high when pushed
int downPin = 2;        // goes high when pushed
int leftPin = 25;       // goes to low when pushed
int rightPin = 26;      // goes low when pushed

int buttons[] = {redButton, yellowButton, upPin, downPin, leftPin, rightPin};

// int buttonState[NUMBUTTONS];
// int lastButtonState[NUMBUTTONS];
// boolean buttonIsPressed[NUMBUTTONS];

LiquidCrystal_I2C lcd(0x27, 16, 2);

// bool buttonPressed(int button) {
//   switch (button) {
//     case yellowButton:
//       return analogRead(yellowButton) < 250;
//       break;

//     case redButton:
//       return analogRead(redButton) > 130;
//       break;

//     case upPin:
//       return analogRead(upPin) > 0;
//       break;

//     case downPin:
//       return analogRead(downPin) < 250;
//       break;

//     case leftPin:
//       return analogRead(leftPin) < 300;
//       break;

//     case rightPin:
//       return analogRead(rightPin) < 400;
//       break;
//   }
// }

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
  // for (int currentButton = 0; currentButton < sizeof(buttons); currentButton++) {
  //   if (buttonPressed(buttons[currentButton])) {
  //     Serial.print("button ");
  //     Serial.println(buttons[currentButton]);
      // if (buttons[currentButton] == 3) {  // -------- Button 3 controls action A
      //   // do action A stuff here
      // } else if (buttons[currentButton] == 4) {  // -------- Button 4 controls action B
      //   // do action B stuff here
      // } else if (buttons[currentButton] == 5) {  // -------- Button 5 controls action C
      //   // do action C stuff here
      // }
      // buttonIsPressed[currentButton] = false;  //reset the button
  //   }
  // }

  lcd.setCursor(0, 0);

  // show the status of each button
  // lcd.print(analogRead(redButton) > 130 ? 1 : 0);
  // lcd.print(analogRead(yellowButton) < 250 ? 1 : 0);
  // lcd.print(analogRead(leftPin) < 300 ? 1 : 0);
  // lcd.print(analogRead(rightPin) < 400 ? 1 : 0);
  lcd.print(analogRead(upPin) > 0 ? 1 : 0);
  lcd.print(" ");
  lcd.print(analogRead(downPin) < 250 ? 1 : 0);

  lcd.setCursor(0, 1);

  // calibration
  // lcd.print(analogRead(redButton));
  // lcd.print(" ");
  // lcd.print(analogRead(yellowButton));
  // lcd.print(" ");
  lcd.print(analogRead(upPin));
  lcd.print("  ");
  lcd.print(analogRead(downPin));
  // lcd.setCursor(0, 1);
  // lcd.print(analogRead(leftPin));
  // lcd.print("  ");
  // lcd.print(analogRead(rightPin));

  if (analogRead(upPin)) {
  }

  delay(100);
  lcd.clear();
}