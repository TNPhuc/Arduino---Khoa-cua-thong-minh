/* 
* Khóa: Lập trìn Arduino cơ bản
* Project: Khóa điện tử thông minh
* Người thực hiện: Trần Nguyễn Phúc, Võ Thị Hồng Ánh, Nguyễn Hoàng Thiên
*
*/
#include <Keypad.h>
//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int numRows = 4;
const int numCols = 4;

char keymap[numRows][numCols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = { 6, 5, 4, 3};
byte colPins[numCols] = { 10, 9, 8, 7};

Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

const int buzzerPin = 12;
const int relayPin = 11;

LiquidCrystal_I2C lcd(0x27,16,2); 

const char password[4] = {'1', '2', '3'};
char inputPassword[4] = {'0', '0', '0', '\0'};
int incorrectAttempts = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print("Enter password:");
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    lcd.setCursor(strlen(inputPassword), 1);
    lcd.print(key);
    
    if (strlen(inputPassword) < 3) {
      inputPassword[strlen(inputPassword)] = key;
    }
    
    if (strlen(inputPassword) == 3) {
      if (strcmp(inputPassword, password) == 0) {
        unlock();
      } else {
        incorrectAttempts++;
        Serial.println(incorrectAttempts);
        if (incorrectAttempts > 3) {
          lcd.clear();
          lcd.print("Enter password:");
          buzzer();
          memset(inputPassword, '\0', sizeof(inputPassword));
          incorrectAttempts = 0;
        } else {
          lock();
        }
      }
    }
  }
}

void unlock() {
  digitalWrite(relayPin, HIGH);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Unlocked");
}

void lock() {
  digitalWrite(relayPin, LOW);
  lcd.clear();
  lcd.print("Enter password:");
  memset(inputPassword, '\0', sizeof(inputPassword));
}

void buzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(600);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(600);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);

}
