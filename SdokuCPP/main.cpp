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
    
    NaiveSolver solver;
    
    //solver.GenerateSdoku(sdoku, 45);
    solver.PrintSdoku(sdoku);
    
    gettimeofday(&begin, NULL);
    solver.SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("Time measured: %.3f seconds.\n", elapsed);
    solver.PrintSdoku(sdoku);
    printf("\n");
    memcpy(sdoku, sdokuOriginal, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    
    Solver solver1;
    //solver1.GenerateSdoku(sdoku, 58);
    solver1.PrintSdoku(sdoku);
    
    gettimeofday(&begin, NULL);
    solver1.SolveSdoku(sdoku);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    printf("Time measured: %.3f seconds.\n", elapsed);
    printf("\n");
    solver.PrintSdoku(sdoku);
    
    delete []sdoku;
    delete []sdokuOriginal;
}
