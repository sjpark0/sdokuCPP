//
//  NewFastSolver2.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/29.
//

#ifndef NewFastSolver2_hpp
#define NewFastSolver2_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;
// NewFastSolver + FastSolver3
class NewFastSolver2 : public Solver
{
private:
    vector<vector<COORD3>*> m_vecSolved;
    int m_initialEmptySize;
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int SolveSdoku(int* sdoku, vector<COORD3> *emptyList);
    
    int SolveSdokuR(vector<COORD3> *assignList, vector<COORD3> *emptyList);
    int AssignValue(vector<COORD3> *assignList, int x, int y, int val, vector<COORD3> *emptyList);
    int GetAvailableNumber(int* sdoku, int i, int j, vector<int> *numList);
    
public:
    NewFastSolver2();
    ~NewFastSolver2();
    
};

#endif /* NewFastSolver2_hpp */
