/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					Last update : 17.12.20									 *
 ****************************************************************************/

#ifndef __SUDOKU_HPP__
#define __SUDOKU_HPP__

#include <cstdint>      //uint8_t
#include "bitarray.hpp" //BitArray


class Sudoku
{
public:
    enum difficulty_t
    {
        EASY,
        MEDIUM,
        HARD
    };
    static const uint8_t BASE = 3;
    static const uint8_t NUM_OF_DIGITS = BASE * BASE;
    typedef ilrd::Bitarray<NUM_OF_DIGITS+1> digits_bitarray_t;

    explicit Sudoku(int values[NUM_OF_DIGITS][NUM_OF_DIGITS]);
    explicit Sudoku(Sudoku::difficulty_t level =  EASY);
//    ~Sudoku();

    void PrintBoard();
    void Play();
    bool Check();
    void Solve();

private:
    class Square
    {
    public:
        void InitSquare(uint8_t row, uint8_t column, uint8_t square);
        size_t CountPossibleValues(const Sudoku &sudoku);
        void UpdatePossibleValues(const Sudoku& sudoku);
        void UnSetValue(Sudoku *sudoku);
        int FindNextOption(size_t startIdx) const;
        Square *NextSquare(Sudoku *sudoku) const;
        void SetValue(Sudoku *sudoku, int value);
        int GetValue() const;
        bool IsPossible(size_t value) const;

    private:
        int m_value;
        uint8_t m_row;
        uint8_t m_column;
        uint8_t m_square;
        digits_bitarray_t m_possibleValues;
    };

    void GetInput();
    void StepOne();
    void StepTwo();
    void BackTracking(Square *square);

    static int FindMissingDigit(digits_bitarray_t bitarray, size_t startIdx);

    Square m_board[NUM_OF_DIGITS][NUM_OF_DIGITS];
    digits_bitarray_t m_rows[NUM_OF_DIGITS];
    digits_bitarray_t m_columns[NUM_OF_DIGITS];
    digits_bitarray_t m_fullSquares[NUM_OF_DIGITS];
    bool m_noChanges = false;
    size_t m_missingDigits;
};

#endif //__SUDOKU_HPP__
