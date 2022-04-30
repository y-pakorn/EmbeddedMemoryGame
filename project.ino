#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <Keypad.h>
#include <MFRC522.h>
#define RST_PIN 5
#define SS_PIN 53


dht DHT;
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int tact1 = 31;
const int tact2 = 32;
const int tact3 = 33;
const int led1 = 41;
const int led2 = 42;
const int led3 = 43;
const int DHTPIN = 22;
const int buz = 10;

const int tact[3] = {31, 32, 33};
const int led[3] = {41, 42, 43};

const byte ROWS = 2; //four rows
const byte COLS = 2; //three columns
char keys[ROWS][COLS] = {
  {'1', '2'},
  {'5', '6'},
};
byte rowPins[ROWS] = {47, 46};
byte colPins[COLS] = {44, 45};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int currentMode = 0;
int highscore = 0;
int user = 0;

const int rSize = 6;
int randLed[rSize];
int selectedLed[rSize];

void genRandom() {
  for (int i = 0; i < rSize; i++) {
    randLed[i] =  random() % 3;
  }
}


void setup() {
  Serial.begin(9600);
  lcd.begin();
  DHT.read11(DHTPIN);
  mfrc522.PCD_Init();

  pinMode(tact1, INPUT);
  pinMode(tact2, INPUT);
  pinMode(tact3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buz, OUTPUT);

  genRandom();
}

void loop() {
  if (currentMode > 100 && currentMode < 200) {
    int currentIndex = currentMode - 101;
    if (currentIndex == rSize) {
      currentMode = 1000;
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Press switch for");
      lcd.setCursor(0, 1);
      lcd.print("#");
      lcd.print(currentIndex + 1);

      for (int i = 0; i < 3; i++) {
        if (digitalRead(tact[i])) {
          selectedLed[currentIndex] = i;
          currentMode += 1;
          delay(200);
        }
      }
    }
  } else if (currentMode == 1000) {
    int score = 0;
    for (int i = 0; i < rSize; i++) {
      if (randLed[i] == selectedLed[i]) {
        score += 1;
      }
    }
    
    tone(buz, 5000);
    delay(500);
    noTone(buz);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Completed!");
    lcd.setCursor(0, 1);
    lcd.print("Score:");
    lcd.print(score);
    delay(1000);

    lcd.clear();
    highscore = max(highscore, score);
    currentMode = 0;
  } else {
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(int(DHT.temperature));

    lcd.print(" Hum: ");
    lcd.print(int(DHT.humidity));

    delay(1000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("High score: ");
    lcd.print(highscore);

    lcd.setCursor(0, 1);
    lcd.print("User: ");
    lcd.print(user);


    genRandom();
    DHT.read11(DHTPIN);
  }

  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (currentMode == 0 && key == '1') {
      currentMode = 1;
      lcd.clear();
      lcd.print("Alzheimer recovery!");
      delay(1000);
      lcd.clear();
      lcd.print("Watch the led!");
      delay(1000);
      tone(buz, 5000);
      delay(500);
      noTone(buz);

      for (int i = 0; i < rSize; i++) {
        int selectedPin = led[randLed[i]];
        digitalWrite(selectedPin, HIGH);
        delay(500);
        digitalWrite(selectedPin, LOW);
        delay(500);
      }

      currentMode = 101;
      lcd.clear();
    } else {
      currentMode = 0;
    }
  }

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())) {
    user = int(*mfrc522.uid.uidByte);
    highscore = 0;
    currentMode = 0;
  }

  

  delay(200);
    

}
