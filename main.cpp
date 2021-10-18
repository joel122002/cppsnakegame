#include <bits/stdc++.h>
// Header file for detecting keypress
#include <windows.h>
// Header file for the graphic window
#include <graphics.h>

using namespace std;

// TODO: Add walls and obstructions
// TODO: Add food for snake
// TODO: Increase snake size after eating food
// TODO: End game if snake collides with the wall or itself

enum direction {
    RIGHT, LEFT, UP, DOWN
};

// Class which represents a snake
class Snake {
public:
    // Holds coordinates of the head
    pair<int, int> head;
    // Holds coordinates of the tail
    pair<int, int> tail;
    // Holds the direction in which the snake is moving
    direction direction;

    // Constructor to initialize the head tail and direction
    Snake(pair<int, int> head, pair<int, int> tail, enum direction direction) {
        this->head = head;
        this->tail = tail;
        this->direction = direction;
    }
};

void drawThickLine(int x1, int y1, int x2, int y2, direction direction, colors color) {
    cout << "x1 :" << x1 << "y1 :" << y1 << endl;
    cout << "x2 :" << x2 << "y2 :" << y2 << endl;
    setcolor(color);
    if (direction == DOWN || direction == UP) {
        line(x1 - 1, y1, x2 - 1, y2);
        line(x1, y1, x2, y2);
        line(x1, y1 + 1, x2 + 1, y2);
    } else {
        line(x1, y1 - 1, x2,y2 - 1);
        line(x1, y1, x2,y2);
        line(x1, y1 + 1, x2,y2 + 1);
    }
}

// Vector of snakes. Basically at each turn we create a new snake object. Then we increment the head of the last snake
// element and decrement the tail of the first tail element. If the head and tail of the first element are the same we
// pop the fist element. If there is only one element in the vector we increment or decrement the head and tail
// coordinates depending on the direction in which the head is moving
vector<Snake *> snake;


