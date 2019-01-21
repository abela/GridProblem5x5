//
//  Point.cpp
//  MiniclipTest2
//
//  Created by Giorgi Abelashvili on 1/21/19.
//  Copyright © 2019 Giorgi Abelix Abelashvili. All rights reserved.
//

#include "Point.h"

Point::Point(int X, int Y)
{
    this->x = X;
    this->y = Y;
}
int Point::X()
{
    return x;
}
int Point::Y()
{
    return y;
}
void Point::Set(int x, int y)
{
    this->x = x;
    this->y = y;
}
