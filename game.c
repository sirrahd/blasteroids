#include <stdlib.h>
#include "game.h"

Game* game = NULL;

Game* new_game() {
	game = malloc(sizeof(Game));

	game->resolution.x = 640;
	game->resolution.y = 480;
	game->lives = 3;
	game->objects = new_list();
	game->ship = new_spaceship();
	
	int i;
	for (i = 0; i < 5; i++)
		new_asteroid();
}

void draw_screen() {
	Object* o;
	for(o = list_next(game->objects); o != NULL; o = list_next(game->objects)) {
		move_object(o);
		
		draw_object(o, o->position.x, o->position.y);
		if (o->position.x + o->structure.size / 2 > game->resolution.x)
			draw_object(o, o->position.x - game->resolution.x, o->position.y);
		else if (o->position.x - o->structure.size / 2 < 0)
			draw_object(o, o->position.x + game->resolution.x, o->position.y);
		if (o->position.y + o->structure.size / 2 > game->resolution.y)
			draw_object(o, o->position.x, o->position.y - game->resolution.y);
		else if (o->position.y - o->structure.size / 2 < 0)
			draw_object(o, o->position.x, o->position.y + game->resolution.y);
		
		// State
		if (o->state.time > 0)
			o->state.time -= 1;
		else
			object_state_transition(o);
	}
}
	
/*
void delete_game() {
	list_reset(game->objects);
	Object* o;
	for(o = list_next(game->objects); o != NULL; o = list_next(game->objects))
		delete_object(o);
		
	delete_list(game->objects);
	free(game);
}
*/
