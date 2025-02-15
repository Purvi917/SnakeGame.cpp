#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <set>

using namespace std;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
const int width = 50, height = 20;



class Snake {
public:
       queue<pair<int, int>> body;
       multiset<pair<int, int>> bodySet;  // Faster lookup for self-collision
       eDirection direction;
        pair<int, int> head;

    Snake() {
        direction = RIGHT;
        head = { width / 2, height / 2 };

        // Initialize snake with three segments
        for (int i = 0; i < 3; i++) {
            body.push({ head.first - i, head.second });
            bodySet.insert({ head.first - i, head.second });
        }
    }

    void Move(bool grow) {
        int prevX = head.first, prevY = head.second;

        switch (direction) {
        case LEFT: head.first--; break;
        case RIGHT: head.first++; break;
        case UP: head.second--; break;
        case DOWN: head.second++; break;
        default: break;
        }

        if (head.first >= width || head.first < 0 ||
            head.second >= height || head.second < 0) {
            return;  // Prevent out-of-bounds update
        }

        // Add new head
        body.push(head);
        bodySet.insert(head);

        // Remove tail if not growing
        if (!grow) {
            pair<int, int> tail = body.front();
            body.pop();
            bodySet.erase(tail);
        }
    }

    bool CollidedWithSelf() {
        return bodySet.count(head) > 1; // If head position appears twice, it's a collision
    }
};

class Food {
    public:
        int x, y;
        multiset<pair<int, int>> bodySet;
        Food() { Respawn(); }
        void Respawn() { 
            //x = rand() % width; y = rand() % height;
            do {
                x = rand() % width;
                y = rand() % height;
            } while (bodySet.find({x, y}) != bodySet.end());
         }
    };

class GameBoard {
public:
    Snake snake;
    Food food;
    bool gameOver;
    int score;

    GameBoard() { Reset(); }

    void Reset() {
        gameOver = false;
        score = 0;
        snake = Snake();
        food.Respawn();
    }

    void Draw() {
        //system("cls");
        HANDLE hConsole =
            GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPosition = { 0,0 };
        SetConsoleCursorPosition( hConsole, cursorPosition);

        char grid[height][width] = {};

        // Place food
        grid[food.y][food.x] = 'F';

        // Place snake
        queue<pair<int, int>> temp = snake.body;
        while (!temp.empty()) {
            pair<int, int> segment = temp.front();
            temp.pop();
            grid[segment.second][segment.first] = 'o';
        }
        grid[snake.head.second][snake.head.first] = '@';

        // Draw board
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            cout << "#";
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == 0) cout << " ";
                else cout << grid[i][j];
            }
            cout << "#\n";
        }

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << "\nScore: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a': if (snake.direction != RIGHT) snake.direction = LEFT; break;
            case 'd': if (snake.direction != LEFT) snake.direction = RIGHT; break;
            case 'w': if (snake.direction != DOWN) snake.direction = UP; break;
            case 's': if (snake.direction != UP) snake.direction = DOWN; break;
            case 'x': gameOver = true; break;
            }
        }
    }

    void Logic() {
        if (gameOver) return;

        bool grow = (snake.head.first == food.x && snake.head.second == food.y);
        if (grow) {
            score += 10;
            food.Respawn();
        }

        snake.Move(grow);

        // Ensure the game doesn't end on first render
        if (snake.head.first >= width || snake.head.first < 0 ||
            snake.head.second >= height || snake.head.second < 0 ||
            snake.CollidedWithSelf()) {
            gameOver = true;
        }
    }

    void GameOverScreen() {
        cout << "Game Over! Final Score: " << score << endl;
        cout << "Press R to restart or X to exit." << endl;
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'r' || ch == 'R') {
                    Reset();
                    break;
                }
                if (ch == 'x' || ch == 'X') {
                    exit(0);
                }
            }
        }
    }
};

int main() {
    GameBoard game;
    while (true) {
        while (!game.gameOver) {
            game.Draw();
            game.Input();
            game.Logic();
            Sleep(100);
        }
        game.GameOverScreen();
    }
    return 0;
}