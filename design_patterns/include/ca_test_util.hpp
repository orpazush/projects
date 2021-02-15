/******************************************************************************
 *                              Test utility tool			                  *
 *                        Created by Aviv L. and Chanan K.	                  *
 *                              All rights reserved			                  *
 ******************************************************************************/

#ifndef __NINJA_TEST_H__
#define __NINJA_TEST_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>



size_t TEST_FAILED_COUNT = 0;
size_t TEST_SUCCESS_COUNT = 0;

void Red()
{
  printf("\033[1;31m");
}

void Yellow()
{
  printf("\033[0;33m");
}

void Green()
{
  printf("\033[0;32m");
}

void Blue()
{
  printf("\033[1;34m");
}

void Cyan()
{
  printf("\033[1;36m");
}

void Magenta()
{
  printf("\033[1;35m");
}

void DefualtColor()
{
  printf("\033[0m");
}


#ifdef ABORT
#define INT_TEST(x, y) do {ssize_t __RES__ = y; if(x != __RES__){\
        printf("\nINT_TEST failed in line %d\nexpected: %ld\nactual: %ld\n\n"\
        ,__LINE__, (ssize_t)x, __RES__);\
        exit(1);}\
        }while (0)

#define STRING_TEST(x, y) do {char *__RES__ = y; if(strcmp(x, __RES__)){\
        printf("\nSTRING_TEST failed in line %d\nexpected: %s\nactual: %s\n\n"\
        , __LINE__, x, __RES__);\
        exit(1);}\
        }while (0)

#define TEST_SUMMARY() ((void)0)
#else

#define TEST_SUMMARY() do {double __RES__ = \
        (TEST_FAILED_COUNT + TEST_SUCCESS_COUNT);\
        printf("OVERALL TESTS: %ld\n", (size_t)__RES__);\
		printf("SUCCESED TESTS: %ld\n", TEST_SUCCESS_COUNT);\
        if (__RES__){\
        __RES__ = (double)((TEST_SUCCESS_COUNT)/(__RES__));\
        __RES__ *= 100;\
        (__RES__ != 100) ? Magenta() : DefualtColor();\
        printf("TEST SUCCESS RATE (%%): %.2f\n", __RES__);\
        DefualtColor();}\
        }while(0)

#define BOOL_TEST(x) do { int __RES__ = x; if(!__RES__){\
        Magenta();\
        printf("\nBOOL_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expression is false\n\n");\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)


#define PTR_TEST(x, y) do {void *__RES__ = y; if(x != __RES__){\
        Magenta();\
        printf("\nPTR_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %p\nactual: %p\n\n", x, __RES__);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)

#define INT_TEST(x, y) do {ssize_t __RES__ = y; if(x != __RES__){\
        Magenta();\
        printf("\nINT_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %ld\nactual: %ld\n\n", (ssize_t)x, __RES__);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)

#define STRING_TEST(x, y) do {char *__RES__ = y; if(strcmp(x, __RES__)){\
        Magenta();\
        printf("\nSTRING_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %s\nactual: %s\n\n", x, __RES__);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)
#endif

#endif /* __NINJA_TEST_H__ */
