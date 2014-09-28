#pragma once

typedef struct Item {
	void* object;
	struct Item* next;
} Item;

typedef struct {
	Item* start;
	Item* current;
} List;

List* list_new();
void list_delete(List* list);
void list_add(List* list, void* object);
void list_remove(List* list, void* object);
void* list_next(List* list);
void list_reset(List* list);
