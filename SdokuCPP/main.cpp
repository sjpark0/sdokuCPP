//
//  main.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#include <iostream>
#include <sys/time.h>
#include "common.h"
#include "NaiveSolver.hpp"
#include "FastSolver.hpp"
#include "FastSolver2.hpp"
#include "FastSolver3.hpp"
#include "Solver.hpp"


int main(int argc, const char * argv[]) {
    int *sdoku = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    int *sdokuOriginal = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    
    memset(sdoku, 0, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    sdoku[1] = 9;
    sdoku[5] = 6;
    sdoku[8] = 5;
    sdoku[10] = 3;
    sdoku[12] = 4;
    sdoku[13] = 5;
    sdoku[16] = 8;
    sdoku[18] = 4;
    sdoku[23] = 2;
    sdoku[32] = 4;
    sdoku[36] = 3;
    sdoku[39] = 7;
    sdoku[40] = 9;
    sdoku[44] = 2;
    sdoku[46] = 8;
    sdoku[51] = 1;
    sdoku[54] = 7;
    sdoku[57] = 5;
    sdoku[58] = 3;
    sdoku[62] = 9;
    sdoku[67] = 6;
    sdoku[74] = 9;
    sdoku[79] = 2;
    
    memcpy(sdokuOriginal, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    
    timeval begin, end;
    long seconds, microseconds;
    double elapsed;
    
    Solver *solver = new NaiveSolver();
    //solver.GenerateSdoku(sdoku, 45);
    solver->PrintSdoku(sdoku);
    gettimeofday(&begin, NULL);
    solver->SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("NaiveSolver => Time measured: %.8f seconds.\n", elapsed);
    solver->PrintSdoku(sdoku);
    printf("\n");
    delete solver;
    
    memcpy(sdoku, sdokuOriginal, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    solver = new FastSolver();
    solver->PrintSdoku(sdoku);
    gettimeofday(&begin, NULL);
    solver->SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("FastSolver => Time measured: %.8f seconds.\n", elapsed);
    solver->PrintSdoku(sdoku);
    printf("\n");
    delete solver;
    
    memcpy(sdoku, sdokuOriginal, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    solver = new FastSolver2();
    solver->PrintSdoku(sdoku);
    gettimeofday(&begin, NULL);
    solver->SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("FastSolver2 => Time measured: %.8f seconds.\n", elapsed);
    solver->PrintSdoku(sdoku);
    printf("\n");
    delete solver;
    
    memcpy(sdoku, sdokuOriginal, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    solver = new FastSolver3();
    solver->PrintSdoku(sdoku);
    gettimeofday(&begin, NULL);
    solver->SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("FastSolver3 => Time measured: %.8f seconds.\n", elapsed);
    solver->PrintSdoku(sdoku);
    printf("\n");
    delete solver;
    delete []sdoku;
    delete []sdokuOriginal;
    
    /*vector<int> test;
    test.push_back(1);
    test.push_back(11);
    test.push_back(111);
    test.push_back(1111);
    test.push_back(11111);
    test.push_back(111111);
    
    vector<int>::iterator iter;
    for(iter = test.begin();iter != test.end();iter++){
        cout << (*iter) << endl;
    }
    cout << test.size() << endl;
    test.erase(remove(test.begin(), test.end(), 1), test.end());
    cout << test.size() << endl;
    
    for(iter = test.begin();iter != test.end();iter++){
        cout << (*iter) << endl;
    }*/
    
}
