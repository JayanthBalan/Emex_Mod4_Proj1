
#include "apc.h"

ret_types_e subtraction(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    int comp = dllCompare(x, y);
    if(x->sign == minus && y->sign == minus) {
        if(comp == 1) {
            z->sign = minus;
        }
        else if(comp == -1) {
            z->sign = plus;
        }
        else {
            z->sign = plus;
            return insert_beg(z, 0);
        }
    }
    else if(x->sign == minus && y->sign == plus) {
        z->sign = minus;
        return addBase(x, y, z);
    }
    else if(y->sign == minus && x->sign == plus) {
        z->sign = plus;
        return addBase(x, y, z);
    }
    else {
        if(comp == 1) {
            z->sign = plus;
            return subtractBase(x, y, z);
        }
        else if(comp == -1) {
            z->sign = minus;
            return subtractBase(y, x, z);
        }
        else {
            z->sign = plus;
            return insert_beg(z, 0);
        }
    }

    return fail;
}

ret_types_e subtractBase(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    node_t *ux = x->tail, *uy = y->tail;
    int8_t borrow = 0, diff = 0;

    while(ux != NULL || uy != NULL || borrow != 0) {
        diff = (int8_t)((ux != NULL) ? ux->data : 0);
        diff -= (int8_t)borrow;
        diff -= (int8_t)((uy != NULL) ? uy->data : 0);
        borrow = (diff < 0) ? 1 : 0;
        diff = (diff < 0) ? (diff + 10) : diff;
        
        if(insert_beg(z, (uint8_t)diff) == fail) {
            return fail;
        }

        if(ux != NULL) {
            ux = ux->prev;
        }
        if(uy != NULL) {
            uy = uy->prev;
        }
    }

    return pass;
}

ret_types_e subtractBase2(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    ret_types_e retno;

    retno = subtractBase(x, y, z);
    if(retno == fail) {
        return fail;
    }

    while(z->count > 1 && z->head->data == 0) {
        node_t *tnode = z->head;
        z->head = z->head->next;
        z->head->prev = NULL;
        free(tnode);
        z->count--;
    }

    z->tail = z->head;
    while(z->tail != NULL && z->tail->next != NULL) {
        z->tail = z->tail->next;
    }

    return pass;
}
