//
//  Grid.cpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "Grid.h"

Grid::Grid(int piecesCount, int minimumMoveCount) : m_totalPiecesCount(piecesCount),
                                                    m_minimumMoveCount(minimumMoveCount),
                                                    m_movementCounter(0),
                                                    m_lastMovePosition(-1,-1),
                                                    m_movementEnded(false),
                                                    m_invalidCombination(false)
{
    // initialize grid tiles
    InitTiles();
}

void Grid::InitTiles()
{
    // create grid and
    for (int j = 0; j < TILES_COUNT; ++j)
    {
        for (int i = 0; i < TILES_COUNT; ++i) {
            Point pos(i,j);
            m_tiles[i][j].reset(new GridTile(pos));
        }
    }
}

Grid::~Grid()
{
    // release pieces array
    for (int i = 0; i < m_piecesArray.size(); ++i) {
        m_piecesArray[i].reset();
    }
    // delete main grid
    for (int j = 0; j < TILES_COUNT; ++j)
    {
        for (int i = 0; i < TILES_COUNT; ++i) {
            m_tiles[i][j].reset();
        }
    }
    
}

void Grid::Generate()
{
    // check input parameters
    // there are imediate invalid moves in some cases:
    // when m_minimumMoveCount == 0 || m_totalPiecesCount <= 1
    if(m_minimumMoveCount == 0 || m_totalPiecesCount <= 1 || m_totalPiecesCount > MAXIMUM_PIECES_COUNT)
        std::cout<<"No available moves!"<<std::endl;
    else
    {
        // set grid first state
        InitFirstState();
        //
        // run every next grid state
        SetNextState();
        //
        //when moving pieces handle invalid combination
        if(m_invalidCombination)
            std::cout<<"No available moves!"<<std::endl;
        else // print final result after grid generate
            PrintFinalResult();
    }
}

void Grid::PrintFinalResult()
{
    // if total pieces count more than minimum move count, arrange other elements on the edge of the grid
    // all possible edge
    Point randomEdges[TILES_COUNT - 1] = {
        Point(0,0),
        Point(0,TILES_COUNT - 1),
        Point(TILES_COUNT - 1,TILES_COUNT - 1),
        Point(TILES_COUNT - 1,0)
    };
    //
    // add missed elements to final array
    for (int edgesCounter = 0, i = (int)m_piecesArray.size(); i < m_totalPiecesCount; ++i, ++edgesCounter) {
        std::unique_ptr<Piece> piece(new Piece(randomEdges[edgesCounter]));
        m_piecesArray.push_back(std::move(piece));
    }
    
    // print final result - initial elements position
    for(int i =0; i < m_piecesArray.size(); ++i)
    {
        std::cout<<std::to_string(m_piecesArray[i]->GetPosition().X())<<","<<std::to_string(m_piecesArray[i]->GetPosition().Y())<<" ";
    }
    std::cout<<std::endl<<std::endl;
    //
    // print puzzle commands
    for (int i = 0; i<m_moveCommands.size(); i++) {
        std::cout<<m_moveCommands[i]<<" ";
    }
    //
    std::cout<<std::endl;
    //
}

