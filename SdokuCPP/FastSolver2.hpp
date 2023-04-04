//
//  FastSolver2.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/27.
//

#ifndef FastSolver2_hpp
#define FastSolver2_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class FastSolver2 : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD> *emptyList) override;
    int GetAvailableNumber(int* sdoku, int i, int j, vector<int> *numList);
    
public:
    FastSolver2();
    ~FastSolver2();
    
    //void SolveSdoku(int* sdoku);
};

#endif /* FastSolver2_hpp */
