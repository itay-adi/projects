#include <stdio.h>

#include "knights_tour.h"

/******************************************************************************/

int KnightsTour_Rec(int x, int y, size_t len, point_t *LUT, int frame, size_t steps, int *x_move, int *y_move);
int KnightsTourWar_Rec(int x, int y, size_t len, point_t *LUT, int frame, size_t steps, int *x_move, int *y_move);
void SetLUT(point_t *LUT, int index, int x, int y);
int IsPointValid(int x, int y, size_t len, size_t steps_ptr);

int MovesCount(int x, int y, int *x_move, int *y_move, size_t steps, size_t len);
point_t FindNextMove(int x, int y, int *x_move, int *y_move, size_t *bit_arr, size_t len, size_t steps);

/******************************************************************************/

int IsOutOfFrame(int x, int y, int len)
{
    return (!(x >= 0 && x < len && y >= 0 && y <len));
}

/******************************************************************************/

int BitNum(int x, int y, int x_len)
{
    return (y * x_len + x);
}

/******************************************************************************/

point_t *KnightsTour(int x, int y, int len, point_t *LUT)
{
    size_t steps = 0;
    
    int x_move[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int y_move[8] = {1, 2,  2,  1, -1, -2, -2, -1};
    int index = BitNum(x, y, len) + 1;

    if(!IsOutOfFrame(x, y, len))
    {
        SetLUT(LUT, 0, x, y);
        steps = BitArrSetOn(steps, index);
        if (KnightsTour_Rec(x, y, len, LUT, 1, steps, x_move, y_move))
        {
            return (LUT);
        }
    }

    return (NULL);
}

/******************************************************************************/

int KnightsTour_Rec(int x, int y, size_t len, point_t *LUT, int frame, size_t steps, int *x_move, int *y_move)
{
    size_t i = 0;
    int x_add = 0;
    int y_add = 0;

    if(BitArrCountOn(steps) == (len * len))
    {
        return (1);
    }

    for(i = 0; i < 8; ++i)
    {
        x_add = x + x_move[i];
        y_add = y + y_move[i];

        if (IsPointValid(x_add, y_add, len, steps))
        {
            steps = BitArrSetOn(steps, BitNum(x_add, y_add, len) + 1);
            SetLUT(LUT, frame, x_add, y_add);

            if (KnightsTour_Rec(x_add, y_add, len, LUT, frame + 1, steps, x_move, y_move) == 1)
            {
                return (1);
            }

            else
            {
                steps = BitArrSetOff(steps, BitNum(x_add, y_add, len) + 1);
            }            
        }
    }

    return (0);
}

/******************************************************************************/

void SetLUT(point_t *LUT, int index, int x, int y)
{
    LUT[index].x = x;
    LUT[index].y = y;
}

/******************************************************************************/

int IsPointValid(int x, int y, size_t len, size_t steps)
{
    size_t index = BitNum(x, y, len) + 1;

    return(!IsOutOfFrame(x,y,len) &&
            BitArrIsOff(steps, index));
}

/******************************************************************************/

point_t *KnightsTourWar(int x, int y, int len, point_t *LUT)
{
    size_t steps = 0;
    
    int x_move[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int y_move[8] = {1, 2,  2,  1, -1, -2, -2, -1};
    int index = BitNum(x, y, len) + 1;

    if(!IsOutOfFrame(x, y, len))
    {
        SetLUT(LUT, 0, x, y);
        steps = BitArrSetOn(steps, index);
        if (KnightsTourWar_Rec(x, y, len, LUT, 1, steps, x_move, y_move))
        {
            return (LUT);
        }
    }

    return (NULL);
}

/******************************************************************************/

int KnightsTourWar_Rec(int x, int y, size_t len, point_t *LUT, int frame, size_t steps, int *x_move, int *y_move)
{
    size_t i = 0;
    int x_add = 0;
    int y_add = 0;
    point_t next = {0, 0};
    size_t local_steps = 0;

    if(BitArrCountOn(steps) == (len * len))
    {
        return (1);
    }

    for(i = 0; i < 8; ++i)
    {
        next = FindNextMove(x, y, x_move, y_move, &local_steps, len, steps);
        x_add = next.x;
        y_add = next.y;

        steps = BitArrSetOn(steps, BitNum(x_add, y_add, len) + 1);
        SetLUT(LUT, frame, x_add, y_add);

        if (KnightsTour_Rec(x_add, y_add, len, LUT, frame + 1, steps, x_move, y_move) == 1)
            {
                return (1);
            }

            else
            {
                steps = BitArrSetOff(steps, BitNum(x_add, y_add, len) + 1);
            }            
    }

    return (0);
}

/******************************************************************************/

point_t FindNextMove(int x, int y, int *x_move, int *y_move, size_t *bit_arr, size_t len, size_t steps)
{
    int i = 0;
    int count = 9;
    int place = 0;
    int curr_num = 0;
    point_t temp = {0,0};

    for (i = 0; i < 8; ++i)
    {
        temp.x = x + x_move[i];
        temp.y = y + y_move[i];

        curr_num = MovesCount(temp.x, temp.y, x_move, y_move, steps, len);

        if(IsPointValid(temp.x, temp.y, len, steps) && 
           curr_num < count && BitArrIsOff(*bit_arr, i))
            {
                place = i;
                count = curr_num;
            }     
        
    }
   
    BitArrSetOn(*bit_arr, place);

    temp.x = x + x_move[place];
    temp.y = y + y_move[place];
    
    return (temp);
}

/******************************************************************************/

int MovesCount(int x, int y, int *x_move, int *y_move, size_t steps, size_t len)
{
    int i = 0;
    int temp_x = 0;
    int temp_y = 0;
    int moves = 0;

    for (i = 0; i < 8; ++i)
    {
        temp_x = x + x_move[i];
        temp_y = y + y_move[i];

        if (IsPointValid(temp_x, temp_y, len, steps))
        {
            ++moves;
        }
    }

    return (moves);
}

/******************************************************************************/