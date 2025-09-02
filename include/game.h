#ifndef GAME_H
#define GAME_H

#include <raylib.h>


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

#endif
