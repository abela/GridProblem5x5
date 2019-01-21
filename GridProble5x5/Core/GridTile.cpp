//
//  GridTile.cpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "GridTile.h"
#include <iostream>

GridTile::GridTile(Point p) : m_position(p), m_value(-1)
{
    
}

GridTile::~GridTile()
{
    
}

Point GridTile::GetPosition()
{
    return m_position;
}

void GridTile::SetPosition(Point p)
{
    this->m_position = p;
}

int GridTile::GetValue()
{
    return m_value;
}

void GridTile::SetValue(int value)
{
    this->m_value = value;
}

// use for debug
void GridTile::PrintValue()
{
    std::cout<<m_value;
}

