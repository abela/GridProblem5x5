//
//  main.cpp
//  MiniclipTest2
//
//  Created by Giorgi Abelix Abelashvili on 12/24/17.
//  Copyright © 2017 Giorgi Abelix Abelashvili. All rights reserved.
//

#include <iostream>
#include "Grid.h"
#include <cstdlib>

int main(int argc, const char ** argv) {
    // Check arguments
    if(argv[1] == NULL || argv[2] == NULL)
    {
        std::cout << "arguments missing!" << std::endl;
        return 0;
    }
    //
    // convert input parameters to int
    int piecesCount = atoi(argv[1]);
    int minimumMoveCount = atoi(argv[2]);
    //
    // declare grid with input parameters
    Grid grid(piecesCount,minimumMoveCount);
    //
    // generate grid
    grid.Generate();
    
    return 0;
}
