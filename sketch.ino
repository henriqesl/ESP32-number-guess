#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// COMPONENTS AND THEIR PINS
#define UP 5
#define DOWN 19
#define CONFIRM 18
#define HINT 17
#define LED_WIN 2
#define LED_LOSE 23
#define BUZZER 16

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define OLED_RESET -1

// DEBOUNCE CONTROL FOR BUTTONS
unsigned long lastPressUP = 0;
unsigned long lastPressDOWN = 0;
unsigned long lastPressHINT = 0;
unsigned long lastPressCONFIRM = 0;
const unsigned long debounceTime = 100;
bool buttonStateUP = HIGH;
bool buttonStateDOWN = HIGH;
bool buttonStateCONFIRM = HIGH;
bool buttonStateHINT = HIGH;

int i = 0;                   // Number displayed on the OLED screen.
int playerNumber;            // Stores the player's chosen number for comparison.
int correct_answer;          // The number the player needs to guess.
int triesCount = 0;          // Number of attempts made by the player.
int maxTries = 5;            // Maximum allowed attempts.
bool hintUsed = false;       // Tracks whether the hint button has already been used.

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(CONFIRM, INPUT_PULLUP);
  pinMode(HINT, INPUT_PULLUP);
  pinMode(LED_WIN, OUTPUT);
  pinMode(LED_LOSE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  startGame();
  numberDraw();
}

void numberDraw() {
  int pinValue = analogRead(1);
  randomSeed(pinValue);
  correct_answer = random(61);
  Serial.println(correct_answer);
}

void startGame() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Guess the number");
  display.setCursor(0, 10);
  display.print("between 0 and 60");
  display.setCursor(0, 20);
  display.print("GREEN: Increase");
  display.setCursor(0, 30);
  display.print("RED: Decrease");
  display.setCursor(0, 40);
  display.print("You have 5 tries");
  display.setCursor(0, 50);
  display.print("Press green to start.");
  display.display();
  waitToStart();
}

void loop() {
  if (playerNumber != correct_answer) {
    buttons();
    tries(); 

    if (triesCount >= maxTries) {
      gameOver();
    }

    if (triesCount >= 3) {
      hint();
    }
  } else {
    win();
  }
}

void buttons() {
  unsigned long currentMillis = millis();

  buttonStateUP = digitalRead(UP);
  buttonStateDOWN = digitalRead(DOWN);
  buttonStateCONFIRM = digitalRead(CONFIRM);

  if (buttonStateUP == LOW) {
    if ((currentMillis - lastPressUP) > debounceTime) {
      i++;
      lastPressUP = currentMillis;
    }
  }

  if (buttonStateDOWN == LOW) {
    if ((currentMillis - lastPressDOWN) > debounceTime) {
      i--;
      lastPressDOWN = currentMillis;
    }
  } 

  if (i < 0) i = 60;
  if (i > 60) i = 0;

  if (buttonStateCONFIRM == LOW && (currentMillis - lastPressCONFIRM) > debounceTime) {
    lastPressCONFIRM = currentMillis;
    triesCount++;
    playerNumber = i;

    display.fillRect(10, 40, 100, 10, BLACK);
    if (playerNumber < correct_answer) {
      display.setCursor(10, 40);
      display.print("Higher!");
    } else if (playerNumber > correct_answer) {
      display.setCursor(10, 40);
      display.print("Lower!");
    }
    display.display();
  }

  display.setCursor(10, 21);
  display.fillRect(10, 21, 100, 10, BLACK);
  display.print("Number: ");
  display.print(i);
  display.display();
}

void tries() {
  display.setCursor(5, 50);
  display.fillRect(0, 50, 128, 10, BLACK);
  display.print("Tries left: ");
  display.print(maxTries - triesCount);
  display.display();
}

void win() {
  display.fillRect(0, 0, 128, 64, BLACK);
  display.setCursor(5, 20);
  display.println("CONGRATULATIONS");
  display.setCursor(5, 30);
  display.print("The value is: ");
  display.println(correct_answer);
  display.setCursor(5, 50);
  display.print("Press Green to Restart");
  display.display();

  for (int j = 0; j < 5; j++) {
    digitalWrite(LED_WIN, HIGH);
    tone(BUZZER, 1000, 100);
    delay(200);
    digitalWrite(LED_WIN, LOW);
    delay(200);
  }

  noTone(BUZZER);

  waitForRestart();
}

void gameOver() {
  display.fillRect(0, 0, 128, 64, BLACK);
  display.setCursor(20, 10);
  display.println("GAME OVER");
  display.setCursor(20, 20);
  display.print("Answer was: ");
  display.println(correct_answer);
  display.setCursor(5, 40);
  display.print("Press Green to Restart");
  display.display();

  for (int j = 0; j < 5; j++) {
    digitalWrite(LED_LOSE, HIGH);
    tone(BUZZER, 300, 200);
    delay(500);
    digitalWrite(LED_LOSE, LOW);
    delay(500);
  }

  digitalWrite(LED_LOSE, LOW);
  noTone(BUZZER);              

  waitForRestart();
}

void waitForRestart() {
  while (true) {
    if (digitalRead(UP) == LOW) {
      resetGame();
      break;
    }
  }
}

void waitToStart() {
  while (true) {
    if (digitalRead(UP) == LOW) {
      display.clearDisplay();
      display.display();
      buttons();
      break;
    }
  }
}

void resetGame() {
  i = 0;
  playerNumber = 0;
  triesCount = 0;
  hintUsed = false;

  display.clearDisplay();
  startGame();
  numberDraw();
}

void hint() {
  unsigned long currentMillis = millis();
  buttonStateHINT = digitalRead(HINT);

  if (!hintUsed && buttonStateHINT == LOW && (currentMillis - lastPressHINT) > debounceTime) {
    lastPressHINT = currentMillis;
    hintUsed = true;

    display.setCursor(5, 5);
    display.fillRect(0, 0, 128, 10, BLACK);
    display.print("HINT: ");
    if (correct_answer % 2 == 0) {
      display.print("EVEN");
    } else {
      display.print("ODD");
    }
    display.display();
  }
}
