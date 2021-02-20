/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					Last update : 1.2.20									 *
 *****************************************************************************
 * End of game - all the rabbits inside a hole.                              *
 * Parts Rules:                                                              *
 * Mushrooms - are stationary & cannot be moved (1 space)                    *
 * Foxes - can only move backward or forward. foxes cannot jump over         *
 *         obstacles (2 spaces)                                              *
 * Rabbits - move by jumping horizontally or vertically over one or more     *
 *           spaces with obstacles (other rabbits, mushrooms, foxes or       *
 *           combination of these)                                           *
 *         - rabbits must land on the first empty space after a jump - means *
 *           they can never jump over empty spaces.                          *
 *         - rabbits can never move without jumping over at least 1 obstacle,*
 *           thus they can't move to adjacent space.                         *
 *         - rabbits cannot jump over an empty hole.                         *
 *         - rabbits can jump over a fox no matter the orientation           *
 *           (tail/front/over the side).                                     *
 ****************************************************************************/

#ifndef JUMP_IN_HPP
#define JUMP_IN_HPP

#include <vector>           //m_solution, m_movingParts..
#include <map>              //m_players
#include <cstddef>          //size_t
#include <sstream>          // std::istringstream

#include "factory.hpp"      //m_deserializersFactory

namespace jump_in
{

class GamePart;
class MovingPart;
struct Rabbit;

enum side_t
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    NUM_OF_SIDES
};

inline side_t ToSideT(int integer);
inline side_t ToSideT(const char *str);
inline void PrintSideT(side_t toPrint);
inline side_t GetOppositeSide(side_t side);

struct Move
{
    explicit Move(MovingPart *player, side_t direction);
    MovingPart *m_player;
    side_t m_direction;
};

class Square
{
public:
    explicit Square();
//    ~Square(); default

    void InitSquare(Square *up, Square *down, Square *left, Square *right,
                    uint8_t row, uint8_t column);
    void Print() const;
    void PlacePart(GamePart *part);
    void SetHole(bool isHole=true);
    Square *GetNeighbor(side_t side) const;
    uint8_t GetRow() const;
    uint8_t GetColumn() const;
    Move AskToLeave(int beginFrom= UP);
    void MovePartAside(side_t side);

    bool IsEmpty() const;
    bool IsHole() const;

private:
    Square *m_neighbors[NUM_OF_SIDES];
    GamePart *m_part;
    uint8_t m_row;
    uint8_t m_column;
    bool m_isHole;
};

class Game : private boost::noncopyable
{
public:
    explicit Game(const std::string& levelsFileName="levels_file");
    //TODO for debug /*"/home/orpaz/orpaz-houta/jump_in/levels_file"*/
    ~Game();

    void Play(size_t level=1);
    void Solve();
    bool Check() const;

    template<typename PART>
    void AddNewPart(const std::string& key);
    GamePart *Deserialize(std::istream& in) const;

    inline static void RabbitEntersAHole();
    inline static void RabbitLeaveHole();

private:

    void InitBoard();
    void InsertNewPartToBoard(std::istream &in, std::string key);
    void PlaceInBoard(GamePart *newObj);
    void SetBoard(size_t level);
    void PrintBoard() const;
    void PrintRules() const;
    void ClearBoard();

    void GetInput();

    void BackTracking();
    void CancelMove();
    void CancelHelp(MovingPart *lastRabbit);
    bool IsReverseLastMove(MovingPart *player, side_t direction) const;
    void TryFillSquare(Rabbit *player, Square *toFill, side_t direction);
    void TryJumpCloser(Rabbit *player, Square *toFill, side_t direction);
    void TryOtherOps(Rabbit *player, side_t direction);
//    void TryClearSquare(Rabbit *player, Square *toFill, side_t direction);

    void PrintSolution() const;
    void AddMoveToSolution(MovingPart *player, side_t direction);

    static const int ROWS = 5;//TODO maybe change to template
    static const int COLUMNS = 5;

    Square m_board[ROWS][COLUMNS];

    std::vector<Move> m_solution;
    std::vector<MovingPart *> m_movingParts;
    std::vector<GamePart *> m_staticParts;
    std::vector<Rabbit *> m_rabbits;
    std::vector<std::string> m_levels;
    std::map<std::string, MovingPart *> m_players;

