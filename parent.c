#include "tree_based_quadrants.h"

void
parent (const quadrant_t * q, quadrant_t * parent_quadrant)
{
    if ( q->level == 0 ) {
        printf("The root has no parent quadrant");
        return;
    } 
    // level of the parent decreases by 1
    parent_quadrant->level = q->level - 1;
    // we compute the size
    int h = QUADRANT_LEN(q->level);
    // compute parent coordinates
    parent_quadrant->x = q->x & ~h;
    parent_quadrant->y = q->y & ~h;
    parent_quadrant->z = q->z & ~h;
    return;
}