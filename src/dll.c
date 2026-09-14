
#include "dll.h"

void display_dll(Dlist_t *dll) {
    node_t *tnode;
    for(tnode = dll->head; tnode != NULL; tnode = tnode->next) {
        fprintf(stdout, "%hhu", tnode->data);
    }
}

ret_types_e convertStrDll(char *data, Dlist_t *conv_list) {
    conv_list->head = (node_t*)malloc(sizeof(node_t));
    if(conv_list->head == NULL) {
        return fail;
    }
    if(*data == 0) {
        return fail;
    }

    conv_list->head->data = data[0];
    conv_list->head->next = NULL;
    conv_list->head->prev = NULL;

    node_t *tnode, *root = conv_list->head;
    for(int i = 1; data[i] != 0; i++) {
        tnode = (node_t*)malloc(sizeof(node_t));
        if(tnode == NULL) {
            return fail;
        }
        tnode->data = data[i];
        tnode->next = NULL;
        tnode->prev = root;

        root->next = tnode;
        root = root->next;
    }

    return pass;
}
