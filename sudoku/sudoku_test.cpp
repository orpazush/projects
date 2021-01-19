//
// Created by orpaz on 17/12/2020.
//

#include <iostream>
#include "sudoku.hpp"

int main()
{
    int easy[9][9] = { {8, 6, 0, 7, 5, 0, 0, 0, 0},
                       {0, 0, 9, 2, 1, 0, 0, 0, 3},
                       {3, 0, 0, 0, 0, 9, 2, 6, 0},
                       {6, 0, 5, 0, 0, 4, 0, 7, 0},
                       {0, 7, 0, 5, 0, 2, 0, 3, 0},
                       {0, 2, 0, 8, 0, 0, 1, 0, 6},
                       {0, 5, 6, 9, 0, 0, 0, 0, 8},
                       {9, 0, 0, 0, 2, 8, 5, 0, 0},
                       {0, 0, 0, 0, 4, 5, 0, 2, 9}  };

    int hard[9][9] =  {{0, 0, 0, 7, 0, 3, 0, 0, 0},
                       {0, 7, 0, 0, 0, 0, 0, 9, 0},
                       {8, 0, 6, 0, 0, 0, 3, 0, 1},
                       {0, 0, 4, 5, 9, 2, 1, 0, 0},
                       {2, 0, 0, 0, 0, 0, 0, 0, 5},
                       {0, 0, 1, 6, 3, 4, 9, 0, 0},
                       {5, 0, 7, 0, 0, 0, 6, 0, 8},
                       {0, 4, 0, 0, 0, 0, 0, 2, 0},
                       {0, 0, 0, 8, 0, 1, 0, 0, 0} };

//
//    Sudoku test(easy);
//
//    test.PrintBoard();
//    test.Solve();
//    test.PrintBoard();
//    if (test.Check())
//    {
//        std::cout << "🎉🎊🎉🎊 you won!! 🎉🎊🎉🎊\n";
//    }
//    else
//    {
//        std::cout << "👎🏻👎🏻👎🏻 you lose!! 👎🏻👎🏻👎🏻\n";
//    }
//
//    Sudoku test1(hard);
//    test1.PrintBoard();
//    test1.Solve();
//    test1.PrintBoard();
//    if (test1.Check())
//    {
//        std::cout << "🎉🎊🎉🎊 you won!! 🎉🎊🎉🎊\n";
//    }
//    else
//    {
//        std::cout << "👎🏻👎🏻👎🏻👎🏻 you lose!! 👎🏻👎🏻👎🏻👎🏻\n";
//    }

    Sudoku test2(Sudoku::EASY);
    test2.Play();

    return 0;
}
