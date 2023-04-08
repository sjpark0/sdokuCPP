//
//  FastSolver1.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/08.
//

#ifndef FastSolver1_hpp
#define FastSolver1_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class FastSolver1 : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int GetAvailableNumber(int* sdoku, int i, int j, int* numList, int m);
    
public:
    FastSolver1();
    ~FastSolver1();
    
    //void SolveSdoku(int* sdoku);
};
#endif /* FastSolver1_hpp */
