//
//  NaiveSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#ifndef NaiveSolver_0_hpp
#define NaiveSolver_0_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;
// 메모리 새롭게 생성하지 않기
class NaiveSolver_0 : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int SolveSdoku(int* sdoku, COORD1 *emptyList, int numEmptyList);
public:
    NaiveSolver_0();
    ~NaiveSolver_0();
};

#endif /* NaiveSolver_0_hpp */
