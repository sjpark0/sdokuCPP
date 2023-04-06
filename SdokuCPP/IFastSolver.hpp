//
//  IFastSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/06.
//

#ifndef IFastSolver_hpp
#define IFastSolver_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class IFastSolver : public Solver
{
private:
	vector<vector<COORD1>*> m_vecSolved;
    int m_initialEmptySize;
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int SolveSdokuR(vector<COORD1> *assignList, vector<int> *availableList, vector<COORD1> *emptyList);
    int AssignValue(vector<COORD1> *assignList, int x, int y, int val, vector<int> *availableList, vector<COORD1> *emptyList);
    int GetAvailableNumber(int* sdoku, int i, int j, vector<int> *numList);
    
public:
	IFastSolver();
    ~IFastSolver();
    
    //void SolveSdoku(int* sdoku);
};

#endif /* IFastSolver_hpp */