
#include "apc.h"

ret_types_e addition(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    if(x->sign == minus && y->sign == minus) {
        z->sign = minus;
    }
    else if((x->sign == minus || y->sign == minus)) {
        int comp = dllCompare(x, y);
        if(x->sign == minus) {
            if(comp == -1) {
                z->sign = plus;
                return subtractBase(y, x, z);
            }
            else if(comp == 1) {
                z->sign = minus;
                return subtractBase(x, y, z);
            }
            else {
                z->sign = plus;
                return insert_beg(z, 0);
            }
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
    }
    else {
        z->sign = plus;
    }

    return addBase(x, y, z);
}

ret_types_e addBase(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    node_t *ux = x->tail, *uy = y->tail;
    uint8_t carry = 0, sum = 0;

    while(ux != NULL || uy != NULL || carry != 0) {
        sum = carry;
        sum += (ux != NULL) ? ux->data : 0;
        sum += (uy != NULL) ? uy->data : 0;
        carry = sum/10;
        sum %= 10;
        
        if(insert_beg(z, sum) == fail) {
            return fail;
        }

        ux = ux->prev;
        uy = uy->prev;
    }

    return pass;
}

ret_types_e addBase2(Dlist_t y, Dlist_t *z) {
    node_t *uy = y.tail;
    uint8_t carry = 0, sum = 0;

    Dlist_t x = {0};
    node_t *ux, *tnode = z->head;
    for(; tnode != NULL; tnode = tnode->next) {
        if(insert_end(&x, tnode->data) == fail) {
            return fail;
        }
    }
    ux = x.head;
    if(freeAllNodes(&z->head, &z->tail) == fail) {
        return fail;
    }

    while(ux != NULL || uy != NULL || carry != 0) {
        sum = carry;
        sum += (ux != NULL) ? ux->data : 0;
        sum += (uy != NULL) ? uy->data : 0;
        carry = sum/10;
        sum %= 10;
        
        if(insert_beg(z, sum) == fail) {
            return fail;
        }

        ux = ux->prev;
        uy = uy->prev;
    }

    return pass;
}
