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
// numList가 숫자만이 아니라 각 숫자에 대해 available하면 1, 아니면 0값을 갖도록 함
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
