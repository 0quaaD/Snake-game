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
        50,         50,          // Top left
        WIDTH - 50, 50,          // Top right
        50,         HEIGHT - 50, // Bottom left
        WIDTH - 50, HEIGHT - 50  // Bottom right
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
                
                pushHead(&snake, newHead); 		
		updateSnake(&snake, &border);

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