void moveSnake() {
    // Running animation endlessly
    while (true) {
        // If snake vector has one element then we increment or decrement the head/tail of that element
        if (snake.size() == 1) {
            // Incrementing/decrementing the x or y coordinates of the head and tail to make the snake move
            if (snake[0]->direction == DOWN) {
                snake[0]->tail.second++;
                snake[0]->head.second++;
            } else if (snake[0]->direction == UP) {
                snake[0]->tail.second--;
                snake[0]->head.second--;
            } else if (snake[0]->direction == LEFT) {
                snake[0]->tail.first--;
                snake[0]->head.first--;
            } else {
                snake[0]->tail.first++;
                snake[0]->head.first++;
            }
            setcolor(WHITE);
            if (snake[0]->direction == DOWN || snake[0]->direction == UP) {
                line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1, snake[0]->head.second);
                line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1, snake[0]->head.second);
            } else {
                line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,snake[0]->head.first - 1);
                line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first,snake[0]->head.first);
                line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,snake[0]->head.first + 1);
            }
            Sleep(100);
            setcolor(BLACK);
            if (snake[0]->direction == DOWN || snake[0]->direction == UP) {
                line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1, snake[0]->head.second);
                line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1, snake[0]->head.second);
            } else {
                line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,snake[0]->head.first - 1);
                line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first,snake[0]->head.first);
                line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,snake[0]->head.first + 1);
            }
        }
        // If snake vector has more than one element then we increment or decrement the head of the last element and decrement or increment the tail of the first element
        else {
            // Incrementing/Decrementing the head of the last element
            if (snake[snake.size() - 1]->direction == DOWN) {
                snake[snake.size() - 1]->head.second++;
            } else if (snake[snake.size() - 1]->direction == UP) {
                snake[snake.size() - 1]->head.second--;
            } else if (snake[snake.size() - 1]->direction == LEFT) {
                snake[snake.size() - 1]->head.first--;
            } else {
                snake[snake.size() - 1]->head.first++;
            }
            // Incrementing/Decrementing the tail of the last element
            if (snake[0]->direction == DOWN) {
                snake[0]->tail.second++;
            } else if (snake[0]->direction == UP) {
                snake[0]->tail.second--;
            } else if (snake[0]->direction == LEFT) {
                snake[0]->tail.first--;
            } else {
                snake[0]->tail.first++;
            }
            // Popping the first element if its tail and head of the fist element coincide
            if (snake[0]->head == snake[0]->tail) {
                snake.erase(snake.begin());
            }
            // Drawing the increment in the head of the last element
            if (snake[snake.size() - 1]->direction == UP || snake[snake.size() - 1]->direction == DOWN) {
                // Draws a THICK white line
                setcolor(WHITE);
                line(snake[snake.size() - 1]->tail.first - 1, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first - 1, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first + 1, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first + 1, snake[snake.size() - 1]->head.second);
                // Drawing the increment in the tail of the first element
                if (snake[0]->direction == UP || snake[0]->direction == DOWN) {
                    // Draws a THICK white line
                    line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1,
                         snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1,
                         snake[0]->head.second);
                } else {
                    drawThickLine(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second, snake[0]->direction, WHITE);
                    // Draws a THICK white line
                    line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,
                         snake[0]->head.second - 1);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,
                         snake[0]->head.second + 1);
                }
                // Delay for animation
                Sleep(100);
                // Draws a THICK black line over the white line to erase the white line to produce the animation
                setcolor(BLACK);
                line(snake[snake.size() - 1]->tail.first - 1, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first - 1, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first + 1, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first + 1, snake[snake.size() - 1]->head.second);
                if (snake[0]->direction == UP || snake[0]->direction == DOWN) {
                    line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1,
                         snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1,
                         snake[0]->head.second);
                } else {
                    line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,
                         snake[0]->head.second - 1);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,
                         snake[0]->head.second + 1);
                }
            } else {
                // Draws a THICK white line
                setcolor(WHITE);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second - 1,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second - 1);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second + 1,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second + 1);
                if (snake[0]->direction == UP || snake[0]->direction == DOWN) {
                    line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1,
                         snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1,
                         snake[0]->head.second);
                } else {
                    line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,
                         snake[0]->head.second - 1);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,
                         snake[0]->head.second + 1);
                }
                // Delay for animation
                Sleep(100);
                // Draws a THICK black line over the white line to erase the white line to produce the animation
                setcolor(BLACK);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second - 1,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second - 1);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second);
                line(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second + 1,
                     snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second + 1);
                if (snake[0]->direction == UP || snake[0]->direction == DOWN) {
                    line(snake[0]->tail.first - 1, snake[0]->tail.second, snake[0]->head.first - 1,
                         snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first + 1, snake[0]->tail.second, snake[0]->head.first + 1,
                         snake[0]->head.second);
                } else {
                    line(snake[0]->tail.first, snake[0]->tail.second - 1, snake[0]->head.first,
                         snake[0]->head.second - 1);
                    line(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second);
                    line(snake[0]->tail.first, snake[0]->tail.second + 1, snake[0]->head.first,
                         snake[0]->head.second + 1);
                }
            }
        }
    }
}

int main() {
    // Initialize graphic window for the animations
    initwindow(800, 600, "Snake Game");
    Snake *initialSnake = new Snake(pair<int, int>(100, 100), pair<int, int>(100, 400), UP);
    snake.push_back(initialSnake);
    // A separate thread to run the animation on
    thread t(moveSnake);
    // Detects arrow key press key
    while (true) {
        if (GetAsyncKeyState(VK_UP)) {
            cout << "Up arrow key pressed" << endl;
            if (snake[snake.size() - 1]->direction != DOWN && snake[snake.size() - 1]->direction != UP) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        UP);
                snake.push_back(head);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(VK_DOWN)) {
            cout << "Down arrow key pressed" << endl;
            if (snake[snake.size() - 1]->direction != DOWN && snake[snake.size() - 1]->direction != UP) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        DOWN);
                snake.push_back(head);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(VK_LEFT)) {
            cout << "Left arrow key pressed" << endl;
            if (snake[snake.size() - 1]->direction != LEFT && snake[snake.size() - 1]->direction != RIGHT) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        LEFT);
                snake.push_back(head);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(VK_RIGHT)) {
            cout << "Right arrow key pressed" << endl;
            if (snake[snake.size() - 1]->direction != LEFT && snake[snake.size() - 1]->direction != RIGHT) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        RIGHT);
                snake.push_back(head);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(VK_ESCAPE)) {
            cout << "Escape key pressed" << endl;
            break;
        }
    }
    return 0;
}
