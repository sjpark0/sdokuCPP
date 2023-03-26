//
//  NaiveSolver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#include "NaiveSolver.hpp"
#include <time.h>
#include <stdlib.h>


NaiveSolver::NaiveSolver()
{
    m_solved.clear();
}


NaiveSolver::~NaiveSolver()
{
}

int NaiveSolver::SolveSdoku(int* sdoku, vector<COORD> *emptyList)
{
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

    if(emptyList->size() == 0){
        m_solved.push_back(sdokuTemp);
        return 1;
    }
    int result = 0;
    int tempResult;
    
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    vector<COORD>::iterator iter = emptyList->begin();
    vector<COORD>::iterator iter1;
    
    vector<COORD> emptyListTemp;
    
    
    numList = GetAvailableNumber(sdoku, iter->y, iter->x, availableList);
    if(numList == 0){
        delete []availableList;
        delete []sdokuTemp;
        return 0;
    }
    else{
        result = 0;
        for(iter1 = emptyList->begin() + 1;iter1 != emptyList->end();iter1++){
            emptyListTemp.push_back(*iter1);
        }
        for(int i=0;i<numList;i++){
            sdokuTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[i];
            tempResult = SolveSdoku(sdokuTemp, &emptyListTemp);
            if(tempResult > 1){
                result = 2;
                break;
            }
            result += tempResult;
        }
    }
    
    delete []sdokuTemp;
    delete []availableList;
    return result;
    

}
