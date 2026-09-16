
#include "apc.h"

ret_types_e multiplication(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    if((x->sign == minus && y->sign == minus) || (x->sign == plus && y->sign == plus)) {
        z->sign = plus;
    }
    else {
        z->sign = minus;
    }

    return multiplyBase(x, y, z);
}

ret_types_e multiplyBase(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    node_t *ux, *uy = y->tail;
    uint8_t carry = 0, prod = 0;

    Dlist_t inter = {0};
    inter.head = (node_t*)malloc(sizeof(node_t));
    if(inter.head == NULL) {
        return fail;
    }
    if(insert_beg(z, 0) == fail) {
        return fail;
    }

    for(int i = 0; uy != NULL; uy = uy->prev, i++) {
        for(ux = x->tail; ux != NULL; ux = ux->prev) {
            prod = (uy->data)*(ux->data) + carry;
            carry = prod/10;
            prod %= 10;

            if(insert_beg(&inter, prod) == fail) {
                return fail;
            }
        }
        if(carry != 0) {
            if(insert_beg(&inter, carry) == fail) {
                return fail;
            }
        }
        for(int j = 0; j < i; j++) {
            if(insert_end(&inter, 0) == fail) {
                return fail;
            }
        }

        if(addBase2(inter, z) == fail) {
            return fail;
        }
        if(freeAllNodes(&inter.head, &inter.tail) == fail) {
            return fail;
        }
    }

    return pass;
}
