#include <bits/stdc++.h>
// Header file for detecting keypress
#include <windows.h>
// Header file for the graphic window
#include <graphics.h>

using namespace std;

// TODO: Add food for snake
// TODO: Increase snake size after eating food

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

// Vector of snakes. Basically at each turn we create a new snake object. Then we increment the head of the last snake
// element and decrement the tail of the first tail element. If the head and tail of the first element are the same we
// pop the fist element. If there is only one element in the vector we increment or decrement the head and tail
// coordinates depending on the direction in which the head is moving
vector<Snake *> snake;

// Function which checks if the snake has hit the wall or eaten itself and returns true if it has hits the wall
bool snakeHasHitWallOrEatenItself() {
    int len = snake.size();
    // Head has to move more than one pixel as the snake has a width of 3 meaning it has one pixels to each sides
    bool hasMoveAwayFromVertexByMoreThanOnePixel;
    if (len > 1) {
        hasMoveAwayFromVertexByMoreThanOnePixel =
                !((snake[len - 1]->head.first == snake[len - 2]->head.first + 1 ||
                snake[len - 1]->head.first == snake[len - 2]->head.first - 1 ||
                snake[len - 1]->head.first == snake[len - 2]->head.first) &&
                (snake[len - 1]->head.second == snake[len - 2]->head.second + 1 ||
                snake[len - 1]->head.second == snake[len - 2]->head.second - 1 ||
                snake[len - 1]->head.second == snake[len - 2]->head.second));
    }
    bool hasHitWall = (getpixel(snake[len - 1]->head.first, snake[len - 1]->head.second) == 2);
    bool hasEatenItself = (len > 1 && hasMoveAwayFromVertexByMoreThanOnePixel && getpixel(snake[len - 1]->head.first, snake[len - 1]->head.second) == 15);
    return hasHitWall || hasEatenItself;
}

// Creates a wall along all four sides of the window of thickness 4px
void createWalls() {
    setcolor(GREEN);
    line(0, 0, 800, 0);
    line(0, 1, 800, 1);
    line(0, 2, 800, 2);
    line(0, 3, 800, 3);
    line(0, 4, 800, 4);

    line(0, 0, 0, 600);
    line(1, 0, 1, 600);
    line(2, 0, 2, 600);
    line(3, 0, 3, 600);
    line(4, 0, 4, 600);

    line(0, 600, 800, 600);
    line(0, 599, 800, 599);
    line(0, 598, 800, 598);
    line(0, 597, 800, 597);
    line(0, 596, 800, 596);

    line(800, 600, 800, 0);
    line(799, 600, 799, 0);
    line(798, 600, 798, 0);
    line(797, 600, 797, 0);
    line(796, 600, 796, 0);
}

void drawThickLine(int x1, int y1, int x2, int y2, direction direction, colors color) {
    setcolor(color);
    if (direction == DOWN || direction == UP) {
        line(x1 - 1, y1, x2 - 1, y2);
        line(x1, y1, x2, y2);
        line(x1 + 1, y1, x2 + 1, y2);
    } else {
        line(x1, y1 - 1, x2, y2 - 1);
        line(x1, y1, x2, y2);
        line(x1, y1 + 1, x2, y2 + 1);
    }
}

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
            // Checks if the snake has hit the wall
            if (snakeHasHitWallOrEatenItself()) {
                break;
            }
            drawThickLine(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second,
                          snake[0]->direction, WHITE);
            Sleep(100);
            drawThickLine(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second,
                          snake[0]->direction, BLACK);
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
            drawThickLine(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second,
                          snake[0]->direction, WHITE);
            // Checks if the snake has hit the wall
            if (snakeHasHitWallOrEatenItself()) {
                break;
            }
            // Draws a THICK white line
            drawThickLine(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                          snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second,
                          snake[snake.size() - 1]->direction, WHITE);
            // Checks if the snake has hit the wall
            // Delay for animation
            Sleep(100);
            // Draws a THICK black line over the white line to erase the white line to produce the animation
            drawThickLine(snake[snake.size() - 1]->tail.first, snake[snake.size() - 1]->tail.second,
                          snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second,
                          snake[snake.size() - 1]->direction, BLACK);
            drawThickLine(snake[0]->tail.first, snake[0]->tail.second, snake[0]->head.first, snake[0]->head.second,
                          snake[0]->direction, BLACK);
        }
    }
    exit(0);
}

int main() {
    // Initialize graphic window for the animations
    initwindow(800, 600, "Snake Game");
    Snake *initialSnake = new Snake(pair<int, int>(100, 100), pair<int, int>(100, 400), UP);
    snake.push_back(initialSnake);
    createWalls();
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