# Custom Video Game Controller with Arduino and 3D-Designed Parts

## Overview
This project is a custom-built video game controller featuring 3D-designed parts and Arduino-compatible components. The controller supports two players and includes joystick controls, push buttons, LEDs, and an LCD display. The controller is designed to support multiple games, with the **Memory Game** and **Reaction Game** currently implemented and functional.

## Components Used
- **Arduino Board** (Compatible with ATmega328-based models)
- **Joysticks** (Two analog joysticks with push buttons)
- **LEDs** (Four colored LEDs: Red, Blue, Yellow, Green)
- **LiquidCrystal I2C Display** (16x2 LCD for game instructions and feedback)
- **3D-Designed Enclosure** (Custom-designed to house all components securely)
- **Resistors and Wiring** (For proper electrical connections and stability)

## Features
- **Two-Player Support**
- **LCD Menu Navigation**
- **Memory Game** (Simon Says-like pattern repetition challenge)
- **Reaction Game** (Fastest player to press wins the round)

## Functional Games
### Memory Game
The player must repeat a randomly generated LED sequence of length 6 using the joystick controls. The game increases in difficulty with each correct round. If the player makes a mistake, the game ends.

#### Gameplay
1. A sequence of LED flashes is displayed.
2. The player repeats the sequence using joystick movements.
3. If the sequence is correct, the next round starts with an additional step.
4. The game ends when the player completes all rounds or makes an incorrect input.

### Reaction Game
Two players compete to press their button first when an LED lights up. The reaction time is recorded, and after five rounds, the player with the most wins is declared the champion.

#### Gameplay
1. The game randomly chooses a delay before lighting an LED.
2. Players must press their buttons as fast as possible.
3. The player who reacts first wins the round.
4. The process repeats for five rounds, and the overall winner is announced.

## Planned Enhancements
- **Additional Games** (Expanding the game library with new challenges)
- **Refined Controller Ergonomics** (Further optimizing the 3D-printed design for comfort and usability)
- **Improved User Interface** (Adding more interactive elements and animations on the LCD screen)

## Code Repository
The Arduino code for this project is available and currently supports the Memory and Reaction games. Future iterations will enhance functionality and improve user experience.


