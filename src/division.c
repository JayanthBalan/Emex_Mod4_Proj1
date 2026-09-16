
#include "apc.h"

static void normalize(Dlist_t *list) {
    node_t *tnode;

    while(list->count > 1 && list->head->data == 0) {
        tnode = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(tnode);
        list->count--;
    }

    list->tail = list->head;
    while(list->tail != NULL && list->tail->next != NULL) {
        list->tail = list->tail->next;
    }
}

ret_types_e division(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    Dlist_t rem = {0};
    Dlist_t temp = {0};
    node_t *tnode = x->head;
    uint8_t qdigit;

    if(y->count == 1 && y->head->data == 0) {
        fprintf(stderr, "%s>>> Division by zero\n", __FILE__);
        return fail;
    }

    z->sign = (x->sign == y->sign) ? plus : minus;

    while(tnode != NULL) {
        if(insert_end(&rem, tnode->data) == fail) {
            freeAllNodes(&rem);
            return fail;
        }

        normalize(&rem);
        qdigit = 0;

        while(dllCompare(&rem, y) >= 0) {
            freeAllNodes(&temp);

            if(subtractBase(&rem, y, &temp) == fail) {
                freeAllNodes(&rem);
                freeAllNodes(&temp);
                return fail;
            }

            freeAllNodes(&rem);
            rem = temp;
            temp = (Dlist_t){0};
            qdigit++;
        }

        if(insert_end(z, qdigit) == fail) {
            freeAllNodes(&rem);
            freeAllNodes(&temp);
            return fail;
        }

        tnode = tnode->next;
    }

    normalize(z);

    if(z->count == 1 && z->head->data == 0) {
        z->sign = plus;
    }

    freeAllNodes(&rem);
    freeAllNodes(&temp);

    return pass;
}
