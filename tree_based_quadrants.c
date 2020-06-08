#include "tree_based_quadrants.h"

int
parent (const quadrant_t * q, quadrant_t * parent_quadrant)
{
    if (!is_valid(q)) {
        printf("parent: the input quadrant is not valid");
        return -1;
    }
    if ( q->level == 0 ) {
        printf("The root has no parent quadrant");
        return -1;
    }
    // level of the parent decreases by 1
    parent_quadrant->level = q->level - 1;
    // compute the size and its bitwise negation
    int h = QUADRANT_LEN(q->level);
    int not_h = ~h;
    // compute coordinates of parent quadrant
    parent_quadrant->x = q->x & not_h;
    parent_quadrant->y = q->y & not_h;
    parent_quadrant->z = q->z & not_h;
    return 1;
}

int
is_parent (const quadrant_t * q, const quadrant_t * p)
{
    quadrant_t parent_p;
    // we compute the parent of p
    parent( p, &parent_p);
    // we return true if q is the parent of p
    return is_equal( &parent_p, q );
}
