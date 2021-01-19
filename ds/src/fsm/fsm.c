/****************************************************************************
* 					written by : orpaz houta								*
* 					review : Yonathan Bardugo								*
*					Last update : 23.5.20 									*
****************************************************************************/
#include <stdio.h> 	    /* fprintf 					    */
#include <string.h>	    /* memcpy, memset, strlen       */
#include <assert.h>	    /* assert    					*/
#include <stdlib.h>     /* strtod, malloc, free	        */
#include <math.h> 	    /* pow 						    */

#include "stack.h"
#include "fsm.h"
/* ------------------------------------------------------------------------- */

/* Status */
#define FSM_TRUE (1)
#define FSM_FALSE (0)

/* Amount of columns in the LUT */
#define ASCII_SIZE (256)

/* For unused parameters */
#define UNUSED(x) (void)(x)

/* ------------------------------------------------------------------------- */

typedef enum
{
    WAIT_FOR_NUMBER,
    WAIT_FOR_OPERATION,
    CALCULATE,
    PRIORITY,
    NUM_OF_STATES,
    SUCCESS
} status_t;

typedef enum
{
    MALLOC_ERROR = -3,
    SYNTAX_ERROR = -2,
    MATH_ERROR = -1,
    END_OF_STR = 0
}error_t;

typedef enum
{
    LOW,
    MEDIUM,
    HIGH,
    SUPER_HIGH
} priority_t;

typedef enum action
{
    OPEN = 40,
    CLOSE,
    MUL,
    ADD,
    SUB = 45,
    DIV = 47,
    POW = 94
} action_t;

typedef struct operate
{
    char operate;
    int priority;
} operate_t;

typedef int (*operate_func)(char *sub_str, stack_t *stack_num,
                                                stack_t *stack_opr);
static operate_func fsm[NUM_OF_STATES][ASCII_SIZE];

/* ------------------------------------------------------------------------- */