// initialize first grid state
// first ever move - assign special piece position to the middle of deck
// and add some normal piece to neighrbour position (up , down , left, or right)
void Grid::InitFirstState()
{
    //
    // create special piece at the center of the grid to move backward
    Point pos(TILES_COUNT/2,TILES_COUNT/2);
    std::unique_ptr<Piece> specialPiece(new Piece(pos));
    specialPiece->SetSpecialOne(true);
    //
    // add piece to the pieces array
    m_piecesArray.push_back(std::move(specialPiece));
    //
    // create one normal piece at random position from special one ( we can choose 4 sides at start from center)
    // up / down / left / right
    Point p[4] = {
        Point(m_piecesArray[0]->GetPosition().X(),m_piecesArray[0]->GetPosition().Y() + 1),
        Point(m_piecesArray[0]->GetPosition().X() + 1,m_piecesArray[0]->GetPosition().Y()),
        Point(m_piecesArray[0]->GetPosition().X(),m_piecesArray[0]->GetPosition().Y() - 1),
        Point(m_piecesArray[0]->GetPosition().X() - 1,m_piecesArray[0]->GetPosition().Y())
    };
    //
    // create next piece with random neighbrhood from p indices array
    int randomIndex = arc4random()%4;
    std::unique_ptr<Piece> nextPiece(new Piece(p[randomIndex]));
    //
    // command string
    std::string command = "";
    //
    // index to move special one at some position
    Point nextIndex(-1,-1);
    //
    // move special one
    // move left if first nonspecial is on the right
    if(m_piecesArray[0]->GetPosition().X() < nextPiece->GetPosition().X())
    {
        // set move command
        command = std::to_string(0)+"R";
        // move special piece
        nextIndex.Set(m_piecesArray[0]->GetPosition().X() - 1,m_piecesArray[0]->GetPosition().Y());
    }
    //
    // move Right if first nonspecial is on the left
    else if(m_piecesArray[0]->GetPosition().X() > nextPiece->GetPosition().X())
    {
        // add movement command
        command = std::to_string(0)+"L";
        // move special piece
        nextIndex.Set(m_piecesArray[0]->GetPosition().X() + 1,m_piecesArray[0]->GetPosition().Y());
    }
    //
    // move down if first nonspecial is on the top
    if(m_piecesArray[0]->GetPosition().Y() < nextPiece->GetPosition().Y())
    {
        // set movement command
        command = std::to_string(0)+"U";
        // move special piece
        nextIndex.Set(m_piecesArray[0]->GetPosition().X(),m_piecesArray[0]->GetPosition().Y()-1);
    }
    //
    // move up if first nonspecial is on the bottom
    else if(m_piecesArray[0]->GetPosition().Y() > nextPiece->GetPosition().Y())
    {
        // set move command
        command = std::to_string(0)+"D";
        // move special piece
        nextIndex.Set(m_piecesArray[0]->GetPosition().X(),m_piecesArray[0]->GetPosition().Y()+1);
    }
    //
    // assign grid position that we alredy have been occupied by pieces - (2 is occupied, 1 is visited)
    m_tiles[nextPiece->GetPosition().X()][nextPiece->GetPosition().Y()]->SetValue(2);
    //
    // update special one's position
    UpdateSpecialOnesPosition(nextIndex);
    //
    // add movement command in commands array (add every command at start of the array)
    StoreMoveCommand(command);
    // store piece in array
    m_piecesArray.push_back(std::move(nextPiece));
    //
    // increase current move count
    m_movementCounter++;
    //
}

