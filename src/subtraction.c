
#include "apc.h"

ret_types_e subtraction(Dlist_t *x, Dlist_t *y, Dlist_t *z) {
    if((x->head->data == '-' && y->head->data != '-') || (x->head->data != '-' && y->head->data == '-')) {
        
    }

    node_t *ux = x->tail, *uy = y->tail;
    node_t *st_node;
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
    }

    return pass;
}
