//
// Created by orpaz on 22/12/2020.
//

#include <cstddef>//size_t
#include <iostream>

template<int ROWS, int COLUMNS, typename T>
void SnailMatrix(T matrix[ROWS][COLUMNS])
{
    size_t i = 0;
    size_t j = 0;
    size_t rightEdge = COLUMNS-1;
    size_t leftEdge = 0;
    size_t downEdge = ROWS-1;
    size_t upEdge = 0;

    for (i = upEdge, j = leftEdge;
         rightEdge >= leftEdge || downEdge >= upEdge;
         ++i, ++j)
    {
        while (j < rightEdge)
        {
            std::cout << matrix[i][j] << ", ";
            ++j;
        }
        --rightEdge;

        std::cout << std::endl;
        while (i < downEdge)
        {
            std::cout << matrix[i][j] << ", ";
            ++i;
        }
        --downEdge;
        std::cout << std::endl;

        while (j > leftEdge)
        {
            std::cout << matrix[i][j] << ", ";
            --j;
        }
        ++leftEdge;
        std::cout << std::endl;
        while (i > upEdge)
        {
            std::cout << matrix[i][j] << ", ";
            --i;
        }
        ++upEdge;
        std::cout << std::endl;
    }
}

int main()
{
    int matrix[5][5] {{1, 2, 3, 4, 5},
                      {6, 7, 8, 9, 10},
                      {11, 12, 13, 14, 15},
                      {16, 17, 18, 19, 20},
                      {21, 22, 23, 24, 25} };

    SnailMatrix<5>(matrix);

    return 0;
}