static void InitTable(void);
static void RemoveSpaces(char *expression);
static char *GetNextSubStr(char *str, char *sub_str ,int status);
static int SubCalc(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int PushNum(char *number, stack_t *stack_num, stack_t *stack_opr);
static int PushOper(char *sign, int priority, stack_t *stack_opr);
static int IsValid(char *sign, int priority, stack_t *stack_num,
                                                        stack_t *stack_opr);
static void Destroy(stack_t *stack_num, stack_t *stack_opr);
static int EndOfStr(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Error(char *sign, stack_t *stack_num, stack_t *stack_opr);

/* ------------------------------------------------------------------------- */

static int GetSuperHigh(char *sign, stack_t *stack_num,stack_t *stack_opr);
static int GetHigh(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int GetMedium(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int GetLow(char *sign, stack_t *stack_num, stack_t *stack_opr);

/* ------------------------------------------------------------------------- */

static int Add(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Mul(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Sub(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Div(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Pow(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int Parentheses(char *sign, stack_t *stack_num, stack_t *stack_opr);
static int OpenParentheses(char *sign, stack_t *stack_num, stack_t *stack_opr);

/* ------------------------------------------------------------------------- */

int Calculate(double *result, char *expression)
{
    char *sub_str = NULL;
    stack_t *stack_num = NULL, *stack_opr = NULL;
    operate_func lut_action = NULL;
	size_t size_expression = 0;
	int curr_status = WAIT_FOR_NUMBER;

	assert(expression);
	assert(result);

	RemoveSpaces(expression);
	size_expression = (strlen(expression) + 1);

	/*
     * Creating two stacks :
     * 1 - to contain the oparations.
     * 2 - to contain the numbers.
     */
    stack_num = StackCreate(size_expression);

    if (!stack_num)
    {
#ifndef NDEBUG
        fprintf(stderr, "Error - memory allocation failed for 'stack_num'!\n");
#endif
        return (MALLOC_ERROR);
    }

    stack_opr = StackCreate(size_expression * sizeof(operate_t));

    if (!stack_opr)
    {
#ifndef NDEBUG
        fprintf(stderr, "Error - memory allocation failed for 'stack_opr'!\n");
#endif
        return (MALLOC_ERROR);
    }

    sub_str = (char *)malloc(sizeof(char) * size_expression);

    if (!sub_str)
    {
        free(stack_num);
        stack_num = NULL;

        free(stack_opr);
        stack_opr = NULL;

#ifndef NDEBUG
        fprintf(stderr, "Error - memory allocation failed for 'sub_str'!\n");
#endif
        return (MALLOC_ERROR);
    }

	/* LUT initialization. */
    InitTable();

    /*
	 * Main loop that will run until ERROR accurs or 'END_OF_STR' will be
     * returned
     */
    while (curr_status <= SUCCESS)
    {
        GetNextSubStr(expression, sub_str, curr_status);

        if ('\0' == *sub_str)
        {
            lut_action = fsm[curr_status][0];
        }
        else
        {
            lut_action = fsm[curr_status][(int)sub_str[0]];
        }
        curr_status = lut_action(sub_str, stack_num, stack_opr);
    }

	/* stirng reached '\0' and ERRORS accured, the result will be updated */
    if (curr_status == END_OF_STR)
    {
        *result = *(double *)StackPeek(stack_num);
    }

	*expression = '\0';
    GetNextSubStr(expression, sub_str, curr_status);

    free(sub_str);
    sub_str = NULL;

    Destroy(stack_num, stack_opr);

    return (curr_status);
}

/* ------------------------------------------------------------------------- */

static void InitTable(void)
{
    int i = 0 , j = 0;

    for (i = 0; i < NUM_OF_STATES; ++i)
    {
        for (j = 0; j < ASCII_SIZE; ++j)
        {
            fsm[i][j] = &Error;
        }
    }

    fsm[WAIT_FOR_NUMBER][OPEN] = &SubCalc;
    fsm[WAIT_FOR_NUMBER][ADD] = &PushNum;
    fsm[WAIT_FOR_NUMBER][SUB] = &PushNum;

    for (i = '0'; i <= '9'; ++i)
    {
        fsm[WAIT_FOR_NUMBER][i] = &PushNum;
    }

    /* \0 */
    fsm[WAIT_FOR_OPERATION][0] = &EndOfStr;

    fsm[WAIT_FOR_OPERATION][CLOSE] = &SubCalc;
    fsm[WAIT_FOR_OPERATION][MUL] = &SubCalc;
    fsm[WAIT_FOR_OPERATION][ADD] = &SubCalc;
    fsm[WAIT_FOR_OPERATION][SUB] = &SubCalc;
    fsm[WAIT_FOR_OPERATION][DIV] = &SubCalc;
    fsm[WAIT_FOR_OPERATION][POW] = &SubCalc;

    fsm[PRIORITY][OPEN] = &GetSuperHigh;
    fsm[PRIORITY][CLOSE] = &GetSuperHigh;
    fsm[PRIORITY][MUL] = &GetMedium;
    fsm[PRIORITY][ADD] = &GetLow;
    fsm[PRIORITY][SUB] = &GetLow;
    fsm[PRIORITY][DIV] = &GetMedium;
    fsm[PRIORITY][POW] = &GetHigh;

    fsm[CALCULATE][OPEN] = &OpenParentheses;
    fsm[CALCULATE][CLOSE] = &Parentheses;
    fsm[CALCULATE][MUL] = &Mul;
    fsm[CALCULATE][ADD] = &Add;
    fsm[CALCULATE][SUB] = &Sub;
    fsm[CALCULATE][DIV] = &Div;
    fsm[CALCULATE][POW] = &Pow;
}

/* ------------------------------------------------------------------------- */

static char *GetNextSubStr(char *str, char *sub_str, int status)
{
    static char *save_location = NULL;
    char *curr_str = NULL;

    memset(sub_str, '\0', 2);

    if (NULL == save_location)
    {
        save_location = str;
    }

    if (('\0' == *save_location) || ('\0' == *str))
    {
        save_location = NULL;
        return sub_str;
    }

    curr_str = save_location;

    if (status == WAIT_FOR_OPERATION)
    {
        ++save_location;
        memset(sub_str, *curr_str, 1);
    }
    else
    {
        strtod(curr_str, &save_location);

        if (curr_str == save_location)
        {
            memset(sub_str, '$', 1);

            if ('(' == *curr_str )
            {
                ++save_location;
                memset(sub_str, *curr_str, 1);
            }
        }
        else
        {
            memset(sub_str, '\0', (save_location - curr_str) + 1);
            memcpy(sub_str, curr_str, save_location - curr_str);
        }
    }

    return (sub_str);
}

/* ------------------------------------------------------------------------- */

static int SubCalc(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    int priority = 0;
    int parantheses_flag = 1;
	int status = WAIT_FOR_NUMBER;
    operate_t *prev_opr = {NULL};
    operate_func lut_action = NULL;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

	/* get the priority of the operation */
    lut_action = fsm[PRIORITY][(int)sign[0]];
    priority = lut_action(sign, stack_num, stack_opr);

	/* checks if the previous operation can be done */
    status = IsValid(sign, priority, stack_num, stack_opr);

    if ((FSM_TRUE == status) || (')' == *sign))
    {
        if (')' == *sign)
        {
            status = PushOper(sign, priority, stack_opr);

            if (status == MALLOC_ERROR)
            {
                return status;
            }

            parantheses_flag = 0;
        }

        prev_opr = StackPeek(stack_opr);
        StackPop(stack_opr);

        lut_action = fsm[CALCULATE][(int)prev_opr->operate];
        status = lut_action(&prev_opr->operate, stack_num, stack_opr);

        free(prev_opr);
        prev_opr = NULL;
    }

    if (parantheses_flag && (status <= SUCCESS))
    {
        status = PushOper(sign, priority, stack_opr);
    }

    return ((status == SUCCESS) ? (WAIT_FOR_NUMBER) : (status));
}

/* ------------------------------------------------------------------------- */

static int PushOper(char *sign, int priority, stack_t *stack_opr)
{
    operate_t *operate = {NULL};

    assert(sign);
    assert(stack_opr);

    operate = (operate_t *)malloc(sizeof(operate_t));

    if (!operate)
    {
#ifndef NDEBUG
        fprintf(stderr, "Error in alocating memory\n");
#endif
        return (MALLOC_ERROR);
    }

    operate->priority = priority;
    operate->operate = *sign;

    StackPush(stack_opr, operate);
    return (SUCCESS);
}

/* ------------------------------------------------------------------------- */

static int PushNum(char *number, stack_t *stack_num, stack_t *stack_opr)
{
    double *num_to_push = NULL;

    assert(stack_num);
    assert(stack_opr);
    assert(number);

    num_to_push = (double *)malloc(sizeof(double));

	if (!num_to_push)
    {
#ifndef NDEBUG
        fprintf(stderr, "Error in alocating memory\n");
#endif
        return (MALLOC_ERROR);
    }

    *num_to_push = strtod(number, NULL);
    StackPush(stack_num, num_to_push);

    return (WAIT_FOR_OPERATION);
}

/* ------------------------------------------------------------------------- */

static int IsValid(char *sign, int priority, stack_t *stack_num,
                                                        stack_t *stack_opr)
{
    operate_t *prev_opr = {NULL};

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    if (!StackIsEmpty(stack_opr))
    {
        prev_opr = (operate_t *)StackPeek(stack_opr);

        if ((priority <= prev_opr->priority) && (1 < StackSize(stack_num)) &&
            ('(' != prev_opr->operate))
        {
            if ((HIGH == priority) && (HIGH == prev_opr->priority))
            {
                return (FSM_FALSE);
            }

            return (FSM_TRUE);
        }
    }
    return (FSM_FALSE);
}

/* ------------------------------------------------------------------------- */

static int Add(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    double *num1 = NULL;
    double *num2 = NULL;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    num1 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    num2 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    *num2 += *num1;
    StackPush(stack_num, num2);

    free(num1);
    num1 = NULL;
    return (SUCCESS);
}

/* ------------------------------------------------------------------------- */

static int Sub(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    double *num1 = NULL;
    double *num2 = NULL;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    num1 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    num2 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    *num2 -= *num1;
    StackPush(stack_num, num2);

    free(num1);
    num1 = NULL;
    return (SUCCESS);
}

/* ------------------------------------------------------------------------- */

static int Mul(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    double *num1 = NULL;
    double *num2 = NULL;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    num1 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    num2 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    *num2 *= *num1;
    StackPush(stack_num, num2);

    free(num1);
    num1 = NULL;
    return (SUCCESS);
}

/* ------------------------------------------------------------------------- */

static int Div(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    double *num1 = NULL;
    double *num2 = NULL;
    int status = SUCCESS;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    num1 = (double *)StackPeek(stack_num);
    StackPop(stack_num);
    num2 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    (*num1) ? (*num2 /= *num1) : (status = MATH_ERROR);

    StackPush(stack_num, num2);

    free(num1);
    num1 = NULL;

    return (status);
}

/* ------------------------------------------------------------------------- */

static int Pow(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    double *num1 = NULL;
    double *num2 = NULL;
    int status = SUCCESS;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    num1 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    num2 = (double *)StackPeek(stack_num);
    StackPop(stack_num);

    if ((!*num1 && !*num2) || (0 > *num1 && !*num2))
    {
        status = MATH_ERROR;
    }
	else
	{
		*num2 = pow(*num2, *num1);
	}

    StackPush(stack_num, num2);

    free(num1);
    num1 = NULL;

    return (status);
}

/* ------------------------------------------------------------------------- */

static int Parentheses(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    char sub_str = 0;
    int status = WAIT_FOR_OPERATION;
    operate_t *curr_opr = {NULL};
    operate_func lut_action = NULL;

    assert(sign);
    assert(stack_num);
    assert(stack_opr);

    curr_opr = (operate_t *)StackPeek(stack_opr);
    sub_str = curr_opr->operate;

    while (('(' != sub_str) && (!StackIsEmpty(stack_opr)) &&
                                                (status != MATH_ERROR))
    {
        lut_action = fsm[CALCULATE][(int)sub_str];
        status = lut_action(&sub_str, stack_num, stack_opr);

        StackPop(stack_opr);
        free(curr_opr);
        curr_opr = NULL;

        if (!StackIsEmpty(stack_opr))
        {
            curr_opr = (operate_t *)StackPeek(stack_opr);
            sub_str = curr_opr->operate;
        }
    }
    if (StackIsEmpty(stack_opr))
    {
        return MATH_ERROR;
    }

    curr_opr = (operate_t *)StackPeek(stack_opr);
    StackPop(stack_opr);
    free(curr_opr);
    curr_opr = NULL;

    return ((status == SUCCESS) ? (WAIT_FOR_OPERATION) : (status));
}

/* ------------------------------------------------------------------------- */

static int OpenParentheses(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (MATH_ERROR);
}

/* ------------------------------------------------------------------------- */

static int GetLow(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (LOW);
}

/* ------------------------------------------------------------------------- */

static int GetMedium(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (MEDIUM);
}

/* ------------------------------------------------------------------------- */

static int GetHigh(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (HIGH);
}

/* ------------------------------------------------------------------------- */

static int GetSuperHigh(char *sign, stack_t *stack_num, stack_t *stack_opr)

{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (SUPER_HIGH);
}

/* ------------------------------------------------------------------------- */

static void Destroy(stack_t *stack_num, stack_t *stack_opr)
{
    double *to_remove = NULL;

	assert(stack_num);
	assert(stack_opr);

    while (!StackIsEmpty(stack_num))
    {
        to_remove = (double *)StackPeek(stack_num);
        StackPop(stack_num);

        free(to_remove);
        to_remove = NULL;
    }

    while (!StackIsEmpty(stack_opr))
    {
        to_remove = StackPeek(stack_opr);
        StackPop(stack_opr);

        free(to_remove);
        to_remove = NULL;
    }

    StackDestroy(stack_num);
    stack_num = NULL;

    StackDestroy(stack_opr);
    stack_opr = NULL;
}

/* ------------------------------------------------------------------------- */

static int EndOfStr(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
	int status = 0;
	operate_func lut_action = NULL;
    operate_t *curr_opr = {NULL};

    UNUSED(sign);
	assert(stack_num);
	assert(stack_opr);

	/*
     * when the str reaches '\0' the function handles with the
	 * numbers and operations that still in the stacks
     */
    while ((0 < StackSize(stack_num)) && (!StackIsEmpty(stack_opr)) &&
                                                    (status != MATH_ERROR))
    {
        curr_opr = (operate_t *)StackPeek(stack_opr);

        lut_action = fsm[CALCULATE][(int)curr_opr->operate];
        status = lut_action(&curr_opr->operate, stack_num, stack_opr);

        StackPop(stack_opr);
        free(curr_opr);
        curr_opr = NULL;
    }
    return ((status == MATH_ERROR) ? MATH_ERROR : END_OF_STR);
}

/* ------------------------------------------------------------------------- */

static int Error(char *sign, stack_t *stack_num, stack_t *stack_opr)
{
    UNUSED(sign);
    UNUSED(stack_num);
    UNUSED(stack_opr);

    return (SYNTAX_ERROR);
}

/* ------------------------------------------------------------------------- */

static void RemoveSpaces(char *expression)
{
	int i = 0, count = 0;

	assert(expression);

    for (; expression[i]; ++i)
	{
		if (' ' != expression[i])
		{
			expression[count++] = expression[i];
		}
	}
    expression[count] = '\0';
}
