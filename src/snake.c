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

Color light_green = {173, 204, 96,255}; // Background color
Color dark_green = {43, 51, 24, 255}; // Snake color 

typedef struct {
  Vector2 pos;
  Texture2D shape;
} Food;

typedef struct {
  int _limX, _limY;   // Top left
  int limX_, limY_;   // Top right
  int __limX, __limY; // Bottom left
  int limX__, limY__; //Bottom right
} Border;

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

int get_score() {
  return 0;  
}

void drawBorder(Border *border, Color color) {
  DrawLine(border->_limX, border->_limY, border->limX_, border->limY_, color);
  DrawLine(border->__limX , border->__limY,border->limX__, border->limY__, color);
  DrawLine(border->_limX, border->_limY, border->__limX, border->__limY, color);
  DrawLine(border->limX_, border->limY_, border->limX__, border->limY__, color);  
}

void drawScore(char *score) {
  sprintf(score, "Score: %d", get_score());
  DrawText(score, 710, 10, 20, BLACK);
}

int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "The Snake Game");
  SetTargetFPS(60);

  Texture2D apple = LoadTexture("./src/assets/apple.jpg");
  Food food = {getRandomFood(), apple};
  Border border = {
      30,         40,          // Top left
      WIDTH - 30, 40,          // Top right
      30,         HEIGHT - 40, // Bottom left
      WIDTH - 30, HEIGHT - 40  // Bottom right
  };
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(light_green);
    drawBorder(&border, BLACK);
    char score[32];
    drawScore(score);

    drawFood(&food);
 
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
