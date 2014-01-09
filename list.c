#include "blasteroids.h"

/*typedef struct Object {*/
/*	int id;*/
/*	union {*/
/*	Asteroid* asteroid;*/
/*	Spaceship* spaceship;*/
/*	} object;*/
/*	struct Object* next;*/
/*} Object;*/

/*static Object* first = NULL;*/
/*static Object* last = NULL;*/

/*void add_to_list(Object* o) {*/
/*	static int nextId = 0;*/
/*	o->id = nextId;*/
/*	nextId++;*/
/*	*/
/*	if (!first) {*/
/*		first = o;*/
/*		last = o;*/
/*		o->next = NULL;*/
/*	}*/
/*	else {*/
/*		last->next = o;*/
/*		last = o;*/
/*	}*/
/*}*/

/*void add_ship(Spaceship* o) {*/
/*	Object* obj = malloc(sizeof(Object));*/
/*	obj->object.spaceship = o;*/
/*	obj->next = NULL;*/
/*	obj->id = 0;*/
/*	add_to_list(obj);*/
/*}*/

/*void add_asteroid(Asteroid* o) {*/
/*	Object* obj = malloc(sizeof(Object));*/
/*	obj->object.asteroid = o;*/
/*	obj->next = NULL;*/
/*	obj->id = 0;*/
/*	add_to_list(obj);*/
/*}*/


