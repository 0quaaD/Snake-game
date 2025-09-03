#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH       850
#define HEIGHT      850
#define CELL_SIZE   30
#define CELL_COUNT  25
#define MAX_LENGTH 50

extern Color light_green;
extern Color dark_green;

typedef enum {
  PLAYING,
  GAME_OVER
} GameState;

typedef struct {
  Vector2 pos;
  Texture2D shape;
} Food;

typedef struct Node {
  Vector2 pos;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  int size;
} Snake;

typedef struct {
  int _limX, _limY;   // Top left
  int limX_, limY_;   // Top right
  int __limX, __limY; // Bottom left
  int limX__, limY__; //Bottom right
} Border;

void initSnake(Snake *snake, Vector2 startPos);
void pushHead(Snake *snake, Vector2 newPos);
void popTail(Snake *snake);
void drawSnake(Snake *snake, Color color);
void drawFps(char *fps);
void drawBorder(Border *border, Color color);
void drawFood(Food *food);
void drawGameOver(int score, float playtime);
void updateSnake(Snake *snake, Border *border);

bool isFoodOnSnake(Vector2 foodPos, Snake *snake);
bool isGameOver(Snake *snake);


Vector2 getHead(Snake *snake);
Vector2 getRandomFood(Border *border);

#endif