void Grid::SetNextState()
{
    // check if we finished movement, or there is a invalid combination
    if(m_movementEnded || m_invalidCombination)
        return;
    
    // check if we havent'been on this place yet on the grid
    if(m_tiles[m_piecesArray[0]->GetPosition().X()][m_piecesArray[0]->GetPosition().Y()]->GetValue()==-1)
    {
        // detect next neighbour position - should it be horizontal, or vertical:
        // if last movement is horizontal to current position next neighbour should vertical
        // check for horizontal
        if(m_lastMovePosition.Y() == m_piecesArray[0]->GetPosition().Y())
        {
            // two possible position, upper and bottom
            int possibleIndices[2] = { m_piecesArray[0]->GetPosition().Y() - 1, m_piecesArray[0]->GetPosition().Y() + 1};
            //
            bool freeMovementChanged = false;
            // check if grid position on some of that positions is already taken by some piece, change move direction
            // check 1
            if(m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[0]]->GetValue()==2)
            {
                ChangeMoveDirection(m_piecesArray[0]->GetPosition().X(),possibleIndices[1], "0D");
                freeMovementChanged = true;
            }
            // check 2
            else if(m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[1]]->GetValue()==2)
            {
                ChangeMoveDirection(m_piecesArray[0]->GetPosition().X(),possibleIndices[0], "0U");
                freeMovementChanged = true;
            }
            // call the recursion if movement has changed
            if(freeMovementChanged)
                SetNextState();
            //
            // maybe neighbours are fresh, or we've been before there (checking verticals)
            if(m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[0]]->GetValue() != 2
               && m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[1]]->GetValue() != 2
               && m_movementCounter < m_minimumMoveCount)
            {
                // create next normal piece
                int nextPossiblePositionY = -1;//possibleIndices[arc4random()%2];
                
                // if neighbours are fresh
                if(m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[0]]->GetValue() == -1 &&
                   m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[1]]->GetValue() == -1)
                {
                    nextPossiblePositionY = RandomizeNextIndex(possibleIndices[0],possibleIndices[1]);
                }
                // or we've been there
                else
                {
                    nextPossiblePositionY = m_tiles[m_piecesArray[0]->GetPosition().X()][possibleIndices[0]]->GetValue() == 1 ?
                                            possibleIndices[1] : possibleIndices[0];
                }
                //
                // create new element
                std::unique_ptr<Piece> nextPiece(new Piece(Point(m_piecesArray[0]->GetPosition().X(), nextPossiblePositionY)));
                //
                // detect next move command and add it on the list
                std::string command = "";
                int nextSpecialPosition = -1;
                if(nextPossiblePositionY > m_piecesArray[0]->GetPosition().Y())
                {
                    nextSpecialPosition = m_piecesArray[0]->GetPosition().Y() - 1;
                    command = std::to_string(0) + "U";
                }
                else
                {
                    nextSpecialPosition = m_piecesArray[0]->GetPosition().Y() + 1;
                    command = std::to_string(0) + "D";
                }
                // insert move commands
                StoreMoveCommand(command);
                //
                // update special one's move position
                UpdateSpecialOnesPosition(Point(m_piecesArray[0]->GetPosition().X(),nextSpecialPosition));
                //
                // assign grid position that we alredy have been occupied by pieces
                m_tiles[nextPiece->GetPosition().X()][nextPiece->GetPosition().Y()]->SetValue(2);
                //
                // add new element into array
                m_piecesArray.push_back(std::move(nextPiece));
                //
                // check invalid
                if(m_piecesArray.size() > m_totalPiecesCount)
                {
                    m_invalidCombination = true;
                    return;
                }
                //
                // increase current move count
                m_movementCounter++;
                //
                // call the recursion for updated parameters
                SetNextState();
            }
        }
        //
        //
        // if last movement is vertical to current position next neighbour should horizontal
        else if(m_lastMovePosition.X() == m_piecesArray[0]->GetPosition().X())
        {
            // two possible position, upper and bottom
            int possibleIndices[2] = { m_piecesArray[0]->GetPosition().X() - 1, m_piecesArray[0]->GetPosition().X() + 1};
            //
            bool freeMovementChanged = false;
            // check if grid position on some of that positions is already taken by some piece, change move direction
            // check 1
            if(m_tiles[possibleIndices[0]][m_piecesArray[0]->GetPosition().Y()]->GetValue()==2)
            {
                ChangeMoveDirection(possibleIndices[1], m_piecesArray[0]->GetPosition().Y(), "0L");
                freeMovementChanged = true;
            }
            // check 2
            else if(m_tiles[possibleIndices[1]][m_piecesArray[0]->GetPosition().Y()]->GetValue()==2)
            {
                ChangeMoveDirection(possibleIndices[0], m_piecesArray[0]->GetPosition().Y(), "0R");
                freeMovementChanged = true;
            }
            //// call the recursion if movement changed
            if(freeMovementChanged)
                SetNextState();
            //
            //// maybe neighbours are fresh, or we've been before there (checking horizontals)
            if(m_tiles[possibleIndices[0]][m_piecesArray[0]->GetPosition().Y()]->GetValue() != 2
               && m_tiles[possibleIndices[1]][m_piecesArray[0]->GetPosition().Y()]->GetValue() != 2
               && m_movementCounter < m_minimumMoveCount)
            {
                // create next normal piece
                int nextPossiblePositionX = -1;
                
                // if neighbours are fresh
                if(m_tiles[possibleIndices[0]][m_piecesArray[0]->GetPosition().Y()]->GetValue() == -1 &&
                   m_tiles[possibleIndices[1]][m_piecesArray[0]->GetPosition().Y()]->GetValue()  == -1)
                {
                    nextPossiblePositionX = RandomizeNextIndex(possibleIndices[0],possibleIndices[1]);
                }
                // or visited
                else
                {
                    nextPossiblePositionX = m_tiles[possibleIndices[0]][m_piecesArray[0]->GetPosition().Y()]->GetValue() == 1 ?
                    possibleIndices[1] : possibleIndices[0];
                }
                //
                // create new element on grid
                std::unique_ptr<Piece> nextPiece(new Piece(Point(nextPossiblePositionX,m_piecesArray[0]->GetPosition().Y())));
                //
                // occupy new point on grid by newly created element
                m_tiles[nextPiece->GetPosition().X()][nextPiece->GetPosition().Y()]->SetValue(2);
                //
                // Detect next command in list
                std::string command = "";
                int nextSpecialPosition = -1;
                if(nextPossiblePositionX > m_piecesArray[0]->GetPosition().X())
                {
                    nextSpecialPosition = m_piecesArray[0]->GetPosition().X() - 1;
                    command = std::to_string(0) + "R";
                }
                else
                {
                    nextSpecialPosition = m_piecesArray[0]->GetPosition().X() + 1;
                    command = std::to_string(0) + "L";
                }
                // insert move commands
                StoreMoveCommand(command);
                //
                // update special One's position
                UpdateSpecialOnesPosition(Point(nextSpecialPosition,m_piecesArray[0]->GetPosition().Y()));
                //
                // add it into array
                m_piecesArray.push_back(std::move(nextPiece));
                //
                // detect invalid combination
                if(m_piecesArray.size() > m_totalPiecesCount)
                {
                    m_invalidCombination = true;
                    return;
                }
                //
                // increase current move count
                m_movementCounter++;
                //
                // call the recursion for updated parameters
                SetNextState();
            }
        }
    }
    //
    // if we have been already on this position, just move
    else if(m_tiles[m_piecesArray[0]->GetPosition().X()][m_piecesArray[0]->GetPosition().Y()]->GetValue()==1)
    {
        // move special one
        int nextPos = FreeMoveSpecialOne();
        //
        // check if we are on the edge, finish movement
        if(nextPos == 0 || nextPos == TILES_COUNT - 1)
            m_movementEnded = true;
        else
            SetNextState();
    }
}

