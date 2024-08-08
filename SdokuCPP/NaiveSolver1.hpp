//
//  NaiveSolver.hpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#ifndef NaiveSolver1_hpp
#define NaiveSolver1_hpp

#include <stdio.h>
#include <vector>
#include "common.h"
#include "Solver.hpp"
using namespace std;
// 메모리 새롭게 생성하지 않기
class NaiveSolver1 : public Solver
{
private:
    int SolveSdoku(int* sdoku, vector<COORD1> *emptyList) override;
    int SolveSdoku(int* sdoku, COORD1 *emptyList, int numEmptyList);
public:
    NaiveSolver1();
    ~NaiveSolver1(); 
};

#endif /* NaiveSolver1_hpp */
