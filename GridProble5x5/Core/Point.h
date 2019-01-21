//
//  Point.hpp
//  MiniclipTest2
//
//  Created by Giorgi Abelashvili on 1/21/19.
//  Copyright © 2019 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

struct Point {
private:
    int x,y;
public:
    Point(int X, int Y);
    int X();
    int Y();
    void Set(int x, int y);
};

#endif /* Point_hpp */
