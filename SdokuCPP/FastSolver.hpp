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
// 중간단계에서 availableList가 1개일경우 채우기
class FastSolver : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    
public:
    FastSolver();
    ~FastSolver();
    
    //void SolveSdoku(int* sdoku);
};
#endif /* FastSolver_hpp */
