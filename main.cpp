#include <bits/stdc++.h>
// Header file for detecting keypress
#include <windows.h>
// Header file for the graphic window
#include <graphics.h>

using namespace std;

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

vector<pair<int, int>> foodCoordinates(9);

int random(int min, int max) {
    static bool first = true;
    if (first) {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

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
    bool hasEatenItself = (len > 1 && hasMoveAwayFromVertexByMoreThanOnePixel &&
                           getpixel(snake[len - 1]->head.first, snake[len - 1]->head.second) == 15);
    return hasHitWall || hasEatenItself;
}

void incrementTail() {
    if (snake[0]->direction == UP) {
        snake[0]->tail.second += 20;
    } else if (snake[0]->direction == DOWN) {
        snake[0]->tail.second -= 20;
    } else if (snake[0]->direction == LEFT) {
        snake[0]->tail.first += 20;
    } else if (snake[0]->direction == RIGHT) {
        snake[0]->tail.first -= 20;
    }
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

void generateRandomFood() {
    while (true) {
        int x = random(0, 800);
        int y = random(0, 600);;
        bool hasNoObstruction =
                (getpixel(x, y) != 15 &&
                 getpixel(x, y) != 2)
                &&
                (getpixel(x, y + 1) != 15 &&
                 getpixel(x, y + 1) != 2)
                &&
                (getpixel(x + 1, y + 1) != 15 &&
                 getpixel(x + 1, y + 1) != 2)
                &&
                (getpixel(x + 1, y) != 15 &&
                 getpixel(x + 1, y) != 2)
                &&
                (getpixel(x + 1, y - 1) != 15 &&
                 getpixel(x + 1, y - 1) != 2)
                &&
                (getpixel(x, y - 1) != 15 &&
                 getpixel(x, y - 1) != 2)
                &&
                (getpixel(x - 1, y - 1) != 15 &&
                 getpixel(x - 1, y - 1) != 2)
                &&
                (getpixel(x - 1, y) != 15 &&
                 getpixel(x - 1, y) != 2)
                &&
                (getpixel(x - 1, y + 1) != 15 &&
                 getpixel(x - 1, y + 1) != 2) &&
                !(x == foodCoordinates[0].first && y == foodCoordinates[0].second);
        if (hasNoObstruction) {
            foodCoordinates[0] = pair<int, int>(x, y);
            foodCoordinates[1] = pair<int, int>(x, y + 1);
            foodCoordinates[2] = pair<int, int>(x + 1, y + 1);
            foodCoordinates[3] = pair<int, int>(x + 1, y);
            foodCoordinates[4] = pair<int, int>(x + 1, y - 1);
            foodCoordinates[5] = pair<int, int>(x, y - 1);
            foodCoordinates[6] = pair<int, int>(x - 1, y - 1);
            foodCoordinates[7] = pair<int, int>(x - 1, y);
            foodCoordinates[8] = pair<int, int>(x - 1, y + 1);
            putpixel(x, y, WHITE);
            putpixel(x, y + 1, WHITE);
            putpixel(x + 1, y + 1, WHITE);
            putpixel(x + 1, y, WHITE);
            putpixel(x + 1, y - 1, WHITE);
            putpixel(x, y - 1, WHITE);
            putpixel(x - 1, y - 1, WHITE);
            putpixel(x - 1, y, WHITE);
            putpixel(x - 1, y + 1, WHITE);
            break;
        }
    }
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

void drawHead() {
    if (snake[snake.size() - 1]->direction == UP || snake[snake.size() - 1]->direction == DOWN) {
        putpixel(snake[snake.size() - 1]->head.first - 1, snake[snake.size() - 1]->head.second, WHITE);
        putpixel(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second, WHITE);
        putpixel(snake[snake.size() - 1]->head.first + 1, snake[snake.size() - 1]->head.second, WHITE);
    } else {
        putpixel(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second - 1, WHITE);
        putpixel(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second, WHITE);
        putpixel(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second + 1, WHITE);
    }
}

void eraseTail() {
    if (snake[0]->direction == UP) {
        putpixel(snake[0]->tail.first - 1, snake[0]->tail.second + 1, BLACK);
        putpixel(snake[0]->tail.first, snake[0]->tail.second + 1, BLACK);
        putpixel(snake[0]->tail.first + 1, snake[0]->tail.second + 1, BLACK);
    } else if (snake[0]->direction == DOWN) {
        putpixel(snake[0]->tail.first - 1, snake[0]->tail.second - 1, BLACK);
        putpixel(snake[0]->tail.first, snake[0]->tail.second - 1, BLACK);
        putpixel(snake[0]->tail.first + 1, snake[0]->tail.second - 1, BLACK);
    } else if (snake[0]->direction == LEFT) {
        putpixel(snake[0]->tail.first + 1, snake[0]->tail.second - 1, BLACK);
        putpixel(snake[0]->tail.first + 1, snake[0]->tail.second, BLACK);
        putpixel(snake[0]->tail.first + 1, snake[0]->tail.second + 1, BLACK);
    } else {
        putpixel(snake[0]->tail.first - 1, snake[0]->tail.second - 1, BLACK);
        putpixel(snake[0]->tail.first - 1, snake[0]->tail.second, BLACK);
        putpixel(snake[0]->tail.first - 1, snake[0]->tail.second + 1, BLACK);
    }
}

void moveSnake() {
    // Running animation endlessly
    while (true) {
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
        eraseTail();
        // Checks if snake has reached the food
        vector<pair<int, int>>::iterator it;
        it = find(foodCoordinates.begin(), foodCoordinates.end(), snake[snake.size() - 1]->head);
        if (it != foodCoordinates.end()) {
            cout << "Reached Inside" << endl;
            for (int i = 0; i < 9; ++i) {
                putpixel(foodCoordinates[i].first, foodCoordinates[i].second, BLACK);
                cout << foodCoordinates[i].first << ", " << foodCoordinates[i].second << endl;
            }
            generateRandomFood();
            incrementTail();
        }
        // Checks if the snake has hit the wall
        if (snakeHasHitWallOrEatenItself()) {
            break;
        }
        drawHead();
        Sleep(5);
    }
    exit(0);
}

int main() {
    // Initialize graphic window for the animations
    initwindow(800, 600, "Snake Game");
    Snake *initialSnake = new Snake(pair<int, int>(100, 100), pair<int, int>(100, 400), UP);
    drawThickLine(100, 100, 100, 400, UP, WHITE);
    snake.push_back(initialSnake);
    createWalls();
    // A separate thread to run the animation on
    thread t(moveSnake);
    generateRandomFood();
    // Detects arrow key press key
    while (true) {
        if (GetAsyncKeyState(0x57)) {
            cout << "W key pressed" << endl;
            if (snake[snake.size() - 1]->direction != DOWN && snake[snake.size() - 1]->direction != UP) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        UP);
                snake.push_back(head);
                eraseTail();
                drawThickLine(snake[snake.size() - 2]->tail.first, snake[snake.size() - 2]->tail.second,
                              snake[snake.size() - 2]->head.first, snake[snake.size() - 2]->head.second,
                              snake[snake.size() - 2]->direction, WHITE);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(0x53)) {
            cout << "S key pressed" << endl;
            if (snake[snake.size() - 1]->direction != DOWN && snake[snake.size() - 1]->direction != UP) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        DOWN);
                snake.push_back(head);
                eraseTail();
                drawThickLine(snake[snake.size() - 2]->tail.first, snake[snake.size() - 2]->tail.second,
                              snake[snake.size() - 2]->head.first, snake[snake.size() - 2]->head.second,
                              snake[snake.size() - 2]->direction, WHITE);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(0x41)) {
            cout << "A key pressed" << endl;
            if (snake[snake.size() - 1]->direction != LEFT && snake[snake.size() - 1]->direction != RIGHT) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        LEFT);
                snake.push_back(head);
                eraseTail();
                drawThickLine(snake[snake.size() - 2]->tail.first, snake[snake.size() - 2]->tail.second,
                              snake[snake.size() - 2]->head.first, snake[snake.size() - 2]->head.second,
                              snake[snake.size() - 2]->direction, WHITE);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(0x44)) {
            cout << "D key pressed" << endl;
            if (snake[snake.size() - 1]->direction != LEFT && snake[snake.size() - 1]->direction != RIGHT) {
                Snake *head = new Snake(
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        pair<int, int>(snake[snake.size() - 1]->head.first, snake[snake.size() - 1]->head.second),
                        RIGHT);
                snake.push_back(head);
                eraseTail();
                drawThickLine(snake[snake.size() - 2]->tail.first, snake[snake.size() - 2]->tail.second,
                              snake[snake.size() - 2]->head.first, snake[snake.size() - 2]->head.second,
                              snake[snake.size() - 2]->direction, WHITE);
            }
            Sleep(200);
        } else if (GetAsyncKeyState(VK_ESCAPE)) {
            cout << "Escape key pressed" << endl;
            break;
        }
    }
    return 0;
}
