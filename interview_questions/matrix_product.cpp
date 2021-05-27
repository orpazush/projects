///////////////////////////////////////////////////////////////////////////////
//                           Matrix Product                                  //
// Created by orpaz on 27/05/2021.                                           //
///////////////////////////////////////////////////////////////////////////////
// Question: Given a matrix, find the path from top left to bottom right with//
//           the greatest product by moving only down and right.             //
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>  //size_t
#include <iostream> //cout

using namespace std;

void TestMatrixProduct();

int main()
{
    TestMatrixProduct();

    return 0;
}

// time complex
template <size_t ROWS, size_t COLUMNS, typename T>
T MatrixProduct(T matrix[ROWS][COLUMNS])
{
    T maxMatrix[ROWS][COLUMNS] = {0};

    maxMatrix[0][0] = matrix[0][0];
    //  first row
    for (size_t col = 1; col < COLUMNS; ++col)
    {
        maxMatrix[0][col] = matrix[0][col] * maxMatrix[0][col-1];
    }
    //  first column
    for (size_t row = 1; row < ROWS; ++row)
    {
        maxMatrix[row][0] = matrix[row][0] * maxMatrix[row-1][0];
    }
    //  the rest
    for (size_t row = 1; row < ROWS; ++row)
    {
        for(size_t col = 1; col < COLUMNS; ++col)
        {
            if (maxMatrix[row-1][col] > maxMatrix[row][col-1])
            {
                maxMatrix[row][col] = matrix[row][col] * maxMatrix[row-1][col];
            }
            else
            {
                maxMatrix[row][col] = matrix[row][col] * maxMatrix[row][col-1];
            }
        }
    }

    return (maxMatrix[ROWS-1][COLUMNS-1]);
}

//TODO better test and treat cases there is negative numbers
void TestMatrixProduct()
{
    cout << "TestMatrixProduct : ";

    size_t numOfTests = 0;
    size_t tests = 0;

    int testMatrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    tests += (2016 == MatrixProduct<3, 3, int>(testMatrix));
    ++numOfTests;

    if (tests == numOfTests)
    {
        cout << "Success!\n";
    }
    else
    {
        cout << "Failure!\n";
    }

}
