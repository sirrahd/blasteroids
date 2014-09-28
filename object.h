#pragma once

#include "list.h"

typedef enum {
  Spaceship,
  Asteroid,
  Blast,
} Type;

typedef struct {
  float x;
  float y;
  float r;
} Euclidean;

typedef struct {
  Type type;
  
  float speed_limit;
  
  Euclidean position;
  Euclidean velocity;
  Euclidean acceleration;
  
  struct {
    float size;
    ALLEGRO_COLOR color;
  } structure;
  
  struct {
    int no_blast;
    int no_accel;
    int dead;
  } state;
  
  Euclidean mirror;
} Object;

Object* object_new(Type type, Euclidean resolution);
void object_draw(Object* object, Euclidean resolution);
void object_move(Object* o, List* list, Euclidean boundaries);
void object_delete(Object* object);
