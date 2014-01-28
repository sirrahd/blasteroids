#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

enum MYKEYS {
	KEY_UP, 
	KEY_DOWN, 
	KEY_LEFT, 
	KEY_RIGHT, 
	KEY_SPACE,
	KEYCOUNT
};

const float FPS = 60;
const float SCREEN_X = 640;
const float SCREEN_Y = 480;

int done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;

void shutdown() {
	return;
}

void abort_game(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init() {
	if(!al_init())
		abort_game("Failed to initialize allegro");
	
	if(!al_install_keyboard())
		abort_game("Failed to initialize the keyboard");

	timer = al_create_timer(1.0 / FPS);
	if(!timer)
		abort_game("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(SCREEN_X, SCREEN_Y);
	if(!display)
		abort_game("Failed to create display");

	event_queue = al_create_event_queue();
	if(!event_queue)
		error("Failed to create event queue");

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	done = false;
}

void game_loop() {
	int redraw = true;
	al_start_timer(timer);
	int key[KEYCOUNT] = {false};
	
	srand((unsigned)time(NULL));
	
	new_game();
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		
		if (event.type == ALLEGRO_EVENT_TIMER) {
			if(key[KEY_UP]) {
				if (game->ship)
					accelerate_object(game->ship, 0.2);
			}
			
			if(key[KEY_DOWN]) {
				if (game->ship)
					accelerate_object(game->ship, -0.2);
			}
			
			if(key[KEY_UP] && key[KEY_DOWN]) {
				if (game->ship)
					accelerate_object(game->ship, 0.0);
			}
			
			if(key[KEY_LEFT]) {
				if (game->ship)
					rotate_object(game->ship, -1.0);
			}
			
			if(key[KEY_RIGHT]) {
				if (game->ship)
					rotate_object(game->ship, 1.0);
			}
			
			if(key[KEY_RIGHT] && key[KEY_LEFT]) {
				if (game->ship)
					rotate_object(game->ship, 0.0);
			}
			
			if(key[KEY_SPACE]) {
				if (game->ship)
					new_blast(game->ship);
			}
			
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}

		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					key[KEY_UP] = true;
					break;
				
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					key[KEY_DOWN] = false;//true;
					break;
				
				case ALLEGRO_KEY_LEFT:
				case ALLEGRO_KEY_A:
					key[KEY_LEFT] = true;
					break;
				
				case ALLEGRO_KEY_RIGHT:
				case ALLEGRO_KEY_D:
					key[KEY_RIGHT] = true;
					break;
				
				case ALLEGRO_KEY_SPACE:
				case ALLEGRO_KEY_ENTER:
					key[KEY_SPACE] = true;
					break;
			}
		}
		else if(event.type == ALLEGRO_EVENT_KEY_UP) {
			switch(event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
			case ALLEGRO_KEY_W:
				key[KEY_UP] = false;
				if (game->ship)
					accelerate_object(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				key[KEY_DOWN] = false;
				if (game->ship)
					accelerate_object(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_A:
				key[KEY_LEFT] = false;
				if (game->ship)
					rotate_object(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = false;
				if (game->ship)
					rotate_object(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_SPACE:
			case ALLEGRO_KEY_ENTER:
				key[KEY_SPACE] = false;
				break;
				
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		
		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0,0,0));
			draw_screen();
			al_flip_display();
		}
	}
}

int main(int argc, char** argv){
	init();
	game_loop();
	shutdown();
	
	return 0;
}
