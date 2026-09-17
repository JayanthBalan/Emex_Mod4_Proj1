
#include "dll.h"

static int zeroCheck(Dlist_t list) {
    if(list.head != NULL && list.head == list.tail && list.head->data == 0) {
        return 1;
    }

    return 0;
}

void display_dll(Dlist_t dll) {
    node_t *tnode;
    if(dll.sign == minus && zeroCheck(dll) != 0) {
        fprintf(stdout, "-");
    }
    for(tnode = dll.head; tnode != NULL; tnode = tnode->next) {
        fprintf(stdout, "%c", (char)(tnode->data + '0'));
    }
    fprintf(stdout, "\n");
}

ret_types_e insert_end(Dlist_t *target, uint8_t data) {
    node_t *tnode;

    tnode = (node_t*)malloc(sizeof(node_t));
    if(tnode == NULL) {
        return fail;
    }

    tnode->data = data;
    tnode->next = NULL;
    tnode->prev = target->tail;

    if(target->head == NULL) {
        target->head = tnode;
        target->tail = tnode;
    }
    else {
        target->tail->next = tnode;
        target->tail = tnode;
    }

    target->count++;

    return pass;
}

ret_types_e insert_beg(Dlist_t *target, uint8_t data) {
    node_t *tnode;

    tnode = (node_t*)malloc(sizeof(node_t));
    if(tnode == NULL) {
        return fail;
    }

    tnode->data = data;
    tnode->prev = NULL;
    tnode->next = target->head;

    if(target->head == NULL) {
        target->head = tnode;
        target->tail = tnode;
    }
    else {
        target->head->prev = tnode;
        target->head = tnode;
    }

    target->count++;

    return pass;
}

ret_types_e convertStrDll(char *data, Dlist_t *conv_list) {
    int i = 0;

    if(data == NULL || *data == '\0') {
        return fail;
    }

    if(data[i] == '+' || data[i] == '-') {
        if(data[i] == '-') {
            conv_list->sign = minus;
        }
        else {
            conv_list->sign = plus;
        }
        i++;
    }
    else {
        conv_list->sign = plus;
    }

    if(data[i] == '\0') {
        return fail;
    }

    for(; data[i] != '\0'; i++) {
        if(data[i] < '0' || data[i] > '9') {
            return fail;
        }
    }

    i = 0;

    if(data[0] == '+' || data[0] == '-') {
        i++;
    }

    for(; data[i] == '0' && data[i + 1] != '\0'; i++);

    for(; data[i] != '\0'; i++) {
        if(insert_end(conv_list, (uint8_t)(data[i] - '0')) == fail) {
            freeAllNodes(conv_list);
            return fail;
        }
    }

    if(conv_list->count == 1 && conv_list->head->data == 0) {
        conv_list->sign = plus;
    }

    return pass;
}

int dllCompare(Dlist_t *x, Dlist_t *y) {
    if(x->count < y->count) {
        return -1;
    }
    else if(x->count > y->count) {
        return 1;
    }
    else {
        node_t *xnode = x->head, *ynode = y->head;
        while(xnode != NULL && ynode != NULL) {
            if(xnode->data > ynode->data) {
                return 1;
            }
            else if(xnode->data < ynode->data) {
                return -1;
            }
            else {
                xnode = xnode->next;
                ynode = ynode->next;
            }
        }
    }
    return 0;
}

void freeAllNodes(Dlist_t *list) {
    if(list->head == NULL) {
        return;
    }

    node_t *tnode = list->head;
    while(list->head != NULL) {
        list->head = list->head->next;
        free(tnode);
        tnode = list->head;
    }

    list->count = 0;
    list->tail = NULL;
}
