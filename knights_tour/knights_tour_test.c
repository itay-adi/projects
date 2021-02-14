#include <stdio.h>
#include <stdlib.h>

#include "knights_tour.h"

int main(void)
{
    size_t len = 8;
    size_t i = 0;
    size_t j = 0;
    size_t index = 0;
    point_t *LUT = NULL;

    LUT = (point_t *)calloc(len * len, sizeof(point_t));

    if(NULL == LUT)
    {
        return (1);
    }

    LUT = KnightsTourWar(0, 0, len, LUT);

    if(LUT)
    {
        for(i = 0; i < len; ++i)
        {
            for(j = 0; j < len; ++j)
            {
                index = BitNum(j, i, len);
                printf("%ld: ", index);
                printf("(%d, %d)- ", LUT[index].x, LUT[index].y);
            }

            printf("\n");
        }
    }

    else
    {
        printf("No valid solution.\n");
    }
    
    free(LUT);
    LUT = NULL;

    return (0);
}
