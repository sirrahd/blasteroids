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

const float FPS = 120;
const float RATE = 60;
const float SCREEN_X = 1024;
const float SCREEN_Y = 768;

int done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;
ALLEGRO_THREAD* thread_calc;

void shutdown() {
	return;
}

void abort_game(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

static void* tCalc(ALLEGRO_THREAD* thread, void* arg) {
  while(!done) {
    Game* game = (Game*) arg;
    
    al_lock_mutex(game->mutex);
    game_move(game);
    al_unlock_mutex(game->mutex);
    
    al_rest(1.0 / RATE);
  }
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

void loop() {
	int redraw = true;
	al_start_timer(timer);
	int key[KEYCOUNT] = {false};
	
	srand((unsigned)time(NULL));
	
	Game* game = game_new(SCREEN_X, SCREEN_Y);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	game->mutex = al_create_mutex();
	thread_calc = al_create_thread(tCalc, game);
	al_start_thread(thread_calc);

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		
		if (event.type == ALLEGRO_EVENT_TIMER) {
		  if(key[KEY_UP]) {
			  if (game->ship)
				  ship_accelerate(game->ship, 1);
		  }
		
		  if(key[KEY_DOWN]) {
			  if (game->ship)
				  ship_accelerate(game->ship, -1);
		  }
		
		  if(key[KEY_UP] && key[KEY_DOWN]) {
			  if (game->ship)
				  ship_accelerate(game->ship, 0);
		  }
		
		  if(key[KEY_LEFT]) {
			  if (game->ship)
				  ship_rotate(game->ship, -1);
		  }
		
		  if(key[KEY_RIGHT]) {
			  if (game->ship)
				  ship_rotate(game->ship, 1);
		  }
		
		  if(key[KEY_RIGHT] && key[KEY_LEFT]) {
			  if (game->ship)
				  ship_rotate(game->ship, 0);
		  }
		
		  if(key[KEY_SPACE]) {
			  if (game->ship)
				  //TODO
				  continue;
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
					key[KEY_DOWN] = true;
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
					ship_accelerate(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:
				key[KEY_DOWN] = false;
				if (game->ship)
					ship_accelerate(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_LEFT:
			case ALLEGRO_KEY_A:
				key[KEY_LEFT] = false;
				if (game->ship)
					ship_rotate(game->ship, 0);
				break;
			
			case ALLEGRO_KEY_RIGHT:
			case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = false;
				if (game->ship)
					ship_rotate(game->ship, 0);
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
      al_lock_mutex(game->mutex);
		  game_draw(game);
      al_unlock_mutex(game->mutex);
		  al_flip_display();
		}
	}
}  

int main(int argc, char** argv){
	init();
	loop();
	shutdown();
	
	return 0;
}
