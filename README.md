Snake Game

This is a simple implementation of the classic Snake Game using C++. The game uses standard C++ data structures (queue, set, and pair) along with custom classes (Food, Snake, and GameBoard) to manage gameplay mechanics.

📝 Overview

The game includes:

Food Class: Handles the spawning of food on the game board.

Snake Class: Manages movement, growth, and self-collision of the snake.

Game Board Class: Oversees game logic, input handling, rendering and score update.

🎮 How to Play

Use the following controls to play:

W → Move Up

S → Move Down

A → Move Left

D → Move Right

X → Exit Game

R → Restart Game

The objective is to eat the food (marked as 'F') in order to score more and avoid collisions with the wall or the snake's own body.

![image alt](https://github.com/Purvi917/SnakeGame.cpp/blob/d5876e5e9d662826cc5019969f10d6105fee0561/Screenshot.png)

📌 Data Structures Used

1️⃣ Queue (std::queue)

Used in the Snake class to store the snake's body segments.
Allows efficient insertion of new segments at the head and removal at the tail.

2️⃣ Set (std::set)

Maintains the snake's body positions for quick lookup.
Helps efficiently detect self-collisions.

3️⃣ Pair (std::pair)

Represents coordinates of the snake's segments, food, and head.
Convenient for handling (x, y) positions.

🏗️ Class Structure

Food Class

Attributes:

int x, y → Coordinates of the food.

Methods:

Food() → Initializes food by calling Respawn().
void Respawn() → Generates random food coordinates within the board.

Snake Class

Attributes:

queue<pair<int, int>> body → Stores the snake's segments.
set<pair<int, int>> bodySet → Tracks the body for collision detection.
eDirection direction → Current movement direction.
pair<int, int> head → Snake's head position.
0
Methods:

Snake() → Initializes snake with three segments, facing right.
void Move(bool grow) → Moves the snake. If grow is true, the snake grows by keeping the tail.
bool CollidedWithSelf() → Checks if the snake collides with itself.

GameBoard Class

Attributes:

Snake snake → Manages the snake.
Food food → Manages food spawning.
bool gameOver → Tracks game status.
int score → Player's score.

Methods:

GameBoard() → Initializes the game and resets it.
void Reset() → Resets the game state.
void Draw() → Renders the game board.
void Input() → Handles player input.
void Logic() → Implements game mechanics and handles score updates.
void GameOverScreen() → Displays game-over screen and handles restart.

⚙️ Technical Details
Programming Concepts Used

OOP (Object-Oriented Programming)
Snake, Food, and GameBoard classes
Encapsulation of game logic

Data Structures

Queue (or Vector) for snake’s body
2D Grid representation of game area
Keyboard Input Handling (_kbhit() and _getch())

🚀 Future Enhancements

Obstacles & Levels → Add walls and difficulty levels.
Special Power-ups → Bonus food for speed boosts.
Multiplayer Mode → Play with another snake.
