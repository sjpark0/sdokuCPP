//
//  FastSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/26.
//

#ifndef FastSolver_hpp
#define FastSolver_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class FastSolver : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD> *emptyList) override;
    
public:
    FastSolver();
    ~FastSolver();
    
    //void SolveSdoku(int* sdoku);
};
#endif /* FastSolver_hpp */
