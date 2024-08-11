//
//  FastSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/26.
//

#ifndef FastSolver_0_hpp
#define FastSolver_0_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;
// 중간단계에서 availableList가 1개일경우 채우기 + 메모리 새로생성하지 않기
class FastSolver_0 : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    
public:
    FastSolver_0();
    ~FastSolver_0();
    
    //void SolveSdoku(int* sdoku);
};
#endif /* FastSolver_hpp */
