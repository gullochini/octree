#include "tree_based_quadrants.h"

int child_id (const quadrant_t *q) {
	int res = 0;
	res += (q->x & QUADRANT_LEN(q->level) ? 1 : 0);
	res += ((q->y & QUADRANT_LEN(q->level) ? 1 : 0) << 1);
	res += ((q->z & QUADRANT_LEN(q->level) ? 1 : 0) << 2);
	
	return res;
}

void
root (quadrant_t * q)
{
  q->level = 0;
  q->x = q->y = q->z = 0;
}

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

void child (const quadrant_t * q, quadrant_t * child_quadrant,
                           int child_id)
{
    child_quadrant->level = q->level + 1;

    child_quadrant->x = q->x + (child_id & 1 ? QUADRANT_LEN(child_quadrant->level) : 0);

    child_quadrant->y = q->y + (child_id & 2 ? QUADRANT_LEN(child_quadrant->level) : 0);

    child_quadrant->z = q->z + (child_id & 4 ? QUADRANT_LEN(child_quadrant->level) : 0);

}

void
sibling(const quadrant_t* q, quadrant_t* sibling_quadrant, int sibling_id)
{
#if 0
	if (!is_valid(q)) {
		printf("sibling: the input quadrant has to be valid.\n");
		return;
	}
#endif
	if (sibling_id < 0 || sibling_id > 7) {
		printf
		("sibling: sibling_id should lie between 0 (included) \
        and 7 (included).\n");
		return;
	}

	sibling_quadrant->level = q->level;
	// we compute the size
	int h = QUADRANT_LEN(q->level);
	// compute parent coordinates
	sibling_quadrant->x = (sibling_id & 1) ? (q->x | h) : (q->x & ~h);
	sibling_quadrant->y = (sibling_id & 2) ? (q->y | h) : (q->y & ~h);
	sibling_quadrant->z = (sibling_id & 4) ? (q->z | h) : (q->z & ~h);
}

void
first_descendant(const quadrant_t* q, quadrant_t* first_descendant, int level)
{
#if 0
	if (!is_valid(q)) {
		printf("first_descendant: the input quadrant has to be valid.\n");
		return;
	}
#endif
	if ((int)q->level > level || level >= MAXLEVEL) {
		printf
		("first_descendant: level should lie between quadrant level (included) \
        and MAXLEVEL (excluded).\n");
		return;
	}

	first_descendant->x = q->x;
	first_descendant->y = q->y;
	first_descendant->z = q->z;

	first_descendant->level = (int8_t)level;
}

void
last_descendant (const quadrant_t * q, quadrant_t * last_descendant,
                 int level)
{
  qcoord_t            shift;

#if 0
  if (!is_valid (q)) {
    printf ("last_descendant: the input quadrant has to be valid.\n");
    return;
  }
#endif
  if ((int) q->level > level && level >= MAXLEVEL) {
    printf
      ("last_descendant: level should lie between quadrant level (included) \
        and MAXLEVEL (excluded).\n");
    return;
  }

  shift = QUADRANT_LEN (q->level) - QUADRANT_LEN (level);

  last_descendant->x = q->x + shift;
  last_descendant->y = q->y + shift;
  last_descendant->z = q->z + shift;

  last_descendant->level = (int8_t) level;
}
