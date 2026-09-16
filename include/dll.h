
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

typedef enum signType {
	minus = -1,
	plus = 1
} signType_e;

typedef struct node
{
	struct node *prev;
	uint8_t data;
	struct node *next;
} node_t;

typedef struct Dlist {
	node_t *head;
	node_t *tail;
	unsigned int count;
	signType_e sign;
} Dlist_t;

void display_dll(Dlist_t);
ret_types_e convertStrDll(char*, Dlist_t*);
ret_types_e insert_beg(Dlist_t*, uint8_t);
ret_types_e insert_end(Dlist_t*, uint8_t);
int dllCompare(Dlist_t*, Dlist_t*);
ret_types_e freeAllNodes(node_t**, node_t**);

#endif
