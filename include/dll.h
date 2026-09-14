
#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

typedef enum ret_types {
	pass = 0,
	fail = -1
} ret_types_e;

typedef struct node
{
	struct node *prev;
	uint8_t data;
	struct node *next;
} node_t;

typedef struct Dlist {
	node_t *head;
	node_t *tail;
} Dlist_t;

void display_dll(Dlist_t);
ret_types_e convertStrDll(char*, Dlist_t*);

#endif
