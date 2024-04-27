#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

const int password = "1234321234";
const unsigned long debounceDelay = 80;  // how long in ms a pin should be pressed to count

const String receiverAddress = "http://123.123.123.123";
const char* ssid = "HWDSB-GUEST";
const char* pass = "Education";

// unplug D12 to upload code :(

// String options = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-";
String typedIn = "";
int currentColumn = 0;

const int redButton = 33;
const int yellowButton = 32;
const int upPin = 2;
const int downPin = 4;
const int leftPin = 25;
const int rightPin = 26;

const int buttons[] = { redButton, yellowButton, upPin, downPin, leftPin, rightPin };
const int btnType[] = { 1, 0, 0, 0, 1, 1 };  // 1 goes high when pushed, 0 goes low when pushed
const int btnThresholds[] = { 1, 1, 15, 15, 0, 0 };

int buttonState[] = { 0, 0, 0, 0, 0, 0 };
int lastButtonState[] = { 0, 0, 0, 0, 0, 0 };
int lastDebounceTime[] = { 0, 0, 0, 0, 0, 0 };
bool buttonIsPressed[] = { false, false, false, false, false, false };

LiquidCrystal_I2C lcd(0x27, 16, 2);

void pressedAction(int button) {
  switch (button) {
    case yellowButton:
      // check
      if (typedIn == password) {
        // send a request to receiver
        if (WiFi.status() == WL_CONNECTED) {
          HTTPClient http;
          String serverPath = receiverAddress + "/on";

          // Your Domain name with URL path or IP address with path
          http.begin(serverPath.c_str());

          // Send HTTP GET request
          int httpResponseCode = http.GET();

          if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
          } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
          }
          // Free resources
          http.end();
        } else {
          Serial.println("Failed to send signal: WiFi Disconnected");
        }
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect");
        lcd.setCursor(0, 1);
        lcd.print("Password!");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Password:");
        lcd.setCursor(0, 1);
      }
      break;

    case redButton:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Password:");
      lcd.setCursor(0, 1);
      break;

    case upPin:
      typedIn.append("1");
      break;

    case downPin:
      typedIn.append("2");
      break;

    case leftPin:
      typedIn.append("3");
      break;

    case rightPin:
      typedIn.append("4");
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(yellowButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Password:");

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  for (int currentButton = 0; currentButton < 6; currentButton++) {
    buttonState[currentButton] = btnType[currentButton] == 0
                                   ? (analogRead(buttons[currentButton]) < btnThresholds[currentButton])
                                   : (analogRead(buttons[currentButton]) > btnThresholds[currentButton]);

    if (buttonState[currentButton] != lastButtonState[currentButton]) {
      lastDebounceTime[currentButton] = millis();
    }
    
    if ((millis() - lastDebounceTime[currentButton]) > debounceDelay && buttonState[currentButton] != buttonIsPressed[currentButton]) {
      buttonIsPressed[currentButton] = buttonState[currentButton];

      if (buttonIsPressed[currentButton]) {
        Serial.print("button ");
        Serial.println(buttons[currentButton]);
        pressedAction(buttons[currentButton]);
      }
    }
  }

  Serial.print("Red | Activated: ");
  Serial.print(buttonIsPressed[0] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(redButton));
  Serial.print("Yellow | Activated: ");
  Serial.print(buttonIsPressed[1] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(yellowButton));
  Serial.print("Up | Activated: ");
  Serial.print(buttonIsPressed[2] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(upPin));
  Serial.print("Down | Activated: ");
  Serial.print(buttonIsPressed[3] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(downPin));
  Serial.print("Left | Activated: ");
  Serial.print(buttonIsPressed[4] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(leftPin));
  Serial.print("Right | Activated: ");
  Serial.print(buttonIsPressed[5] ? "🗸" : "✗");
  Serial.print(" | Value: ");
  Serial.print(analogRead(rightPin));
  Serial.println("");
}
