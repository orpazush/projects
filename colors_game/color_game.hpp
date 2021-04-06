/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					Last update : 6.4.21									 *
 *****************************************************************************/

#ifndef __COLOR_GAME_HPP__
#define __COLOR_GAME_HPP__

#include <iostream>
#include <cstring>
#include <cstdlib>

namespace color_game
{

class Game
{

public:
    static const size_t ROWS = 10;
    static const size_t COLUMNS = 10;

    enum color_t
    {
        RED,
        BLUE,
        GREEN,
        YELLOW,
        NUM_OF_COLORS
    };

    static inline color_t IntToColor(int intColor);

    static inline void Print(color_t intColor);

    static inline color_t ToColorT(const char *str);

    //Game();
    //~Game();

    void Play(size_t moves = 15);

private:

    class Square
    {
    public:
        enum side_t
        {
            UP,
            RIGHT,
            DOWN,
            LEFT,
            NUM_OF_SIDES
        };

        void ChangeColor(color_t from, color_t to);

        void Print();

        void InitSquare(color_t color, Square *up, Square *down, Square *left,
                        Square *right);

        color_t GetColor();

    private:
        color_t m_color;
        Square *m_neighbors[NUM_OF_SIDES];
    };

    void InitBoard();

    void PrintBoard();

    static color_t GetInput();

    void PlayMove(color_t chosenMove);

    bool Check(color_t color);

    Square m_board[ROWS][COLUMNS];
};

//////////////////////////////// Static Funcs /////////////////////////////////

Game::color_t Game::IntToColor(int intColor)
{
    static const color_t m_colors[NUM_OF_COLORS] = {RED, BLUE, GREEN, YELLOW};

    return m_colors[intColor];
}

void Game::Print(Game::color_t color)
{
    static const std::string m_colors[NUM_OF_COLORS] =
            {"\033[41m"/*red*/, "\033[44m"/*blue*/, "\033[42m"/*green*/,
             "\033[43m"/*yellow*/ };

    std::cout << m_colors[color] << " ";

}

Game::color_t Game::ToColorT(const char *str)
{
    if (!strcmp(str, "b"))
    {
        return Game::BLUE;
    } else if (!strcmp(str, "r"))
    {
        return Game::RED;
    } else if (!strcmp(str, "g"))
    {
        return Game::GREEN;
    } else if (!strcmp(str, "y"))
    {
        return Game::YELLOW;
    } else
    {
        throw std::runtime_error("invalid input\n");
    }
}

}//namespace color_game

#endif  //__COLOR_GAME_HPP__