    ilrd::project::
    Factory<GamePart, std::string, std::istream& >m_deserializersFactory;

    static size_t m_rabbitsInHole;
    size_t m_minimumMoves;
    size_t m_numOfMovingParts;
    bool m_stop;
};


//////////////////////// Game's parts abstract Classes ///////////////////////

class GamePart
{
public:
    explicit GamePart(uint8_t row, uint8_t column);
    virtual ~GamePart();

    virtual void Print() const=0;
    int GetRow() const;
    int GetColumn() const;
    virtual void LeaveSpace();
    virtual void SettleInSpace(Square *newSpace);
    const Square& GetSpace() const;
    virtual Square *GetNeighbor(side_t direction) const;

private:
    Square *m_space;
    uint8_t m_FirstRow;
    uint8_t m_FirstColumn;
};

class MovingPart : public GamePart
{
public:
    MovingPart(uint8_t row, uint8_t column, size_t PartId);

    virtual side_t CanMoveTo(const Square& destination) const=0;
    virtual bool CanMoveFrom(side_t direction) const=0;
    virtual Square *IsLegalMove(side_t direction) const=0;
    virtual void Move(side_t direction)=0;
    size_t GetId() const;

    void PrintId() const;

private:
    size_t m_id;
};

/////////////////////////// Game's parts Classes /////////////////////////////

class Mushroom : public GamePart
{
public:
    explicit Mushroom(uint8_t row, uint8_t column);
    virtual ~Mushroom();

    static GamePart *Deserialize(std::istream& in);
    virtual void Print() const;
};

class Fox : public MovingPart
{
public:
    explicit Fox(uint8_t row, uint8_t column, side_t direction, bool isTail = false);
    virtual ~Fox();

    static GamePart *Deserialize(std::istream& in);
    virtual void Print() const;
    virtual void Move(side_t direction);
    virtual Square *IsLegalMove(side_t direction) const;
    virtual void LeaveSpace();
    virtual void SettleInSpace(Square *newSpace);
    virtual side_t CanMoveTo(const Square& destination) const;
    virtual bool CanMoveFrom(side_t direction) const;
    virtual Square *GetNeighbor(side_t direction) const;

private:
    Fox *m_tail;
    side_t m_direction;
    static size_t m_numOfOfFoxes;
};

class Rabbit : public MovingPart
{
public:
    explicit Rabbit(uint8_t row, uint8_t column);
    virtual ~Rabbit();

    static GamePart *Deserialize(std::istream& in);
    virtual void Print() const;
    virtual void Move(side_t direction);
    virtual Square *IsLegalMove(side_t direction) const;
    static size_t GetNumOfRabbits();
    virtual void LeaveSpace();
    virtual void SettleInSpace(Square *newSpace);
    virtual side_t CanMoveTo(const Square& destination) const;
    virtual bool CanMoveFrom(side_t direction) const;
    void Jump(Square *newSpace);

private:
    static size_t m_numOfRabbits;
};

////////////////////////////// Static side_t Funcs ///////////////////////////
side_t ToSideT(int integer)
{
    switch (integer)
    {
        case 0: return UP;
        case 1: return RIGHT;
        case 2: return DOWN;
        case 3: return LEFT;
        default: throw std::invalid_argument("invalid int");
    }
}

void PrintSideT(side_t toPrint)
{
    switch (toPrint)
    {
        case UP: std::cout <<"️⏫"; break;
        case RIGHT: std::cout <<"️️⏩"; break;
        case DOWN: std::cout <<"️⏬"; break;
        case LEFT: std::cout <<"️⏪"; break;
        default: throw std::logic_error("invalid input");
    }
}

side_t GetOppositeSide(side_t side)
{
    return ToSideT((side + 2) % NUM_OF_SIDES);
}

side_t ToSideT(const char *str)
{
    if (!strcmp(str, "up"))
    {
        return UP;
    }
    else if (!strcmp(str, "right"))
    {
        return RIGHT;
    }
    else if (!strcmp(str, "down"))
    {
        return DOWN;
    }
    else if (!strcmp(str, "left"))
    {
        return LEFT;
    }
    else
    {
        throw std::runtime_error("invalid input\n");
    }
}


}//namespace rabbit_hole

#endif //JUMP_IN_HPP
