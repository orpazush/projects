#include<cstdlib>		//rand
#include<ctime>		    //time
#include<iostream>		//cout

#include "color_game.hpp"

namespace color_game
{

///////////////////////////////// Game Methods ////////////////////////////////
void Game::InitBoard()
{
    srand(time(0));

    //init first row
    m_board[0][0].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                             NULL, &m_board[1][0], NULL, &m_board[0][1]);

    for (size_t j = 1; j < (COLUMNS-1); ++j)
    {
        m_board[0][j].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                 NULL, &m_board[1][j], &m_board[0][j-1], &m_board[0][j+1]);
    }

    m_board[0][COLUMNS-1].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                     NULL, &m_board[1][(COLUMNS-1)], &m_board[0][COLUMNS-2], NULL);

    //init middle rows
    for (size_t row = 1; row < (ROWS-1); ++row)
    {
        m_board[row][0].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                   &m_board[row-1][0], &m_board[row+1][0],
                                   NULL, &m_board[row][1]);

        for (size_t col = 1; col < (COLUMNS-1); ++col)
        {
            m_board[row][col].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                         &m_board[row-1][col], &m_board[row+1][col],
                                         &m_board[row][col-1], &m_board[row][col+1]);
        }

        m_board[row][(COLUMNS-1)].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                             &m_board[row-1][(COLUMNS-1)],
                                             &m_board[row+1][(COLUMNS-1)],
                                             &m_board[row][COLUMNS-2], NULL);

        //init last row
        m_board[ROWS-1][0].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                      &m_board[ROWS-2][0], NULL, NULL, &m_board[ROWS-1][1]);

        for (size_t col = 1; col < (COLUMNS - 1); ++col)
        {
            m_board[ROWS-1][col].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                            &m_board[ROWS-2][col], NULL,
                                            &m_board[ROWS - 1][col - 1],
                                            &m_board[ROWS - 1][col + 1]);
        }

        m_board[ROWS-1][COLUMNS-1].InitSquare(IntToColor(rand() % NUM_OF_COLORS),
                                              &m_board[ROWS-2][COLUMNS-1], NULL, &m_board[ROWS-1][COLUMNS-2], NULL);
    }
}

void Game::PrintBoard()
{
    for (size_t i = 0; i < ROWS; ++i)
    {
        for (size_t j = 0; j < COLUMNS; j++)
        {
            m_board[i][j].Print();
            std::cout << " ";
        }

        std::cout << "\033[0m" << std::endl;
    }
}

Game::color_t Game::GetInput()
{
    std::string input;
    std::cin >> input;

    return ToColorT(input.c_str());
}

void Game::PlayMove(color_t chosenMove)
{
    color_t first = m_board[0][0].GetColor();
    if (first != chosenMove)
    {
        m_board[0][0].ChangeColor(first, chosenMove);
    }
}

bool Game::Check(Game::color_t color)
{
    for (size_t row = 0; row < ROWS; ++row)
    {
        for (size_t col = 0; col < COLUMNS; ++col)
        {
            if (color != m_board[row][col].GetColor())
            {
                return false;
            }
        }
    }
    return true;
}

///////////////////////////////// Square Methods //////////////////////////////
void Game::Square::ChangeColor(color_t from, color_t to)
{
    if (m_color == from)
    {
        m_color = to;
        for (size_t i = 0; i < NUM_OF_SIDES; ++i)
        {
            if (m_neighbors[i])
            {
                m_neighbors[i]->ChangeColor(from, to);
            }
        }
    }
}

void Game::Square::Print()
{
    Game::Print(m_color);
}

void Game::Square::InitSquare(color_t color, Square* up, Square* down, Square* left, Square* right)
{
    m_color = color;

    m_neighbors[UP] = up;
    m_neighbors[DOWN] = down;
    m_neighbors[LEFT] = left;
    m_neighbors[RIGHT] = right;
}

Game::color_t Game::Square::GetColor()
{
    return m_color;
}

void Game::Play(size_t moves)
{
    InitBoard();
    PrintBoard();
    for (size_t i = 0; i < moves; ++i)
    {
        color_t chosenColor = GetInput();
        PlayMove(chosenColor);
        PrintBoard();
        std::cout << "you have " << (moves-i-1) << " moves left\n";
        if (Check(chosenColor))
        {
            std::cout << "🏆🏆🏆 You won!! 🏆🏆🏆\n";
            return;
        }
    }

    std::cout << "👎🏼👎🏼👎🏼You lose👎🏼👎🏼👎🏼\n";
}

}//namespace color_game
