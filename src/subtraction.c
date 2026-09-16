
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
    int8_t carry = 0, diff = 0;

    while(ux != NULL || uy != NULL || carry != 0) {
        diff = (int8_t)((ux != NULL) ? ux->data : 0);
        diff -= (int8_t)carry;
        diff -= (int8_t)((uy != NULL) ? uy->data : 0);
        carry = (diff < 0) ? 1 : 0;
        diff = (diff < 0) ? (diff + 10) : diff;
        
        if(insert_beg(z, (uint8_t)diff) == fail) {
            return fail;
        }

        ux = ux->prev;
        uy = uy->prev;
    }

    return pass;
}
