/*
  The Snake Game - Created by 0quaaD
  Starting to game:
  $ make run FILE=snake

  Required libraries and programmes:

  1) GCC       -       GNU C Compiler
  2) make      -       Needed for compiling the game
  3) raylib.h  -       Essential game engine library by Raylib on github

*/

#include "../include/game.h"

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
