/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <string>               //getline
#include <iostream>             //cout
#include <cstdlib>              //atoi

#include "jump_in.hpp"

namespace jump_in
{

////////////////////// Initialization Of Static members //////////////////////
size_t Rabbit::m_numOfRabbits = 0;
size_t Fox::m_numOfOfFoxes = 0;
size_t Game::m_rabbitsInHole = 0;

///////////////////////////// Game Public Methods ////////////////////////////

void Game::Play(size_t level)
{
    size_t numOfLevels = m_levels.size();
    PrintRules();
    for (size_t i = level; i < numOfLevels && !m_stop; ++i)
    {
        SetBoard(i);
        while (!Check() && !m_stop)
        {
            std::cout << "\n🚩🚩🚩🚩   level " << i << "   🚩🚩🚩🚩\n";
            PrintBoard();
            GetInput();
        }

        if (m_stop)
        {
            std::cout << "goodbye! see you letter..\n";
        }
        else
        {
            std::cout << "\nlevel solved in -" << m_solution.size() << "moves\n";
            std::cout << "while the minimum is- " << m_minimumMoves << "moves\n";
            PrintBoard();

            if (m_solution.size() == m_minimumMoves)
            {
                std::cout << "🏆🏆🏆 congratulation!! 🏆🏆🏆\n";
            }
            else
            {
                std::cout << "you can do it better\n";
            }

            std::cout << "the path was - ";
            PrintSolution();
        }
    }
    if (!m_stop)
    {
        std::cout << "whooohooooo!!! you finish the game\n";
        std::cout << "🥁🥁🎺🎺🎺️🎖🎖️🎖🎺🎺🎺🥁🥁\n";
    }
}

void Game::Solve()
{
    boost::chrono::steady_clock::time_point start =
            boost::chrono::high_resolution_clock::now();

    BackTracking();

    boost::chrono::steady_clock::time_point stop =
            boost::chrono::high_resolution_clock::now();

    boost::chrono::microseconds duration =
            boost::chrono::duration_cast<boost::chrono::microseconds> (stop - start);

    std::cout << "Time to solve: "
              << duration.count() << " microseconds" << std::endl;
}

bool Game::Check() const
{
    return (Rabbit::GetNumOfRabbits() == m_rabbitsInHole);
}

template<typename OBJECT>
void Game::AddNewPart(const std::string& key)
{
    m_deserializersFactory.Add(key, &OBJECT::Deserialize);
}

GamePart * Game::Deserialize(std::istream &in) const
{
    std::string typeKey;
    in >> typeKey;

    return m_deserializersFactory.Create(typeKey, in);
}

void Game::RabbitEntersAHole()
{
    ++m_rabbitsInHole;
}

void Game::RabbitLeaveHole()
{
    --m_rabbitsInHole;
}

///////////////////////////// Game Private Methods ////////////////////////////

void Game::InsertNewPartToBoard(std::istream &in, std::string key)
{
    GamePart *newObj = Deserialize(in);
    MovingPart *newMovingObj = dynamic_cast<MovingPart *>(newObj);
    if (newMovingObj)
    {
        key += boost::to_string(newMovingObj->GetId());
        m_players[key] = newMovingObj;
        Rabbit *newRabbit = dynamic_cast<Rabbit *>(newMovingObj);
        if (newRabbit)
        {
            m_rabbits.push_back(newRabbit);
        }
        else
        {
            m_movingParts.push_back(newMovingObj);
        }
    }
    else
    {
        m_staticParts.push_back(newObj);
    }

    PlaceInBoard(newObj);
}

void Game::SetBoard(size_t level)
{
    ClearBoard();

    //set the parts on the right place on board
    std::istringstream currLevel(m_levels[level]);

    std::string key;
    std::string minMoves;
    currLevel >> minMoves;
    m_minimumMoves = atoi(minMoves.c_str());

    std::string newObjStr;
    while (!currLevel.eof())
    {
        getline(currLevel, newObjStr, ',');
        std::istringstream newObjIn(newObjStr), forKey(newObjStr);
        forKey >> key;
        InsertNewPartToBoard(newObjIn, key);
    }

    m_numOfMovingParts = m_movingParts.size();
}

void Game::BackTracking()
{
    if (Rabbit::GetNumOfRabbits() == m_rabbitsInHole ||
        (m_solution.size() == m_minimumMoves))
    {
        return;
    }

    for (size_t i = 0; i < Rabbit::GetNumOfRabbits(); ++i)
    {
        Rabbit *player = m_rabbits[i];
        for (int side = UP; side < NUM_OF_SIDES; ++side)
        {
            if (Rabbit::GetNumOfRabbits() == m_rabbitsInHole)
            {
                return;
            }
            side_t direction = ToSideT(side);
            Square *playerNext = player->GetNeighbor(direction);

            //case playerNext is NULL (outside the board) do nothing
            if (playerNext != NULL)
            {
                //case this is the side player came from, check for other ops
                if (IsReverseLastMove(player, direction))
                {
                    TryOtherOps(player, direction);
                }
                else
                {
                    //case nextSpace is empty check if any of the other
                    //parts can come so the rabbit could jump over
                    if (playerNext->IsEmpty())
                    {
                        TryFillSquare(player, playerNext, direction);
                    }
                    else
                    {
                        Square *newPose = player->IsLegalMove(direction);
                        if (newPose != NULL)
                        {
                            player->Jump(newPose);
                            AddMoveToSolution(player, direction);

                            BackTracking();

                            if (Rabbit::GetNumOfRabbits() == m_rabbitsInHole)
                            {
                                return;
                            }
                            // cancel last rabbit's move & look for other ops
                            CancelMove();

                            TryOtherOps(player, direction);
                        }
                        else
                        {
                            //before gave up this move entirely try jump closer
                            for(Square *closer = playerNext->GetNeighbor(direction);
                                closer != NULL && !closer->IsEmpty();
                                closer = closer->GetNeighbor(direction))
                            {
                                TryJumpCloser(player, closer, direction);
                            }
                        }
                    }

                }
            }

        }
    }
}

Game::Game(const std::string& levelsFileName) : m_minimumMoves(0),
                                                m_numOfMovingParts(0), m_stop(false)
{
    std::fstream levelsFile;
    levelsFile.open(levelsFileName.c_str(), std::ios::in);

    if (!levelsFile)
    {
        throw std::runtime_error("No file has been found at the given path\n");
    }

    while (!levelsFile.eof())
    {
        std::string newLevel;
        getline(levelsFile, newLevel, ';');
        m_levels.push_back(newLevel);
    }
    levelsFile.close();

    AddNewPart<Rabbit>("rabbit");
    AddNewPart<Mushroom>("mushroom");
    AddNewPart<Fox>("fox");

    InitBoard();
}

Game::~Game()
{
    ClearBoard();
}

void Game::PrintBoard() const
{
    for (size_t i = 0; i < COLUMNS; ++i)
    {
        std::cout << "├─────";
    }
    std::cout << "├" << std::endl;
    for (size_t row = 0; row < ROWS; ++row)
    {
        for (size_t column = 0; column < COLUMNS; ++column)
        {
            m_board[row][column].Print();
        }
        std::cout << "│" <<  std::endl;
        for (size_t j = 0; j < COLUMNS; ++j)
        {
            std::cout << "├─────";
        }
        std::cout << "├" << std::endl;
    }
}

void Game::InitBoard()
{
    /*------------------------------- Init Squares ---------------------------*/
    //init first row
    m_board[0][0].InitSquare(
            NULL, &m_board[1][0], NULL, &m_board[0][1], 0, 0);

    for (size_t j = 1; j < (COLUMNS-1); ++j)
    {
        m_board[0][j].InitSquare(NULL, &m_board[1][j],
                                 &m_board[0][j-1], &m_board[0][j+1], 0, j);
    }

    m_board[0][COLUMNS-1].InitSquare(
            NULL, &m_board[1][(COLUMNS-1)], &m_board[0][COLUMNS-2], NULL,
            0,COLUMNS-1);

    //init middle rows
    for (size_t i = 1; i < (ROWS-1); ++i)
    {
        m_board[i][0].InitSquare(
                &m_board[i-1][0], &m_board[i+1][0], NULL, &m_board[i][1],
                i,0);

        for (size_t j = 1; j < (COLUMNS-1); ++j)
        {
            m_board[i][j].InitSquare(&m_board[i-1][j], &m_board[i+1][j],
                                     &m_board[i][j-1], &m_board[i][j+1], i, j);
        }

        m_board[i][(COLUMNS-1)].InitSquare(&m_board[i-1][(COLUMNS-1)],
                                           &m_board[i+1][(COLUMNS-1)],
                                           &m_board[i][COLUMNS-2], NULL,
                                           i,COLUMNS-1);

        //init last row
        m_board[ROWS-1][0].InitSquare(&m_board[ROWS-2][0], NULL, NULL,
                                      &m_board[ROWS-1][1], ROWS-1, 0);

        for (size_t j = 1; j < (COLUMNS-1); ++j)
        {
            m_board[ROWS-1][j].InitSquare(
                    &m_board[ROWS-2][j], NULL,
                    &m_board[ROWS-1][j-1], &m_board[ROWS-1][j+1], ROWS-1, j);
        }

        m_board[ROWS-1][COLUMNS-1].InitSquare(
                &m_board[ROWS-2][COLUMNS-1], NULL,
                &m_board[ROWS-1][COLUMNS-2], NULL, ROWS-1, COLUMNS-1);
    }

    /*------------------------------- Set Holes ------------------------------*/
    std::istringstream currLevel(m_levels[0]);

    std::string row;
    std::string column;

    while (!currLevel.eof())
    {
        currLevel >> row;
        currLevel >> column;
        m_board[atoi(row.c_str())][atoi(column.c_str())].SetHole();
    }
}

void Game::ClearBoard()
{
    while (!m_movingParts.empty())
    {
        MovingPart *toDel = m_movingParts.back();
        delete toDel;
        m_movingParts.pop_back();
    }

    while (!m_staticParts.empty())
    {
        GamePart *toDel = m_staticParts.back();
        delete toDel;
        m_staticParts.pop_back();
    }

    while (!m_rabbits.empty())
    {
        Rabbit *toDel = m_rabbits.back();
        delete toDel;
        m_rabbits.pop_back();
    }

    m_solution.clear();

    Game::m_rabbitsInHole = 0;
}

void Game::PrintSolution() const
{
    size_t numOfMoves = m_solution.size();
    for (size_t i = 0; i < numOfMoves; ++i)
    {
        if (!(i%10))
        {
            std::cout << std::endl;
        }
        PrintSideT(m_solution[i].m_direction);
        m_solution[i].m_player->Print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

bool Game::IsReverseLastMove
        (MovingPart *player, side_t direction) const
{
    if (!m_solution.empty())
    {
        Move lastMove = m_solution.back();
        if (lastMove.m_player == player)
        {
            if (GetOppositeSide(lastMove.m_direction) == direction)
            {
                return true;
            }
        }
    }

    return false;
}

void Game::PlaceInBoard(GamePart *newObj)
{
    if (ROWS <= newObj->GetRow() || COLUMNS <= newObj->GetColumn())
    {
        throw std::out_of_range("try to put part outside the board");
    }

    newObj->SettleInSpace(&m_board[newObj->GetRow()][newObj->GetColumn()]);
}

void Game::AddMoveToSolution(MovingPart *player, side_t direction)
{
    Move newMove(player, direction);
    m_solution.push_back(newMove);
//    PrintSolution();//TODO
}

void Game::TryFillSquare(Rabbit *player, Square *toFill, side_t direction)
{
    if (m_solution.size() >= m_minimumMoves-1)
    {
        return;
    }
    for (size_t i = 0; i < m_numOfMovingParts; ++i)
    {
        MovingPart *helper = m_movingParts[i];
        side_t helpDirection = helper->CanMoveTo(*toFill);
        //case it is possible for helper to fill the wanted space
        if (helpDirection != NUM_OF_SIDES && !IsReverseLastMove(helper, helpDirection))
        {
            //case helper needs to move more then once to arrive
            while (m_solution.size() < m_minimumMoves-1 && toFill->IsEmpty())
            {
                helper->Move(helpDirection);
                AddMoveToSolution(helper, helpDirection);
            }
            //check if the help made was enough to fill toFill
            if (!toFill->IsEmpty())
            {
                Square *neighbor = player->GetNeighbor(direction);

                //check if the path to toFill still legal
                while (neighbor != toFill && !neighbor->IsEmpty())
                {
                    neighbor = neighbor->GetNeighbor(direction);
                }
                //case something got wrong, try to fill the emptiness
                if (neighbor != toFill)
                {
                    TryFillSquare(player, neighbor, direction);
                }
                    //case everything is o.k jump to toFill
                else
                {
                    //case toFill is neighbor check if the move legel..
                    if (player->IsLegalMove(direction))
                    {
                        AddMoveToSolution(player, direction);
                        player->Move(direction);

                        BackTracking();
                        if (Rabbit::GetNumOfRabbits() == m_rabbitsInHole)
                        {
                            return;
                        }
                        CancelMove();
                    }
                    //case toFill is right next to player but there is no
                    // where to jump to, try jump closer
                    for(Square *closer = toFill->GetNeighbor(direction);
                        closer != NULL && !closer->IsEmpty();
                        closer = closer->GetNeighbor(direction))
                    {
                        TryJumpCloser(player, closer, direction);
                    }
                }
            }
            //cancel the help if it wasn't enough
            CancelHelp(helper);
        }
    }
}

void Game::TryJumpCloser(Rabbit *player, Square *newPose, side_t direction)
{
    if (m_solution.size() >= m_minimumMoves-1)
    {
        return;
    }
    Move leavingMove = newPose->AskToLeave();//TODO
    //keep trying options(other directions etc..) while there is enough moves
    while (leavingMove.m_player != NULL && m_solution.size() < m_minimumMoves-1)
    {
        leavingMove.m_player->Move(leavingMove.m_direction);
        m_solution.push_back(leavingMove);
//        PrintSolution();//TODO

        //case obstacle (for instance fox) needs to move more then once
        while (!newPose->IsEmpty() && m_solution.size() < m_minimumMoves-1)
        {
            leavingMove.m_player->Move(leavingMove.m_direction);
            m_solution.push_back(leavingMove);
//            PrintSolution();//TODO
        }
        //case the obstacle was removed properly
        if (player->IsLegalMove(direction) && newPose->IsEmpty())
        {
            AddMoveToSolution(player, direction);
            player->Jump(newPose);

            BackTracking();
            if (Rabbit::GetNumOfRabbits() == m_rabbitsInHole)
            {
                return;
            }
            CancelMove();
        }
        //cancel the moves made in the last try to remove the obstacle
        CancelHelp(leavingMove.m_player);
        //check if the obstacle can leave to other direction
        leavingMove = newPose->AskToLeave(leavingMove.m_direction+1);
    }
}

void Game::TryOtherOps(Rabbit *player, side_t direction)
{
    //no need to check validation of first neighbor
    Square *lastJump = player->IsLegalMove(direction);
    Square *newPose = lastJump->GetNeighbor(direction);
    Square *playerNeighbor = player->GetNeighbor(direction);
    side_t opossiteDirection = GetOppositeSide(direction);

    //check if it is possible to jump further with help
    if (newPose != NULL && newPose->IsEmpty())
    {
        TryFillSquare(player, lastJump, direction);
    }
    //case last jump was over more then one square, try make
    //obstacle to leave so player could jump closer
    for (lastJump = lastJump->GetNeighbor(opossiteDirection);
         lastJump != playerNeighbor;
         lastJump = lastJump->GetNeighbor(opossiteDirection))
    {
        TryJumpCloser(player, lastJump, direction);
    }
}

void Game::CancelMove()
{
    Move lastMove = m_solution.back();
    lastMove.m_player->Move(GetOppositeSide(lastMove.m_direction));
    m_solution.pop_back();
//    PrintSolution();//TODO
}

void Game::CancelHelp(MovingPart *helper)
{
    for (Move lastMove = m_solution.back();
         !m_solution.empty() && helper == lastMove.m_player;
         lastMove = m_solution.back())
    {
        lastMove.m_player->Move(GetOppositeSide(lastMove.m_direction));
        m_solution.pop_back();
//            PrintSolution();//TODO
    }
}


/////////////////////////// Square Public Methods ////////////////////////////

void Square::InitSquare(Square *up, Square *down, Square *left, Square *right,
                        uint8_t row, uint8_t column)
{
    m_row = row;
    m_column = column;
    m_neighbors[UP] = up;
    m_neighbors[RIGHT] = right;
    m_neighbors[DOWN] = down;
    m_neighbors[LEFT] = left;
}

void Square::Print() const
{
    std::cout << "│ ";
    if (m_part != NULL)
    {
        m_part->Print();
    }
    else
    {
        if (m_isHole)
        {
            //std::cout << "🌰";
            std::cout << "🕳️  ";
        }
        else
        {
            std::cout << "   ";
        }
    }
    std::cout << " ";
}

Square::Square() : m_part(NULL), m_isHole(false)
{
    //empty
}

void Square::SetHole(bool isHole)
{
    m_isHole = isHole;
}

Square *Square::GetNeighbor(side_t side) const
{
    return m_neighbors[side];
}

void Square::PlacePart(GamePart *part)
{
    m_part = part;
}

bool Square::IsEmpty() const
{
    return (m_part == NULL);
}

bool Square::IsHole() const
{
    return m_isHole;
}

uint8_t Square::GetRow() const
{
    return m_row;
}

uint8_t Square::GetColumn() const
{
    return m_column;
}

Move Square::AskToLeave(int beginFrom)
{
    MovingPart *obstacle = dynamic_cast<MovingPart *>(m_part);
    if (obstacle != NULL)
    {
        for (int side = beginFrom; side < NUM_OF_SIDES; ++side)
        {
            side_t direction = ToSideT(side);
            if (obstacle->CanMoveFrom(direction))
            {
                return Move(obstacle, direction);
            }
        }
    }

    return Move(NULL, NUM_OF_SIDES);
}

void Square::MovePartAside(side_t side)
{
    MovingPart *toMove = dynamic_cast<MovingPart *>(m_part);
    if (toMove)
    {
        toMove->Move(side);
    }
}


///////////////////////////////// Game Parts /////////////////////////////////

GamePart::GamePart(uint8_t row, uint8_t column) :
        m_space(NULL), m_FirstRow(row), m_FirstColumn(column)
{
//empty
}

const Square &GamePart::GetSpace() const
{
    return *m_space;
}

void GamePart::LeaveSpace()
{
    m_space->PlacePart(NULL);
    m_space = NULL;
}

void GamePart::SettleInSpace(Square *newSpace)
{
    newSpace->PlacePart(this);
    m_space = newSpace;
}

GamePart::~GamePart()
{
    GamePart::LeaveSpace();
}

int GamePart::GetColumn() const
{
    return m_FirstColumn;
}

int GamePart::GetRow() const
{
    return m_FirstRow;
}

Square *GamePart::GetNeighbor(side_t direction) const
{
    return GetSpace().GetNeighbor(direction);
}

////////////////////////////// Mushroom's Methods ////////////////////////////
void Mushroom::Print() const
{
    std::cout << "🍄 ";
}

Mushroom::Mushroom(uint8_t row, uint8_t column) : GamePart(row, column)
{
//empty
}

Mushroom::~Mushroom()
{
//empty
}

GamePart *Mushroom::Deserialize(std::istream &in)
{
    std::string row;
    std::string column;

    in >> row;
    in >> column;

    return new Mushroom(atoi(row.c_str()), atoi(column.c_str()));
}

////////////////////////////////// MovingPart ////////////////////////////////
MovingPart::MovingPart(uint8_t row, uint8_t column, size_t PartId) :
        GamePart(row, column), m_id(PartId)
{
//empty
}

void MovingPart::PrintId() const
{
    std::cout << m_id;
}

size_t MovingPart::GetId() const
{
    return m_id;
}

//////////////////////////////// Fox's Methods ///////////////////////////////
void Fox::Print() const
{
    std::cout << "🦊";
    PrintId();
}

Fox::Fox(uint8_t row, uint8_t column, side_t direction, bool isTail) :
        MovingPart(row, column, m_numOfOfFoxes+1), m_direction(direction)
{
    if (isTail)
    {
        m_tail = NULL;
        ++m_numOfOfFoxes;
    }
    else
    {
        int tailRow = row;
        int tailColumn = column;

        switch (direction)
        {
            case UP: ++tailRow; break;
            case RIGHT: --tailColumn; break;
            case DOWN: --tailRow; break;
            case LEFT: ++tailColumn; break;
            default: throw std::runtime_error("bad input no such side");
        }

        m_tail = new Fox(tailRow, tailColumn, direction, true);
    }
}

Fox::~Fox()
{
    if (m_tail != NULL)
    {
        --m_numOfOfFoxes;
        delete m_tail;
        m_tail = NULL;
    }
}

Square *Fox::IsLegalMove(side_t direction) const
{
    if (direction == m_direction && direction == GetOppositeSide(m_direction))
    {
        Square *newPlace = GetNeighbor(direction);
        if (newPlace->IsEmpty())
        {
            return newPlace;
        }
    }

    return NULL;
}

void Fox::SettleInSpace(Square *newSpace)
{
    GamePart::SettleInSpace(newSpace);
    m_tail->GamePart::SettleInSpace(GamePart::GetNeighbor(GetOppositeSide(m_direction)));
}

GamePart *Fox::Deserialize(std::istream &in)
{
    std::string row;
    std::string column;
    std::string direction;

    in >> row;
    in >> column;
    in >> direction;

    return new
            Fox(atoi(row.c_str()), atoi(column.c_str()),
                ToSideT(direction.c_str()));
}

void Fox::LeaveSpace()
{
    GamePart::LeaveSpace();
    m_tail->GamePart::LeaveSpace();
}

void Fox::Move(side_t direction)
{
    if (m_tail != NULL)
    {
        Square *newSpace = GamePart::GetNeighbor(direction);
        LeaveSpace();
        SettleInSpace(newSpace);
    }
    else
    {
        GamePart::GetNeighbor(m_direction)->MovePartAside(direction);
    }
}

side_t Fox::CanMoveTo(const Square &destination) const
{
    uint8_t destRow = destination.GetRow();
    uint8_t destColumn = destination.GetColumn();
    const Square *currSquare = &GetSpace();

    if (currSquare->GetRow() == destRow)
    {
        //case the fox is horizontal & on the same row
        if (m_direction == LEFT || m_direction == RIGHT)
        {
            //check which side the fox needs to move to get to destination
            side_t side = (currSquare->GetColumn() > destColumn) ? LEFT : RIGHT;
            for (currSquare = GetNeighbor(side);
                 currSquare != &destination && currSquare->IsEmpty();
                 currSquare = currSquare->GetNeighbor(side));
            //case it is possible to get to destination return the relevant side
            if (currSquare == &destination)
            {
                return side;
            }
        }
    }
    else if (currSquare->GetColumn() == destColumn)
    {
        //case the fox is vertical & on the same column
        if (m_direction == UP || m_direction == DOWN)
        {
            //check which side the fox needs to move to get to destination
            side_t side = (currSquare->GetRow() > destRow) ? UP : DOWN;
            for (currSquare = GetNeighbor(side);
                 currSquare != &destination && currSquare->IsEmpty();
                 currSquare = currSquare->GetNeighbor(side));
            //case it is possible to get to destination return the relevant side
            if (currSquare == &destination)
            {
                return side;
            }
        }
    }
    return NUM_OF_SIDES;
}

bool Fox::CanMoveFrom(side_t direction) const//TODO big..
{
    Square *nextSpace = GamePart::GetNeighbor(direction);
    if (nextSpace != NULL)
    {
        Square *nextNext = nextSpace->GetNeighbor(direction);
        //check if this fox can move to that direction
        if (nextNext != NULL && nextNext->IsEmpty())
        {
            if (direction == m_direction)
            {
                //if this is tail it's possible & if it's not check if next
                // space also empty
                return (m_tail == NULL || (nextSpace->IsEmpty()));
            }
            else if (direction == GetOppositeSide(m_direction))
            {
                return (m_tail != NULL || (nextSpace->IsEmpty()));
            }
        }
    }
    return false;
}

Square *Fox::GetNeighbor(side_t direction) const
{
    //case it is needed to skip the head or the tail
    if ((direction == m_direction && m_tail == NULL) ||
        (direction == GetOppositeSide(m_direction) && m_tail != NULL))
    {
        return GamePart::GetNeighbor(direction)->GetNeighbor(direction);
    }
    else
    {
        return GamePart::GetNeighbor(direction);
    }
}

//////////////////////////////// Rabbit's Methods ////////////////////////////
void Rabbit::Print() const
{
    std::cout << "🐰";
    PrintId();
}

Rabbit::Rabbit(uint8_t row, uint8_t column) :
        MovingPart(row, column, m_numOfRabbits+1)
{
    ++m_numOfRabbits;
}

////doesn't deal cases the requested move is illegal, use IsLegalMove before.
void Rabbit::Move(side_t direction)
{
    Square *newSpace = GetNeighbor(direction);
    while (!newSpace->IsEmpty())
    {
        newSpace = newSpace->GetNeighbor(direction);
    }
    LeaveSpace();
    SettleInSpace(newSpace);
}

Square *Rabbit::IsLegalMove(side_t direction) const
{
    Square rabbitSpace = GetSpace();
    Square *nextSpace = rabbitSpace.GetNeighbor(direction);

    if (nextSpace)
    {
        if (!(nextSpace->IsEmpty()))
        {
            for (Square *newPose = nextSpace->GetNeighbor(direction);
                 newPose != NULL; newPose = newPose->GetNeighbor(direction))
            {
                if (newPose->IsEmpty())
                {
                    return newPose;
                }
            }
        }
    }

    return NULL;
}

size_t Rabbit::GetNumOfRabbits()
{
    return m_numOfRabbits;
}

Rabbit::~Rabbit()
{
    --m_numOfRabbits;
}

void Rabbit::LeaveSpace()
{
    if (GetSpace().IsHole())
    {
        Game::RabbitLeaveHole();
    }
    GamePart::LeaveSpace();
}

void Rabbit::SettleInSpace(Square *newSpace)
{
    if (newSpace->IsHole())
    {
        Game::RabbitEntersAHole();
    }

    GamePart::SettleInSpace(newSpace);
}

GamePart *Rabbit::Deserialize(std::istream &in)
{
    std::string row;
    std::string column;

    in >> row;
    in >> column;

    return new Rabbit(atoi(row.c_str()), atoi(column.c_str()));
}

side_t Rabbit::CanMoveTo(const Square &destination) const
{
    return NUM_OF_SIDES;
}

void Rabbit::Jump(Square *newSpace)
{
    LeaveSpace();
    SettleInSpace(newSpace);
}

//to prevent loops within the algorithm, rabbits cannot help each other
bool Rabbit::CanMoveFrom(side_t direction) const
{
    return false;
}


Move::Move(MovingPart *player, side_t direction) :
        m_player(player), m_direction(direction)
{
//empty
}


void Game::GetInput()//TODO needs improvement..
{
    std::string input;
    std::cin >> input;

    if ("solve" == input)
    {
        while (!m_solution.empty())
        {
            CancelMove();
        }
        Solve();
    }
    else if ("undo" == input)
    {
        if (!m_solution.empty())
        {
            CancelMove();
        }
    }
    else if ("rules" == input)
    {
        PrintRules();
    }
    else if ("quit" == input)
    {
        m_stop = true;
    }
    else
    {
        MovingPart *chosenPart = NULL;
        try
        {
            chosenPart = m_players.at(input);
        }
        catch (std::out_of_range&)
        {
            std::cout << "bad input.. try again\n";
            return;
        }

        side_t chosenDirection = NUM_OF_SIDES;
        int direction;
        std::cin >> direction;

        switch (direction)
        {
            case 8: chosenDirection = UP; break;
            case 6: chosenDirection = RIGHT; break;
            case 2: chosenDirection = DOWN; break;
            case 4: chosenDirection = LEFT; break;
            default: std::cout << "there is no such direction.. try again, "
                                  "incloud the player you chose\n"; return;
        }
        if (chosenPart->IsLegalMove(chosenDirection))
        {
            chosenPart->Move(chosenDirection);
            AddMoveToSolution(chosenPart, chosenDirection);
        }
        else
        {
            std::cout << "you try to do illegal move! try again..\n";
        }
    }
}

void Game::PrintRules() const
{
    std::cout <<
 "* End of game - all the rabbits inside a hole.\n"
 "* Parts Rules:\n"
 "* Mushrooms - are stationary & cannot be moved (1 space)\n"
 "* Foxes - can only move backward or forward. foxes cannot jump over\n"
 "*         obstacles (2 spaces)\n"
 "* Rabbits - move by jumping horizontally or vertically over one or more\n"
 "*           spaces with obstacles (other rabbits, mushrooms, foxes or\n"
 "*           combination of these)\n"
 "*         - rabbits must land on the first empty space after a jump - means\n"
 "*           they can never jump over empty spaces.\n"
 "*         - rabbits can never move without jump over at least 1 obstacle,\n"
 "*           thus they can't move to adjacent space.\n"
 "*         - rabbits cannot jump over an empty hole.\n"
 "*         - rabbits can jump over a fox no matter the orientation\n"
 "*           (tail/front/over the side).\n\n"
 "* Game options -\n"
 "  1. 'solve' - to automatically solve the level\n"
 "* 2. 'rules' - to print the rules\n"
 "* 3. 'quit' - to quit the game\n"
 "* 4. 'undo' - to cancel the last movement\n"
 "* 5. to move parts on the board, write the name & the id of the part you\n"
 "*    wish to move, after that the direction you choose -\n"
 "*    8(up), 6(right), 2(down) 4(left)\n"
 "*    for example - 'rabbit1 8'\n\n"
 "*     GoodLuck!!\n\n";
}

}//namespace rabbit_hole

