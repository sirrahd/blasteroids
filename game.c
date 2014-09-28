#include <stdlib.h>
#include "game.h"
#include "list.h"

Game* game_new(int resX, int resY) {
	Game* game = malloc(sizeof(Game));

	game->resolution.x = resX;
	game->resolution.y = resY;
	game->lives = 3;
	game->objects = list_new();
	game->ship = object_new(Spaceship, game->resolution);
	
	list_add(game->objects, game->ship);
	
	int i;
	for (i = 0; i < 5; i++) {
		list_add(game->objects, object_new(Asteroid, game->resolution));
	}
	
	return game;
}

void game_draw(Game* game) {
	Object* o;
	for(o = list_next(game->objects); o != NULL; o = list_next(game->objects)) {
		object_draw(o, game->resolution);
	}
}

void game_move(Game* game) {
	Object* o;
	for(o = list_next(game->objects); o != NULL; o = list_next(game->objects)) {
		object_move(o, game->objects, game->resolution);
  }
}

void ship_rotate(Object* o, int direction) {
  o->velocity.r = (float)direction;
}

void ship_accelerate(Object* o, float direction) {
  o->acceleration.x = direction * 0.05 * sinf(o->position.r);
  o->acceleration.y = direction * 0.05 * cosf(o->position.r);
}

void game_delete() {
  return;
  //TODO
  /*
	list_reset(game->objects);
	Object* o;
	for(o = list_next(game->objects); o != NULL; o = list_next(game->objects))
		delete_object(o);
		
	delete_list(game->objects);
	free(game);
	*/
}

/*
void accelerate_object(Object* o, float linear) {
	o->acceleration.x = linear * sinf(o->position.r);
	o->acceleration.y = linear * cosf(o->position.r);
}
*/
