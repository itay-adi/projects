#ifndef ILRD_KNIGHT_H
#define ILRD_KNIGHT_H

#include "bit_array.h"

typedef struct point
{
    int x;
    int y;
} point_t;

/* start - (x, y) starting point
*  optimize - 1 to use optimization, 0 otherwise
* return value - LUT array of the road (user should free memory) */
/*point_t *KnightTour(point_t start, int optimize);*/

point_t *KnightsTour(int x, int y, int len, point_t *LUT);

/*Checks if a point is out of range: 0: valid, 1: invalid*/
int IsOutOfFrame(int x, int y, int len);

/*receives a coordinate and returns its bit number*/
int BitNum(int x, int y, int x_len);

point_t *KnightsTourWar(int x, int y, int len, point_t *LUT);

#endif /* ILRD_KNIGHT_H */ 
