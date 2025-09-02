/*
  The Snake Game - Created by 0quaaD
  Starting to game:
  $ make run FILE=snake

  Required libraries and programmes:

  1) GCC       -       GNU C Compiler
  2) make      -       Needed for compiling the game
  3) raylib.h  -       Essential game engine library by Raylib on github

*/

#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"

#define WIDTH       810
#define HEIGHT      810
#define CELL_SIZE   30
#define CELL_COUNT  25
#define MAX_LENGTH 50

Color light_green = {142, 185, 97, 255}; // Background color
Color dark_green = DARKGREEN;            // Snake color 

void initSnake(Snake *snake, Vector2 startPos) {
  Node *node = malloc(sizeof(Node));
  node->pos = startPos;
  node->next = node->prev = NULL;
  snake->head = snake->tail = node;
  snake->size = 1;
}
void pushHead(Snake *snake, Vector2 newPos) {
  Node *newNode = malloc(sizeof(Node));
  newNode->pos = newPos;
  newNode->next = snake->head;
  newNode->prev = NULL;

  if (snake->head != NULL) {
    snake->head->prev = newNode;
  }

  snake->head = newNode;
  if (snake->tail == NULL)
    snake->tail = newNode;

  snake->size++;
}

void popTail(Snake *snake) {
  if (snake->tail == NULL)
    return;

  Node *temp = snake->tail;
  snake->tail = snake->tail->prev;
  if (snake->tail != NULL) {
    snake->tail->next = NULL;
  } else {
    snake->head = NULL;
  }
  free(temp);
  snake->size--;
}

Vector2 getHead(Snake *snake) {
  if (!snake->head)
    return (Vector2){0, 0};
  return snake->head->pos;
}

void drawSnake(Snake *snake, Color color) {
  Node *curr = snake->head;
  while (curr) {
    Rectangle rect = {curr->pos.x, curr->pos.y, CELL_SIZE, CELL_SIZE};
    DrawRectangleRounded(rect, 0.5, 6, color);
    curr = curr->next;
  }
}

Vector2 getRandomFood() {
  int randX = (rand() % (CELL_COUNT - 1));
  int randY = (rand() % (CELL_COUNT - 1));

  Vector2 pos = {randX * CELL_SIZE, randY * CELL_SIZE};
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

void drawFood(Food *food) {
  Rectangle source = {0, 0, food->shape.width, food->shape.height};
  Rectangle dest = {food->pos.x, food->pos.y, CELL_SIZE, CELL_SIZE};
  Vector2 origin = {0, 0};
  DrawTexturePro(food->shape, source, dest, origin, 0.0f, light_green);
}

int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "The Snake Game");
  SetTargetFPS(60);

  Texture2D apple = LoadTexture("./src/assets/apple.jpg");

  Food food = {getRandomFood(), apple};

  Snake snake;
  Vector2 startPos = {6 * CELL_SIZE, 8 * CELL_SIZE};
  initSnake(&snake, startPos);
  Vector2 dir = {CELL_SIZE , 0};
  
  Border border = {
      30,         40,          // Top left
      WIDTH - 30, 40,          // Top right
      30,         HEIGHT - 40, // Bottom left
      WIDTH - 30, HEIGHT - 40  // Bottom right
  };
  int score_val = 0;
  while (!WindowShouldClose()) {
    // ===== Update part =====
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
    if (frame >= 5) {
      Vector2 newHead = {getHead(&snake).x + dir.x, getHead(&snake).y + dir.y};
      if (food.pos.x == newHead.x && food.pos.y == newHead.y) {
        pushHead(&snake, newHead);
        score_val++;
	food.pos = getRandomFood();
      } else {
        pushHead(&snake, newHead);
	popTail(&snake);
      }
      frame = 0;
    }
    
    // ===== Draw part ======
    BeginDrawing();
    ClearBackground(light_green);
    
    drawSnake(&snake, dark_green);
    drawBorder(&border, BLACK);
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
  Node *curr = snake.head;
  while (curr) {
    Node *tmp = curr;
    curr = curr->next;
    free(tmp);
  }
  UnloadTexture(apple); 
  CloseWindow();
  return 0;  
}
