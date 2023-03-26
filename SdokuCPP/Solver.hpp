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
    void MakeSdoku(int* sdoku);
    void RemoveComponentSdoku(int* sdoku, int numRemove, vector<COORD> *emptyList);
    void DeleteSolvedList();
    virtual int SolveSdoku(int* sdoku, vector<COORD> *emptyList) = 0;
    
protected:
    vector<int*> m_solved;
    int GetAvailableNumber(int* sdoku, int i, int j, int* numList);
    
public:
    Solver();
    virtual ~Solver();
    
    void GenerateSdoku(int* sdoku, int numRemove);
    
    void PrintSdoku(int* sdoku);
    void SolveSdoku(int* sdoku);
    
    int* GetSdoku(int index);
    int GetNumOfSdoku();
};
#endif /* Solver_hpp */
