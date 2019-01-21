//
//  Piece.hpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#ifndef Piece_h
#define Piece_h

#include "GridTile.h"

class Piece : public GridTile {
private:
    // is element special one?
    bool m_SpecialOne;
public:
    // constructor and destructor
    Piece(Point p);
    ~Piece();

    void SetSpecialOne(bool specialOne); // is special one SETTER
    bool ISpecialOne(); // is special one GETTER
};

#endif /* Piece_hpp */
