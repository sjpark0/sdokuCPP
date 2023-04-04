//
//  FastSolver3.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/27.
//

#ifndef FastSolver3_hpp
#define FastSolver3_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class FastSolver3 : public Solver
{
private:
    int m_initialEmptySize;
    int SolveSdoku(int* sdoku, vector<COORD> *emptyList) override;
    int SolveSdokuR(int* sdoku, vector<int> *availableList, vector<COORD> *emptyList);
    int AssignValue(int *sdoku, int x, int y, int val, vector<int> *availableList, vector<COORD> *emptyList);
    int RestoreValue(int x, int y, int val, vector<int> *availableList, vector<COORD> *emptyList);
    int GetAvailableNumber(int* sdoku, int i, int j, vector<int> *numList);
    
public:
    FastSolver3();
    ~FastSolver3();
    
    //void SolveSdoku(int* sdoku);
};

#endif /* FastSolver3_hpp */
