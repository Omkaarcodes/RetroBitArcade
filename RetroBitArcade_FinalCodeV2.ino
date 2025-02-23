#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust this line according to your new library's constructor

// Player 1 Joystick
const int SW_pin1 = 8;
const int X_pin1 = 2;
const int Y_pin1 = 3;

// Player 2 Joystick
const int SW_pin2 = 9;
const int X_pin2 = 1;
const int Y_pin2 = 0;

int RED_LED = 3;
int BLUE_LED = 4;
int YELLOW_LED = 7;
int GREEN_LED = 5;

// Array for LED pins
int ledPins[] = {RED_LED, BLUE_LED, YELLOW_LED, GREEN_LED};
const char* colors[] = {"RED", "BLUE", "YELLOW", "GREEN"};

int sequence[6]; // Store a sequence of 6 LEDs
int playerSequence[6]; // Store the player's input sequence
int sequenceLength = 6; // Length of the sequence for the game
int currentRound = 0; // Current round of the game

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(SW_pin1, INPUT_PULLUP);
  pinMode(SW_pin2, INPUT_PULLUP);
 
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
 
  randomSeed(analogRead(4)); // Use a different analog pin for randomSeed
}

void loop() {
  showMenu();
  int gameChoice = getMenuChoice();
 
  if (gameChoice == 1) {
    playMemoryGame();
  } else if (gameChoice == 2) {
    playReactionGame();
  }
}

void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Game:");
  lcd.setCursor(0, 1);
  lcd.print("1:Memory 2:React");
}

int getMenuChoice() {
  while (true) {
    int x1 = analogRead(X_pin1);
    if (x1 < 100) return 1; // Left for Memory Game
    if (x1 > 900) return 2; // Right for Reaction Game
    delay(50); // Small delay to prevent rapid readings
  }
}

void playMemoryGame() {
  currentRound = 0;
  generateSequence();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MEMORY GAME");
  lcd.setCursor(0, 1);
  lcd.print("Get ready!");

  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(500);
    digitalWrite(ledPins[i], LOW);
    delay(250);
  }
 
  delay(2000);
  lcd.clear();

  while (currentRound < sequenceLength) {
    displaySequence();
    getPlayerInput();
    if (!checkSequence()) {
      gameOver();
      return; // Return to main menu
    }
    currentRound++;
  }

  gameWon();
  delay(3000); // Show win message for 3 seconds before returning to main menu
}

void playReactionGame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Game");
  lcd.setCursor(0, 1);
  lcd.print("5 Rounds");
  delay(2000);

  int player1Score = 0;
  int player2Score = 0;

  for (int round = 1; round <= 5; round++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Round " + String(round));
    lcd.setCursor(0, 1);
    lcd.print("Get ready!");
    delay(2000);
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wait for light...");
   
    delay(random(2000, 5000)); // Random wait time
   
    int targetLED = random(0, 4);
    digitalWrite(ledPins[targetLED], HIGH);
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GO!");
   
    unsigned long startTime = millis();
    int winner = 0;
   
    while (winner == 0) {
      if (digitalRead(SW_pin1) == LOW) {
        winner = 1;
      } else if (digitalRead(SW_pin2) == LOW) {
        winner = 2;
      }
    }
   
    unsigned long reactionTime = millis() - startTime;
   
    digitalWrite(ledPins[targetLED], LOW);
   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player " + String(winner) + " wins!");
    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(reactionTime) + "ms");

    if (winner == 1) player1Score++;
    else player2Score++;
   
    delay(2000);
  }

  // Display final scores
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Final Scores:");
  lcd.setCursor(0, 1);
  lcd.print("P1:" + String(player1Score) + " P2:" + String(player2Score));
  delay(3000);

  // Determine overall winner
  lcd.clear();
  lcd.setCursor(0, 0);
  if (player1Score > player2Score) {
    lcd.print("Player 1 Wins!");
  } else if (player2Score > player1Score) {
    lcd.print("Player 2 Wins!");
  } else {
    lcd.print("It's a Tie!");
  }
  delay(3000); // Show result for 3 seconds before returning to main menu
}

void generateSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(0, 4);
  }
}

void displaySequence() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Watch the LEDs");
  delay(1000);
 
  for (int i = 0; i <= currentRound; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(250);
  }
}

int readJoystick() {
  int x = analogRead(X_pin1);
  int y = analogRead(Y_pin1);
 
  if (x < 100) return 1; // BLUE (left)
  if (x > 900) return 0; // RED (right)
  if (y < 100) return 2; // YELLOW (top)
  if (y > 900) return 3; // GREEN (bottom)
 
  return -1; // No direction selected
}

void getPlayerInput() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Repeat sequence");
  lcd.setCursor(0, 1);
  lcd.print("Use joystick");
 
  for (int i = 0; i <= currentRound; i++) {
    bool inputReceived = false;
    while (!inputReceived) {
      int joystickInput = readJoystick();
      if (joystickInput != -1) {
        playerSequence[i] = joystickInput;
        inputReceived = true;
        digitalWrite(ledPins[joystickInput], HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(colors[joystickInput]);
        delay(300);
        digitalWrite(ledPins[joystickInput], LOW);
        delay(200);
      }
    }
  }
}

bool checkSequence() {
  for (int i = 0; i <= currentRound; i++) {
    if (playerSequence[i] != sequence[i]) {
      return false;
    }
  }
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Correct!");
  lcd.setCursor(0, 1);
  lcd.print("Next round...");
  delay(1000);
  return true;
}

void gameWon() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congratulations!");
  lcd.setCursor(0, 1);
  lcd.print("You won!");
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Try again");
  delay(2000);
}
