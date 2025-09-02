/*
 * The Snake Game - Created by 0quaaD
 * Starting to game:
 * $ make run FILE=snake

 * Required libraries and programmes:

 * 1) GCC - GNU C Compiler
 * 2) make - Needed for compiling the game
 * 3) raylib.h - Essential game engine library by Raylib on github

*/

#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH       810
#define HEIGHT      810
#define CELL_SIZE   30
#define CELL_COUNT  25
#define MAX_LENGTH 50

Color light_green = {173, 204, 96,255}; // Background color
Color dark_green = {43, 51, 24, 255}; // Snake color 

typedef struct {
  Vector2 pos;
  Texture2D shape;
} Food;

typedef struct {
  Vector2 body[MAX_LENGTH];
  int head;
  int tail;
  int size;  
} Snake;

typedef struct {
  int _limX, _limY;   // Top left
  int limX_, limY_;   // Top right
  int __limX, __limY; // Bottom left
  int limX__, limY__; //Bottom right
} Border;

void initSnake(Snake *snake, Vector2 startPos) {
  snake->body[0] = startPos;
  snake->head = 0;
  snake->tail = 0;
  snake->size = 1;
}

// Pushing head when snake moves
void pushHead(Snake *snake, Vector2 newPos) {
  if (snake->size >= MAX_LENGTH)
    return;

  snake->head = (snake->head + 1) % MAX_LENGTH;
  snake->body[snake->head] = newPos;
  snake->size++;
}

// Removing the tail when snake moves
void popTail(Snake *snake) {
  if (snake->size <= 1)
    return;

  snake->tail = (snake->tail + 1) % MAX_LENGTH;
  snake->size--;
}

// Move snake
void moveSnake(Snake *snake, Vector2 newPos) {
  pushHead(snake, newPos);
  popTail(snake);
}

// Growing Snake
void growSnake(Snake *snake, Vector2 newPos) {
  pushHead(snake,newPos);
}

void drawSnake(Snake *snake) {
  for (int i = 0; i < snake->size; i++) {
    int idx = (snake->tail + i) % MAX_LENGTH;
    Rectangle rect = {snake->body[idx].x, snake->body[idx].y, CELL_SIZE,
                      CELL_SIZE};
    DrawRectangleRec(rect, dark_green);
  }
}

Vector2 getSnakeHead(Snake *snake) {
  return snake->body[snake->head];
}

void drawFood(Food *food) {
  Rectangle source = {0, 0, food->shape.width, food->shape.height};
  Rectangle dest = {food->pos.x, food->pos.y, CELL_SIZE, CELL_SIZE};
  Vector2 origin = {0, 0};
  DrawTexturePro(food->shape, source, dest, origin, 0.0f, light_green);
}

Vector2 getRandomFood() {
  int randX = (rand() % (CELL_COUNT - 1));
  int randY = (rand() % (CELL_COUNT - 1));

  Vector2 pos = {randX * CELL_SIZE + 30, randY * CELL_SIZE + 40};
  return pos;
}

void drawFps(char *fps) {
  sprintf(fps, "FPS: %d", GetFPS());
  DrawText(fps, 10, 10, 20, BLACK);
}


void drawBorder(Border *border, Color color) {
  DrawLine(border->_limX, border->_limY, border->limX_, border->limY_, color);
  DrawLine(border->__limX , border->__limY,border->limX__, border->limY__, color);
  DrawLine(border->_limX, border->_limY, border->__limX, border->__limY, color);
  DrawLine(border->limX_, border->limY_, border->limX__, border->limY__, color);  
}

// If snake doesn't eat the food. Do:
void updateSnake(Snake *snake, Vector2 dir) {
  Vector2 currHead = getSnakeHead(snake);
  Vector2 newHead = {currHead.x + dir.x, currHead.y + dir.y};
  pushHead(snake, newHead);
}

// If snake eats the food. Do:
void updateSnakeGrow(Snake *snake, Vector2 dir) {
  Vector2 currHead = getSnakeHead(snake);
  Vector2 newHead = {currHead.x + dir.x, currHead.y + dir.y};
  pushHead(snake, newHead);
}

int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "The Snake Game");
  SetTargetFPS(60);

  Texture2D apple = LoadTexture("./src/assets/apple.jpg");
  Food food = {getRandomFood(), apple};
  Snake snake;
  int score_val = 0;
  Vector2 startPos = {6 * CELL_SIZE, 8 * CELL_SIZE};
  initSnake(&snake, startPos);
  Border border = {
      30,         40,          // Top left
      WIDTH - 30, 40,          // Top right
      30,         HEIGHT - 40, // Bottom left
      WIDTH - 30, HEIGHT - 40  // Bottom right
  };

  Vector2 dir = {CELL_SIZE , 0};
  while (!WindowShouldClose()) {
    // Update part
    if (IsKeyDown(KEY_UP) && dir.y == 0)
	dir = (Vector2){0, -CELL_SIZE};
    if (IsKeyDown(KEY_DOWN) && dir.y == 0)
	dir = (Vector2){0, CELL_SIZE};
    if (IsKeyDown(KEY_LEFT) && dir.x == 0)
	dir = (Vector2){-CELL_SIZE, 0};
    if (IsKeyDown(KEY_RIGHT) && dir.x == 0)
	dir = (Vector2){CELL_SIZE, 0};

    static int frame = 0;
    frame++;
    if (frame >= 10) {
      Vector2 newHead = {getSnakeHead(&snake).x + dir.x,
                         getSnakeHead(&snake).y + dir.y};
      if (food.pos.x == newHead.x && food.pos.y == newHead.y) {
        updateSnakeGrow(&snake, dir);
	score_val++;
	food.pos = getRandomFood();
      } else {
	updateSnake(&snake, dir);
      }
      frame = 0;
    }
    // ===== Draw part ======
    BeginDrawing();
    ClearBackground(light_green);

    // Entity
    drawBorder(&border, BLACK);
    drawSnake(&snake);
    drawFood(&food);
    // Score
    char score[32];
    sprintf(score, "Score: %d", score_val);
    DrawText(score, 710,10,20, BLACK);

    
 
    //Draw fps value    
    char fps[32];
    drawFps(fps);
    EndDrawing();
  }

  // Free the memory before return 0
  UnloadTexture(apple); 
  CloseWindow();
  return 0;  
}
