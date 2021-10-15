#include <iostream>
// Header file for detecting keypress
#include <windows.h>
// Header file for the graphic window
#include <graphics.h>
// Header to create a new thread to move the snake
#include <thread>

using namespace std;

// TODO: Create maze on the graphic window
// TODO: Make snake move in different directions on key press
// TODO: Add food for snake
// TODO: Increase snake size after eating food
// TODO: End game if snake collides with the wall or itself

int snakePos;

void moveSnake() {
    // Running animation endlessly
    while (true) {
        cout << "Snake is moving" << endl;
        // Draws a THICK white line
        setcolor(WHITE);
        line(100-1, 100+snakePos, 100-1, 500+snakePos);
        line(100, 100+snakePos, 100, 500+snakePos);
        line(100+1, 100+snakePos, 100+1, 500+snakePos);
        // Delay for animation
        Sleep(100);
        // Draws a THICK black line over the white line to erase the white line to produce the animation
        setcolor(BLACK);
        line(100-1, 100+snakePos, 100-1, 500+snakePos);
        line(100, 100+snakePos, 100, 500+snakePos);
        line(100+1, 100+snakePos, 100+1, 500+snakePos);
        // Incrementing the position of the snake
        snakePos++;
    }
}

int main() {
    snakePos = 0;
    // Initialize graphic window for the animations
    initwindow(800, 600, "Snake Game");
    // A separate thread to run the animation on
    thread t(moveSnake);
    // Detects arrow key press key
    while (true)
    {
        if (GetAsyncKeyState(VK_UP)) {
            cout << "Up arrow key pressed" << endl;
            Sleep(200);
        } else if (GetAsyncKeyState(VK_DOWN)) {
            cout << "Down arrow key pressed" << endl;
            Sleep(200);
        } else if (GetAsyncKeyState(VK_LEFT)) {
            cout << "Left arrow key pressed" << endl;
            Sleep(200);
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            cout << "Right arrow key pressed" << endl;
            Sleep(200);
        } else if (GetAsyncKeyState(VK_ESCAPE)) {
            cout << "Escape key pressed" << endl;
            break;
        }
    }
    return 0;
}
