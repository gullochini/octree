#include "parent.h"

element parent( element e)
{
    int h = ( 2 <<  ( L - e.level ) ) ;
    element parent;
    parent.level = e.level - 1; 
    parent.x = e.x & ~h ;
    parent.y = e.y & ~h ;
    parent.z = e.z & ~h ;
    return parent;
}