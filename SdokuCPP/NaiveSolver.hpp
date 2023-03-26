//
//  NaiveSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#ifndef NaiveSolver_hpp
#define NaiveSolver_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;

class NaiveSolver : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD> *emptyList) override;
    
public:
    NaiveSolver();
    ~NaiveSolver(); 
};

#endif /* NaiveSolver_hpp */
