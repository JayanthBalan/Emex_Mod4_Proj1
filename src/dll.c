
#include "dll.h"

void display_dll(Dlist_t dll) {
    node_t *tnode;
    if(dll.sign == minus) {
        fprintf(stdout, "-");
    }
    for(tnode = dll.head; tnode != NULL; tnode = tnode->next) {
        fprintf(stdout, "%c", (char)tnode->data);
    }
}

ret_types_e insert_end(Dlist_t *target, uint8_t data) {
    if(target->head == NULL || target->tail == NULL) {
        target->head = (node_t*)malloc(sizeof(node_t));
        if(target->head == NULL) {
            return fail;
        }

        target->head->data = data;
        target->head->next = NULL;
        target->head->prev = NULL;
        target->tail = target->head;

        return pass;
    }

    node_t *tnode = (node_t*)malloc(sizeof(node_t));
    if(tnode == NULL) {
        return fail;
    }
    
    tnode->data = data;
    tnode->prev = target->tail;
    tnode->next = NULL;
    
    target->tail->next = tnode;
    target->tail = target->tail->next;

    return pass;
}

ret_types_e insert_beg(Dlist_t *target, uint8_t data) {
    if(target->head == NULL || target->tail == NULL) {
        target->head = (node_t*)malloc(sizeof(node_t));
        if(target->head == NULL) {
            return fail;
        }

        target->head->data = data;
        target->head->next = NULL;
        target->head->prev = NULL;
        target->tail = target->head;

        return pass;
    }

    node_t *tnode = (node_t*)malloc(sizeof(node_t));
    if(tnode == NULL) {
        return fail;
    }
    
    tnode->data = data;
    tnode->next = target->head;
    tnode->prev = NULL;
    
    target->head->prev = tnode;
    target->head = target->head->prev;

    return pass;
}

ret_types_e convertStrDll(char *data, Dlist_t *conv_list) {
    conv_list->head = (node_t*)malloc(sizeof(node_t));
    if(conv_list->head == NULL) {
        return fail;
    }
    if(*data == 0) {
        return fail;
    }

    int i = 0;
    if(data[i] == '+' || data[i] == '-') {
        i++;
    }
    for(; data[i] == '0'; i++);

    conv_list->head->data = (uint8_t)data[i];
    conv_list->head->next = NULL;
    conv_list->head->prev = NULL;
    conv_list->count = 1;

    if(data[0] == '-') {
        conv_list->sign = minus;
    }
    else {
        conv_list->sign = plus;
    }

    node_t *tnode, *root = conv_list->head;
    for(; data[i] != 0; i++) {
        if(data[i] != '+' && data[i] != '-' && (data[i] < '0' || data[i] > '9')) {
            return fail;
        }

        tnode = (node_t*)malloc(sizeof(node_t));
        if(tnode == NULL) {
            return fail;
        }
        tnode->data = (uint8_t)data[i];
        tnode->next = NULL;
        tnode->prev = root;

        root->next = tnode;
        root = root->next;

        conv_list->count++;
    }
    conv_list->tail = root;

    if(conv_list->count == 1 && (conv_list->head->data == '+' || conv_list->head->data == '-')) {
        return fail;
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
        node_t *xnode = x->head->data, *ynode = y->head->data;
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

ret_types_e freeAllNodes(node_t **head, node_t **tail) {
    if(*head == NULL || *tail == NULL) {
        return pass;
    }

    node_t *hnode = *head, *tnode = *tail;
    for(; hnode != tnode; hnode = hnode->next, tnode = tnode->prev) {
        free(hnode);
        free(tnode);
        hnode->prev = NULL;
        tnode->next = NULL;
    }
    free(hnode);
    hnode->prev = NULL;
    tnode->next = NULL;

    return pass;
}
