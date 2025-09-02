#include "../include/game.h"
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

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
