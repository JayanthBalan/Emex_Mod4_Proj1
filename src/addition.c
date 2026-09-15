
#include "apc.h"

ret_types_e addition(Dlist_t *x, Dlist_t *y, Dlist_t* z) {
    if(x->sign == '-' && y->sign == '-') {
        z->sign = minus;
    }
    else if((x->sign == '-' || y->sign == '-')) {
        if(x->sign == '-') {
            if(x->count < y->count) {
                z->sign = plus;
                return subtraction(x, y, z);
            }
            else if(x->count > y->count) {
                z->sign = minus;
                return subtraction(x, y, z);
            }
            else {
                node_t *xnode = x->head->data, *ynode = y->head->data;
                while(xnode != NULL && ynode != NULL) {
                    if(xnode->data > ynode->data) {
                        z->sign = minus;
                        break;
                    }
                    else if(xnode->data < ynode->data) {
                        z->sign = plus;
                        break;
                    }
                    else {
                        xnode = xnode->next;
                        ynode = ynode->next;
                    }
                }
                return subtraction(x, y, z);
            }
        }
        else {
            if(y->count < x->count) {
                z->sign = plus;
                return subtraction(x, y, z);
            }
            else if(y->count > x->count) {
                z->sign = minus;
                return subtraction(x, y, z);
            }
            else {
                node_t *ynode = y->head->data, *xnode = x->head->data;
                while(ynode != NULL && xnode != NULL) {
                    if(ynode->data > xnode->data) {
                        z->sign = minus;
                        break;
                    }
                    else if(ynode->data < xnode->data) {
                        z->sign = plus;
                        break;
                    }
                    else {
                        xnode = xnode->next;
                        ynode = ynode->next;
                    }
                }
                return subtraction(x, y, z);
            }
        }
    }
    else {
        z->sign = plus;
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
