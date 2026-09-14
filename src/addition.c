
#include "apc.h"

ret_types_e addition(Dlist_t *x, Dlist_t *y, Dlist_t* sum) {
    if(x->tail->data == '-' || y->tail->data == '-') {
        return subtraction(x, y, sum);
    }

    node_t *ux = x->tail, *uy = y->tail;
    node_t *st_node;

    while()

    return pass;
}
