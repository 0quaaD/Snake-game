/*
  The Snake Game - Created by 0quaaD
  Starting to game:
  $ make run 

  Required libraries and programmes:

  1) GCC       -       GNU C Compiler
  2) make      -       Needed for compiling the game
  3) raylib.h  -       Essential game engine library by Raylib on github

*/

#include "game.h"
#include <raylib.h>
/*
int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "The Snake Game");
  InitAudioDevice();

  Sound snake_eating = LoadSound("src/assets/apple.wav");
  Sound gong = LoadSound("src/assets/gong.wav");
  SetTargetFPS(60);

  Texture2D apple = LoadTexture("./src/assets/apple.jpg");
  GameState gameState = PLAYING;
  float startTime = GetTime();
  float playtime = 0.0f;

  Border border = {
        30,         40,          // Top left
        WIDTH - 30, 40,          // Top right
        30,         HEIGHT - 40, // Bottom left
        WIDTH - 30, HEIGHT - 40  // Bottom right
  };
  Food food = {getRandomFood(&border), apple};

  Snake snake;
  Vector2 startPos = {6 * CELL_SIZE, 8 * CELL_SIZE};
  initSnake(&snake, startPos);
  Vector2 dir = {CELL_SIZE , 0};


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
      if (isGameOver(newHead, &snake))
        gameState = GAME_OVER;
      else {
        if (food.pos.x == newHead.x && food.pos.y == newHead.y) {
            pushHead(&snake, newHead);
            PlaySound(snake_eating);
            score_val++;
            if (score_val % 10 == 0)
            PlaySound(gong);
            food.pos = getRandomFood(&border);
            if (isFoodOnSnake(food.pos, &snake))
            continue;
        } else {
            pushHead(&snake, newHead);
            popTail(&snake);
        }
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

  UnloadSound(gong);
  UnloadSound(snake_eating);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
*/

int main(void) {
    srand(time(NULL));
    InitWindow(WIDTH, HEIGHT, "The Snake Game");
    InitAudioDevice();

    Sound snake_eating = LoadSound("src/assets/apple.wav");
    SetTargetFPS(60);

    Texture2D apple = LoadTexture("./src/assets/apple.jpg");

    // Game state variables
    GameState gameState = PLAYING;
    float startTime = GetTime();
    float playTime = 0.0f;

    Border border = {
        30,         40,          // Top left
        WIDTH - 30, 40,          // Top right
        30,         HEIGHT - 40, // Bottom left
        WIDTH - 30, HEIGHT - 40  // Bottom right
    };

    // Initialize game
    Snake snake;
    Vector2 startPos = {6 * CELL_SIZE, 8 * CELL_SIZE};
    initSnake(&snake, startPos);
    Vector2 dir = {CELL_SIZE, 0};
    Food food = {getRandomFood(&border), apple};
    int score_val = 0;

    while (!WindowShouldClose()) {
        if (gameState == PLAYING) {
            // Update play time
            playTime = GetTime() - startTime;
            
            // Input handling
            if (IsKeyDown(KEY_UP) && dir.y == 0)
                dir = (Vector2){0, -CELL_SIZE};
            if (IsKeyDown(KEY_DOWN) && dir.y == 0)
                dir = (Vector2){0, CELL_SIZE};
            if (IsKeyDown(KEY_LEFT) && dir.x == 0)
                dir = (Vector2){-CELL_SIZE, 0};
            if (IsKeyDown(KEY_RIGHT) && dir.x == 0)
                dir = (Vector2){CELL_SIZE, 0};

            // Game logic
            static int frame = 0;
            frame++;
            if (frame >= 5) {
                Vector2 newHead = {getHead(&snake).x + dir.x, getHead(&snake).y + dir.y};
                
                // Check for self collision
                pushHead(&snake, newHead); // Add new head first
                if (isGameOver(&snake)) {
                    gameState = GAME_OVER;
                } else {
                    // Check food collision
                    if (food.pos.x == newHead.x && food.pos.y == newHead.y) {
                        PlaySound(snake_eating);
                        score_val++;
                        food.pos = getRandomFood(&border);
                    } else {
                        popTail(&snake);
                    }
                }
                frame = 0;
            }
        } else if (gameState == GAME_OVER) {
            // Game over input handling
            if (IsKeyPressed(KEY_SPACE)) {
                // Restart game
                gameState = PLAYING;
                
                // Reset snake
                Node *curr = snake.head;
                while (curr) {
                    Node *tmp = curr;
                    curr = curr->next;
                    free(tmp);
                }
                
                // Reinitialize everything
                initSnake(&snake, startPos);
                dir = (Vector2){CELL_SIZE, 0};
                food.pos = getRandomFood(&border);
                score_val = 0;
                startTime = GetTime();
                playTime = 0.0f;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(light_green);
        
        if (gameState == PLAYING) {
            drawSnake(&snake, dark_green);
            drawBorder(&border, BLACK);
            drawFood(&food);
            
            // Score
            char score[32];
            sprintf(score, "Score: %d", score_val);
            DrawText(score, 710, 10, 20, BLACK);

            // FPS
            char fps[32];
            drawFps(fps);
        } else if (gameState == GAME_OVER) {
            // Still draw the game in background (optional)
            drawSnake(&snake, dark_green);
            drawBorder(&border, BLACK);
            drawFood(&food);
            
            // Draw game over screen
            drawGameOver(score_val, playTime);
        }
        
        EndDrawing();
    }

    // Cleanup
    Node *curr = snake.head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    UnloadTexture(apple);
    UnloadSound(snake_eating);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
