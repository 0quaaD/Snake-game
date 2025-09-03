#include "../include/game.h"

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

Vector2 getRandomFood(Border *border) {
  int minCellX = border->_limX / CELL_SIZE + 1;      // Start after left border
  int maxCellX = border->limX_ / CELL_SIZE - 1;      // End before right border
  int minCellY = border->_limY / CELL_SIZE + 1;      // Start after top border  
  int maxCellY = border->limY__ / CELL_SIZE - 1;     // End before bottom border
  
  int randX = GetRandomValue(minCellX, maxCellX);
  int randY = GetRandomValue(minCellY, maxCellY);
  
  Vector2 pos = {randX * CELL_SIZE, randY * CELL_SIZE};
  return pos;
}

void drawFps(char *fps) {
  sprintf(fps, "FPS: %d", GetFPS());
  DrawText(fps, 10, 10, 20, BLACK);
}

bool isFoodOnSnake(Vector2 foodPos, Snake *snake){
  Node *curr = snake->head;
  while(curr){
    if(curr->pos.x == foodPos.x && curr->pos.y == foodPos.y)
      return true;
    curr = curr->next;
  }
  return false;
}

bool isGameOver(Snake *snake){
  if(snake->size < 4) return false;
  Vector2 head = snake->head->pos;
  Node *curr = snake->head->next;
  while(curr){
    if(curr->pos.x == head.x && curr->pos.y == head.y)
      return true;
    curr = curr->next;
  }
  return false;
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

void drawGameOver(int score, float playtime){
  DrawRectangle(0, 0, WIDTH, HEIGHT, (Color){0,0,0,150});

  const char *game_over_text = "GAME OVER";
  int gameOverWidth = MeasureText(game_over_text, 60);

  DrawText(game_over_text, (WIDTH - gameOverWidth) / 2, HEIGHT / 2 -100, 60, RED);

  char score_text[64];
  sprintf(score_text, "Final score: %d", score);
  int scoreWidth = MeasureText(score_text, 30);

  DrawText(score_text, (WIDTH - scoreWidth) / 2, HEIGHT / 2 - 20, 30, RAYWHITE);

  int minut = (int)playtime / 60;
  int sec = (int)playtime % 60;

  char timeText[64];
  sprintf(timeText, "Time played: %02d:%02d", minut, sec);
  int timeWidth = MeasureText(timeText, 30);
  DrawText(timeText, (WIDTH - timeWidth) / 2, HEIGHT / 2 + 20, 30, RAYWHITE);

  const char *exitText = "Press ESC or click to 'x' on top right corner of game window to EXIT.";
  int exitWidth = MeasureText(exitText, 20);
  DrawText(exitText, (WIDTH - exitWidth) / 2, HEIGHT / 2 + 80, 20, LIGHTGRAY);
}
