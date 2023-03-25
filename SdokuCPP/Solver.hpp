//
//  Solver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#ifndef Solver_hpp
#define Solver_hpp

#include <stdio.h>
#include <vector>
#include "common.h"

using namespace std;

class Solver
{
private:
    vector<int*> m_solved;
public:
    Solver();
    ~Solver();
    
    void MakeSdoku(int* sdoku);
    void GenerateSdoku(int* sdoku, int numRemove);
    int GetAvailableNumber(int* sdoku, int i, int j, int* numList);
    
    void RemoveComponentSdoku(int* sdoku, int numRemove, vector<COORD> *emptyList);
    void PrintSdoku(int* sdoku);
    int SolveSdoku(int* sdoku, vector<COORD> *emptyList);
    void SolveSdoku(int* sdoku);
    void DeleteSolvedList();
    
    int* GetSdoku(int index);
    int GetNumOfSdoku();
};
#endif /* Solver_hpp */
