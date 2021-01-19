/******************************************************************************
 *                      code by : Orpaz Houta                                 *
 *                      review by : Chanan Komar                              *
 *                      coding date - 17-06-2020                              *
 ******************************************************************************/
#include <assert.h>         /* assert */
#include <malloc.h>         /* malloc */

#include "bitarray.h"       /* BitArrSetOn, BitArrGetVal */
#include "knights_tour.h"

/*-----------------------------Macros & Enums---------------------------------*/
#define ROWS (8)
#define COLUMNS (ROWS)
#define BOARD_SIZE (ROWS * COLUMNS)
#define MAX_MOVES (8)
#define ILLEGAL (-1)

#define SQUARE(row, col) ((row * COLUMNS) + col)
#define ROW(square) (square / COLUMNS)
#define COL(square) (square % COLUMNS)

enum flag
{
    FIRST_MIN,
    LAST_MIN
};

enum status
{
    TOUR_SUCCESS,
    TOUR_FAILED
};
/*---------------------------------------------------------------------------*/

/*---------------------------Static Functions--------------------------------*/
static void _InitMovesTable(int moves_table[BOARD_SIZE][MAX_MOVES]);
static int _Compare(size_t a, size_t b, int flag);
static size_t _OptionalMoves(int square_moves[], bit_array_t prev_steps);
static int _IsValidStep(int move, bit_array_t prev_steps);
/*---------------------------------------------------------------------------*/

/*-----------------------------Main Function---------------------------------*/
int KnightsTour(int row, int col, int path[BOARD_SIZE])
{
    int flag = FIRST_MIN;
    int min_move_idx = ILLEGAL;
    int *backup_path = (path + 1);
    int moves_table[BOARD_SIZE][MAX_MOVES] = {0};
    int square = SQUARE(row, col);
    size_t i = 0, j = 0, count = 0, min_moves = (MAX_MOVES + 1);
    int next_move = 0;
    bit_array_t prev_steps = 0;

    assert(path);

    _InitMovesTable(moves_table);

    /* initiates the first square in the knights tour */
    *path = square;
    ++path;

    /* the function will run untill it pass upon all the board */
    for (i = 1; i < BOARD_SIZE; ++i)
    {
        min_moves = (MAX_MOVES + 1);
        min_move_idx = ILLEGAL;

        /* A loop to find the next move according to Warnsdorffs heuristic */
        for (j = 0; j < MAX_MOVES; ++j)
        {
            next_move = moves_table[square][j];
            if (_IsValidStep(next_move, prev_steps))
            {
                /* if the move is valid, count how many legal moves it has */
                count = _OptionalMoves(moves_table[next_move], prev_steps);

                /* save the move with the least optional moves */
                if (_Compare(count, min_moves, flag))
                {
                    min_move_idx = j;
                    min_moves = count;
                }
            }
        }

        if (ILLEGAL != min_move_idx)
        {
            /* update all the relevant values */
            prev_steps = BitArrSetOn(prev_steps, square);
            square = moves_table[square][min_move_idx];
            *path = square;
            ++path;
        }

        /* if the function get to a deadend it will do it again this time with
           the last move with minimum optional moves (incase rhere is two..) */
        else
        {
            i = 0;
            flag = LAST_MIN;
            path = backup_path;
            square = SQUARE(row, col);
            prev_steps = 0;
        }
    }

    return (TOUR_SUCCESS);
}
/*---------------------------------------------------------------------------*/

/*-------------------------------Static Definitions--------------------------*/

/* initialises a given 'moves_table' with the possible moves (second dimention)
   from each square in the board (first dimension) */
static void _InitMovesTable(int moves_table[BOARD_SIZE][MAX_MOVES])
{
    size_t i = 0, move = 0;
    int row = 0, col = 0;
    int row_steps[MAX_MOVES] = {1,1,2,2,-1,-1,-2,-2};
    int col_steps[MAX_MOVES] = {2,-2,1,-1,2,-2,1,-1};

    assert(moves_table);

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        for (move = 0; move < MAX_MOVES; ++move)
        {
            row = ROW(i) + row_steps[move];
            col = COL(i) + col_steps[move];
            moves_table[i][move] = (0 <= row && 0 <= col
                                    && row < ROWS && col < COLUMNS)
                                    ? SQUARE(row, col) : ILLEGAL;
        }
    }
}

/* compares between two given 'a' & 'b'
   returns - when 'flag' = FIRST_MIN (1) if 'a' is smaller then 'b'
           - when 'flag' = LAST_MIN (1) if 'a' is smaller or equal to 'b'*/
static int _Compare(size_t a, size_t b, int flag)
{
    return ((FIRST_MIN == flag) ? (a < b) : (a <= b));
}

/* returns the number of possible moves from a given 'square' */
static size_t _OptionalMoves(int square_moves[], bit_array_t prev_steps)
{
    size_t i = 0, count = 0;

    for (i = 0; i < MAX_MOVES; ++i)
    {
        count += _IsValidStep(square_moves[i], prev_steps);
    }

    return (count);
}

/* checks whether a given 'move' is valid or not (retuns 1 if valid or 0 if not) */
static int _IsValidStep(int move, bit_array_t prev_steps)
{
    return (ILLEGAL != move && !BitArrGetVal(prev_steps, move));
}
/*---------------------------------------------------------------------------*/
