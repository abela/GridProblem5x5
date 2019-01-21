//
//  GridTile.h
//  MiniclipTest2
//
//  Created by Giorgi Abelashvili on 1/21/19.
//  Copyright © 2019 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef GridTile_h
#define GridTile_h
#include "Point.h"

class GridTile
{
private:
    Point m_position;
    int m_value;
public:
    GridTile(Point p);
    ~GridTile();
    
    Point GetPosition();
    void SetPosition(Point p);
    
    int GetValue();
    
    void SetValue(int value);
    // use for debug
    void PrintValue();
};

#endif /* GridTile_h */
