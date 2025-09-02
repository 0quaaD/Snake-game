#include <stdio.h>
#include <raylib.h>

#define WIDTH       790
#define HEIGHT      790
#define CELL_SIZE   30
#define CELL_COUNT  25

Color light_green = {173, 204, 96,255}; // Background color
Color dark_green = {43, 51, 24, 255};

typedef struct {
  Vector2 pos;
  Texture2D apple;
} Food;

typedef struct {
  int posX, posY;
} Snake;

void _Draw_FPS(char *fps) {
  sprintf(fps, "FPS: %d", GetFPS());
  DrawText(fps, 10, 10, 20, BLACK);
}

void drawBorder(int limX, int limY,Color color) {
  DrawLine(limX, limY, WIDTH-limX, limY, color); // Up line
  DrawLine(limX, limY, limX, HEIGHT - limY, color); // Left line 
  DrawLine(limX, HEIGHT - limY, WIDTH-limX, HEIGHT-limY, color); // Down line 
  DrawLine(WIDTH-limX, limY, WIDTH-limX, HEIGHT-limY, color); // Right line
}

void drawFood(Food *food) {
  DrawTextureEx(food->apple, food->pos, 0.0f, (float)CELL_SIZE / food->apple.width, light_green);
}

int get_score() {
  return 0;  
}

void drawScore(char *score) {
  sprintf(score, "Score: %d", get_score());
  DrawText(score, 690, 10, 20, BLACK);
}

Vector2 generate_rand_value(int limX, int limY) {
  float randX = CELL_SIZE * GetRandomValue(0, CELL_SIZE - 1);
  float randY = CELL_SIZE * GetRandomValue(0, CELL_SIZE - 1);
  return (Vector2){randX, randY};
}


int main(void) {

  InitWindow(WIDTH, HEIGHT, "Window");
  SetTargetFPS(60);

  int limX = 40, limY = 40;
  Texture2D apple = LoadTexture("./src/assets/apple.jpg");
  
  Food food = { generate_rand_value(limX, limY), apple};
  Snake snake = {};
  while (!WindowShouldClose()) {
    // --- Update part ---
    
    // --- Draw part ---
    BeginDrawing();
    ClearBackground(light_green);

    drawBorder(limX, limY, BLACK);
    drawFood(&food);
    
    // Get Score 
    char score[32];
    drawScore(score);
    
    // Draw FPS on game screen
    char fpsText[32];
    _Draw_FPS(fpsText);
    EndDrawing();
  }
  CloseWindow();
  return 0;  
}
