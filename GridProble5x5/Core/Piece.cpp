//
//  Piece.cpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "Piece.h"

Piece::Piece(Point p) : GridTile(p)
{
}
Piece::~Piece()
{
    
}

bool Piece::ISpecialOne()
{
    return m_SpecialOne;
}

void Piece::SetSpecialOne(bool specialOne)
{
    m_SpecialOne = specialOne;
}
