#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// Adds an object to the beginning of the list
void list_add(List* list, void* object) { 
	Item* item = malloc(sizeof(Item));
	item->object = object;
	item->next = list->start;
	if(!list->start) {
		list->current = item;
	}
	list->start = item;
}

// Removes an object from the list.
void list_remove(List* list, void* object) {
	Item* item = NULL;
	Item* prevItem = NULL;
	
	for(item = list->start; item->object != object && item != NULL; item = item->next) {
		prevItem = item;
	}
		
	if(!item) {
		fprintf(stderr, "Tried to remove item that doesn't exist from list\n");
		exit(1);
	}
	
	if(prevItem) {
		prevItem->next = item->next;
	}
	else {
		list->start = item->next;
	}
	
	free(item);
}

// Returns the next object in the list, or NULL if end of list reached.
void* list_next(List* list) {
	void* object = NULL;
	if(list->current) {
		object = list->current->object;
		list->current = list->current->next;
	}
	else {
		list->current = list->start;
		object = NULL;
	}
	
	return object;
}

// Instantiates and returns new list
List* new_list() {
	List* list = malloc(sizeof(List));
	list->start = NULL;
	list->current = NULL;
	
	return list;
}

// Deletes list completely
void delete_list(List* list) {
	if(list->start) {
		fprintf(stderr, "Attempted list delete before list items were removed\n");
		exit(1);
	}
	
	free(list);
}
