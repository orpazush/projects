//
// Created by orpaz on 08/03/2021.
//

#include <cstddef>
#include <iostream>

using namespace std;

void TestPixelsRectangle();


int main()
{
    TestPixelsRectangle();

    return 0;
}

template<size_t ROWS, size_t COLUMNS>
bool CheckColumn(const char image[ROWS][COLUMNS], size_t column)
{
    for (size_t i = 0; i < ROWS; ++i)
    {
        if (image[i][column])
        {
            return true;
        }
    }
    return false;
}

template<size_t ROWS, size_t COLUMNS>
bool CheckRow(const char image[ROWS][COLUMNS], size_t row)
{
    const char *endOfRow = image[row] + COLUMNS;
    for (const char *i = image[row]; i < endOfRow; ++i)
    {
        if (*i)
        {
            return true;
        }
    }
    return false;
}

//returns the are of the smallest rectangle that enclosing all the black pixels
template<size_t ROWS, size_t COLUMNS>
size_t MinPixelsRectangleArea(char image[ROWS][COLUMNS], int x, int y)
{
    //find top
    size_t up = 0, down = y;
    size_t top = (up + down)/2;

    for ( ; (up+1) < down; top = (up + down)/2)
    {
        if (CheckRow<ROWS, COLUMNS>(image, top))
        {
            down = top;
        } else
        {
            up = top;
        }
    }
    top = CheckRow<ROWS, COLUMNS>(image, up) ? up : down;

    //find bottom
    up = y, down = ROWS-1;
    size_t bottom = (up + down)/2;

    for ( ; (up+1) < down; bottom = (up + down)/2)
    {
        if (CheckRow<ROWS, COLUMNS>(image, bottom))
        {
            up = bottom;
        } else
        {
            down = bottom;
        }
    }
    bottom = CheckRow<ROWS, COLUMNS>(image, down) ? down : up;

    //find left
    size_t left = 0, right = x;
    size_t mostLeft = (left + right) / 2;

    for ( ; (left+1) < right; mostLeft = (left + right) / 2)
    {
        if (CheckColumn<ROWS, COLUMNS>(image, mostLeft))
        {
            right = mostLeft;
        } else
        {
            left = mostLeft;
        }
    }
    mostLeft = CheckColumn<ROWS, COLUMNS>(image, left) ? left : right;

    //find right
    left = x, right = COLUMNS-1;
    size_t mostRight = (left + right) / 2;

    for ( ; (left+1) < right; mostRight = (left + right) / 2)
    {
        if (CheckColumn<ROWS, COLUMNS>(image, mostRight))
        {
            left = mostRight;
        } else
        {
            right = mostRight;
        }
    }
    mostRight = CheckColumn<ROWS, COLUMNS>(image, right) ? right : left;

    return ((bottom - top + 1) * (mostRight - mostLeft + 1));
}

void TestPixelsRectangle()
{
    cout << "TestPixelsRectangle : ";

    size_t tests = 0;
    size_t numOfTests = 0;
    const size_t rows = 5;
    const size_t columns = 4;

    char image[rows][columns] = { {0, 0, 0, 0},
                                  {0, 0, 1, 0},
                                  {0, 1, 1, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 0, 0} };

    tests += (6 == MinPixelsRectangleArea<rows, columns>(image, 2, 1));
    ++numOfTests;

    char image1[rows][columns] = { {0, 0, 0, 0},
                                   {0, 0, 1, 0},
                                   {0, 1, 1, 0},
                                   {1, 1, 1, 0},
                                   {0, 0, 0, 0} };

    tests += (9 == MinPixelsRectangleArea<rows, columns>(image1, 2, 1));
    ++numOfTests;


    char image2[rows][columns] = { {0, 0, 0, 0},
                                   {0, 0, 1, 1},
                                   {0, 1, 1, 0},
                                   {1, 1, 1, 0},
                                   {0, 0, 0, 0} };

    tests += (12 == MinPixelsRectangleArea<rows, columns>(image2, 2, 1));
    ++numOfTests;


    char image3[rows][columns] = { {1, 1, 1, 0},
                                   {0, 0, 1, 1},
                                   {0, 1, 1, 0},
                                   {1, 1, 1, 0},
                                   {0, 0, 0, 0} };

    tests += (16 == MinPixelsRectangleArea<rows, columns>(image3, 0, 0));
    ++numOfTests;

    if (tests == numOfTests)
    {
        cout << "Success!\n";
    }
    else
    {
        cout << "Failure!\n";
        cout << numOfTests - tests << " tests has been failed\n";
    }

}
