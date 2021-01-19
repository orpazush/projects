#ifndef __CA_TEST_UTIL_H__
#define __CA_TEST_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


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
#define INT_TEST(x, y) do {ssize_t res = y; if(x != res){\
        printf("\nINT_TEST failed in line %d\nexpected: %ld\nactual: %ld\n\n"\
        ,__LINE__, (ssize_t)x, res);\
        exit(1);}\
        }while (0)

#define STRING_TEST(x, y) do {char *res = y; if(strcmp(x, res)){\
        printf("\nSTRING_TEST failed in line %d\nexpected: %s\nactual: %s\n\n"\
        , __LINE__, x, res);\
        exit(1);}\
        }while (0)

#define TEST_SUMMARY() ((void)0)
#else

#define TEST_SUMMARY() do {double res = \
        (TEST_FAILED_COUNT + TEST_SUCCESS_COUNT);\
        printf("OVERALL TESTS: %ld\n", (size_t)res);\
        if (res){\
        res = (double)((TEST_SUCCESS_COUNT)/(res));\
        res *= 100;\
        (res != 100) ? Magenta() : DefualtColor();\
        printf("TEST COVERAGE %%: %.2f\n", res);\
        DefualtColor();}\
        }while(0)

#define INT_TEST(x, y) do {ssize_t res = y; if(x != res){\
        Magenta();\
        printf("\nINT_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %ld\nactual: %ld\n\n", (ssize_t)x, res);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)
/*
#define ADDRESS_TEST(x, y) do {void *res = y;\
        if(((void *)x) != res){\
        Magenta();\
        printf("\nADDRESS_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %p\nactual: %p\n\n", (size_t *)(void *)x, res);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)
*/
#define STRING_TEST(x, y) do {char *res = y; if(strcmp(x, res)){\
        Magenta();\
        printf("\nSTRING_TEST failed in line %d\n", __LINE__);\
        DefualtColor();\
        printf("expected: %s\nactual: %s\n\n", x, res);\
        ++TEST_FAILED_COUNT;}\
        else{++TEST_SUCCESS_COUNT;}\
        }while (0)
#endif

#endif /* __CA_TEST_UTIL_H__ */
