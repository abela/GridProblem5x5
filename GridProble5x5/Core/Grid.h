//
//  Grid.hpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Grid_h
#define Grid_h
#include "Piece.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

#define TILES_COUNT 5
#define MAXIMUM_PIECES_COUNT  6

class Grid
{
public:
    Grid(int piecesCount, int minimumMoveCount);
    ~Grid();
    // generate grid
    void Generate();
    
private:
    // init grid tiles
    void InitTiles();
    
    // initialize first random state
    void InitFirstState();
    
    // store move Commands
    void StoreMoveCommand(std::string command);
    
    // update special One's position, save last movement position
    void UpdateSpecialOnesPosition(Point p);
    
    // get possible movement index on grid
    int RandomizeNextIndex(int neighbourIndex_1, int neighbourIndex_2);
    
    // change only move direction and add comand of special one (based on neighbours position)
    void ChangeMoveDirection(int position_1,int position_2, std::string command);
    
    // set Next Grid State
    void SetNextState();
    
    // print grid for debug
    void Print();
    
    // free movement of special one piece
    int FreeMoveSpecialOne();
    
    // stop movement if we are on edge
    void CheckSpecialOneStop();
    
    // print final result
    void PrintFinalResult();
    
private:
    // store total piece count
    int m_totalPiecesCount;
    
    // store minimum move count
    int m_minimumMoveCount;
    
    // each movement counter
    int m_movementCounter;
    
    // is special piece movement ended flag
    bool m_movementEnded;
    
    // invalid combination flag
    bool m_invalidCombination;
    
    // store last move point
    Point m_lastMovePosition;
    
    // pieces array
    std::vector<std::unique_ptr<Piece>> m_piecesArray;
    
    // grid tiles matrix
    std::unique_ptr<GridTile> m_tiles[TILES_COUNT][TILES_COUNT];
    
    // optimal moves array to output
    std::vector<std::string> m_moveCommands;
};

#endif /* Grid_h */
