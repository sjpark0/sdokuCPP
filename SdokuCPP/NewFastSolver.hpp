//
//  NewFastSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/08.
//

#ifndef NewFastSolver_hpp
#define NewFastSolver_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

// FastSolver와 동일한 구조인데, sdoku를 리커시브하게 가져가지 않고, 초기 emptyList와 현재의 assignList를 이용하여 availableNumber계산 (Debug모드에서 가장빠름 - MacOS, Release모드에서 가장느림 - MacOS)
class NewFastSolver : public Solver
{
private:
    vector<vector<COORD1>*> m_assignList;
    int m_initialEmptySize;
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int SolveSdokuR(vector<COORD2> *originalEmptyList, vector<COORD1> *emptyList, vector<COORD1> *assignList);
    int AssignValue(int *sdoku, int x, int y, int val, vector<int> *availableList, vector<COORD1> *emptyList);
    int GetAvailableNumber(int y, int x, vector<COORD2> *originalEmptyList, vector<COORD1> *assignList, int *numList);
public:
    NewFastSolver();
    ~NewFastSolver();
    
    //void SolveSdoku(int* sdoku);
};
#endif /* NewFastSolver_hpp */
