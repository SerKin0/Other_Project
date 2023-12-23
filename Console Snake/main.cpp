#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool GameOver, tail, flag;
const int width = 20;
const int height = 20;
int x_snake, y_snake, x_fruit, y_fruit, score, size_snake;
enum sDiraction {Stop = 0, UP, RIGHT, DOWN, LEFT};
sDiraction dir;
int x_tails[150], y_tails[150];


void gotoxy(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void StartGame() {
    GameOver = false;
    x_snake = (int)(width / 2);
    y_snake = (int)(height / 2);
    x_fruit = rand() % width;
    y_fruit = rand() % height;
    score = 0;
    size_snake = 1;
    dir = Stop;
    system("cls");
}
// ╔=╗ 201 205 187
// ║ ║ 186     186
// ╚=╝ 200 205 188

void DrawMap() {
    gotoxy(0, 0);
    for (int y = 0; y < height + 2; y++) {
        for (int x = 0; x < width + 2; x++) {
            if ((x == x_fruit) && (y == y_fruit)) cout << char(3);
            else if ((x == x_snake) && (y == y_snake)) cout << "0";
            else if ((y == 0) && (x == 0)) cout << char(201);
            else if ((x == width + 1) && (y == 0)) cout << char(187);
            else if ((x == 0) && (y == height + 1)) cout << char(200);
            else if ((x == width + 1) && (y == height + 1)) cout << char(188);
            else if ((x == 0) || (x == width + 1)) cout << char(186);
            else if ((y == 0) || (y == height + 1)) cout << char(205);
            else {
                tail = false;
                for (int i = 0; i < size_snake; i++) {
                    if ((x - 1 == x_tails[i]) && (y - 1 == y_tails[i])) {
                        cout << "o";
                        tail = true;
                        break;
                    }
                }
                if (!tail) cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}


void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'x':
            GameOver = true;
            break;
        }    
    }
}


void Logic() {
    int x_pred = x_tails[0];
    int y_pred = y_tails[0];
    int pred2X, pred2Y;
    x_tails[0] = x_snake-1;
    y_tails[0] = y_snake-1;
    for (int i = 1; i < size_snake; i++) {
        pred2X = x_tails[i];
        pred2Y = y_tails[i];
        x_tails[i] = x_pred;
        y_tails[i] = y_pred;
        x_pred = pred2X;
        y_pred = pred2Y;
    }
    switch (dir)
    {
    case UP:
        y_snake--;
        break;
    case RIGHT:
        x_snake++;
        break;
    case DOWN:
        y_snake++;
        break;
    case LEFT:
        x_snake--;
        break; 
    }
    if (((x_snake < 0) || (x_snake > width)) || ((y_snake < 1) || (y_snake > height))) {
        GameOver = true;
    }
    for (int i = 1; i < size_snake; i++) {
        if (x_tails[i] == x_snake-1 && y_tails[i] == y_snake-1) {
            GameOver = true;
        }
    }
    if ((x_snake == x_fruit) && (y_snake == y_fruit)) {
        score += 100;
        size_snake++;
        tail = true;
        while (tail) {
            x_fruit = rand() % width + 1;
            y_fruit = rand() % height + 1;
            flag = false;
            for (int i = 0; i < size_snake; i++) {
                if (x_fruit == x_tails[i] && y_fruit == y_tails[i]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) tail = false;
        }        
    }
}


int main() {
    StartGame();
    while (!GameOver) {
        DrawMap();
        Input();
        Logic();
        Sleep(100);
    }
}