// change move direction of special one
void Grid::ChangeMoveDirection(int position_1,int position_2, std::string command)
{
    // check if we need more moves to count
    if(m_movementCounter<m_minimumMoveCount)
    {
        // update special one's position
        UpdateSpecialOnesPosition(Point(position_1,position_2));
        //
        // add movement command in commands array (add every command at start of the array)
        StoreMoveCommand(command);
        //
        // increase move counter
        m_movementCounter++;
    }
    else
    {
        // check special one stop
        CheckSpecialOneStop();
    }
}

// get next ranomized movement index on grid
int Grid::RandomizeNextIndex(int neighbourIndex_1, int neighbourIndex_2)
{
    int nextPossiblePositionX = -1;
    // detect if we are on vertical edges
    // bottom edge
    if(neighbourIndex_1 == 0)
        nextPossiblePositionX = 0;
    // upper edge
    else if(neighbourIndex_2 == TILES_COUNT - 1)
        nextPossiblePositionX = TILES_COUNT - 1;
    // if not just choose random
    else nextPossiblePositionX = arc4random()%2 == 0 ? neighbourIndex_1 : neighbourIndex_2;
    return nextPossiblePositionX;
}

// free movement of special one piece
int Grid::FreeMoveSpecialOne()
{
    int newPosCoord = -1;
    // if last movement is horizontal to current position next neighbour should vertical
    if(m_lastMovePosition.Y() == m_piecesArray[0]->GetPosition().Y())
    {
        // calculate next Direction
        int direction = m_piecesArray[0]->GetPosition().X() - m_lastMovePosition.X();
        int nextPosX = m_piecesArray[0]->GetPosition().X() + direction;
        // avoid edge intersection
        if(nextPosX > 0 && nextPosX < TILES_COUNT-1)
        {
            // update special One's position
            UpdateSpecialOnesPosition(Point(nextPosX, m_piecesArray[0]->GetPosition().Y()));
        }
        newPosCoord = nextPosX;
    }
    
    // if last movement is vertical to current position next neighbour should horizontal
    if(m_lastMovePosition.X() == m_piecesArray[0]->GetPosition().X())
    {
        // calculate next Direction
        int direction = m_piecesArray[0]->GetPosition().Y() - m_lastMovePosition.Y();
        int nextPosY = m_piecesArray[0]->GetPosition().Y() + direction;
        // avoid edge intersection
        if(nextPosY > 0 && nextPosY < TILES_COUNT-1)
        {
            // update special One's position
            UpdateSpecialOnesPosition(Point(Point(m_piecesArray[0]->GetPosition().X(),nextPosY)));
        }
        newPosCoord = nextPosY;
    }
    return newPosCoord;
}

// stop movement if we are on edge
void Grid::CheckSpecialOneStop()
{
    // just move special one by its old direction
    int nextPos = FreeMoveSpecialOne();
    // detect if we are on the edge
    if(nextPos == 0 || nextPos == TILES_COUNT - 1)
        m_movementEnded = true;
}
// update special one position, assign grid tiles as visited, save previous position
void Grid::UpdateSpecialOnesPosition(Point p)
{
    // save last position
    m_lastMovePosition.Set(m_piecesArray[0]->GetPosition().X(), m_piecesArray[0]->GetPosition().Y());
    //
    // after saving last movement point set grid tile as visited
    m_tiles[m_lastMovePosition.X()][m_lastMovePosition.Y()]->SetValue(1);
    //
    // assign new position to the special one
    m_piecesArray[0]->SetPosition(p);
}

// store move Command
void Grid::StoreMoveCommand(std::string command)
{
    // insert move commands in commands array
    m_moveCommands.insert(m_moveCommands.begin(),command);
}

// use for debug
void Grid::Print()
{
    for (int j = TILES_COUNT - 1; j>=0; j--)
    {
        for (int i = 0; i<TILES_COUNT; i++) {
            m_tiles[i][j]->PrintValue();
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
