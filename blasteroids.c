#include "blasteroids.h"

/*const int BOUNCER_SIZE = 32;*/
enum MYKEYS {
	KEY_UP, 
	KEY_DOWN, 
	KEY_LEFT, 
	KEY_RIGHT, 
	KEY_SPACE,
	KEYCOUNT
};

int main(int argc, char** argv){
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	Spaceship* ship = NULL;
/*	ALLEGRO_BITMAP *bouncer = NULL;*/
/*	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;*/
/*	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;*/
/*	float bouncer_dx = -4.0, bouncer_dy = 4.0;*/
	bool key[KEYCOUNT] = {false};
	bool redraw = true;
	bool doexit = false;

	if(!al_init())
		error("Failed to initialize allegro");
	
/*	if(!al_install_mouse()) {*/
/*		error("Failed to initialize the mouse");*/
/*	}*/

	if(!al_install_keyboard())
		error("Failed to initialize the keyboard");
	
	timer = al_create_timer(1.0 / FPS);
	if(!timer)
		error("Failed to create timer");

	display = al_create_display(SCREEN_X, SCREEN_Y);
	if(!display)
		error("Failed to create display");

/*	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);*/
/*	if(!bouncer) {*/
/*		al_destroy_display(display);*/
/*		al_destroy_timer(timer);*/
/*		error("Failed to create bouncer bitmap");*/
/*	}*/
	
/*	al_set_target_bitmap(bouncer);*/
/*	*/
/*	al_clear_to_color(al_map_rgb(255, 0, 255));*/
/*	*/
/*	al_set_target_bitmap(al_get_backbuffer(display));*/
	
	event_queue = al_create_event_queue();
	if(!event_queue)
		error("Failed to create event queue");
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
/*	al_register_event_source(event_queue, al_get_mouse_event_source());*/
	
	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();
	
	al_start_timer(timer);
	
	ship = create_ship();
	
	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER) {
/*			if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {*/
/*				bouncer_dx = -bouncer_dx;*/
/*			}*/
/*			*/
/*			if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {*/
/*				bouncer_dy = -bouncer_dy;*/
/*			}*/
/*			*/
/*			bouncer_x += bouncer_dx;*/
/*			bouncer_y += bouncer_dy;*/
			if(key[KEY_UP]) {
				ship->accel = -1;
			}
			
			if(key[KEY_DOWN]) {
				ship->accel = 1;
			}
			
			if(key[KEY_LEFT]) {
				ship->rotate = -1;
			}
			
			if(key[KEY_RIGHT]) {
				ship->rotate = 1;
			}
			
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;
				
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;
				
				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;
				
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				
				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					ship->accel = 0;
					break;
				
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					ship->accel = 0;
					break;
				
				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					ship->rotate = 0;
					break;
				
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					ship->rotate = 0;
					break;
					
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
			}
		}
/*		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {*/
/*			bouncer_x = ev.mouse.x;*/
/*			bouncer_y = ev.mouse.y;*/
/*		}*/
/*		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {*/
/*			break;*/
/*		}*/

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			draw_ship(ship);
			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(ship->bitmap, ship->x, ship->y, 0);
/*			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);*/
			al_flip_display();
		}
	}
	
/*	al_destroy_bitmap(bouncer);*/
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	return 0;
}
