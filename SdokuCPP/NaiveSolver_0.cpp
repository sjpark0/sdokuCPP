//
//  NaiveSolver1.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#include "NaiveSolver_0.hpp"
#include <time.h>
#include <stdlib.h>


NaiveSolver_0::NaiveSolver_0()
{
    m_solved.clear();
}


NaiveSolver_0::~NaiveSolver_0()
{
}
int NaiveSolver_0::SolveSdoku(int* sdoku, COORD1 *emptyList, int numEmptyList)
{
    if(numEmptyList == 0){
        int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
        memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

        m_solved.push_back(sdokuTemp);
        return 1;
    }
    int result = 0;
    int tempResult;
    
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    
    
    numList = GetAvailableNumber(sdoku, emptyList[0].y, emptyList[0].x, availableList);
    if(numList == 0){
        delete []availableList;
        return 0;
    }
    else{
        result = 0;
        for(int i=0;i<numList;i++){
            sdoku[emptyList[0].x + emptyList[0].y * NUM_X * NUM_Y] = availableList[i];
            //tempResult = SolveSdoku(sdoku, &emptyListTemp);
            tempResult = SolveSdoku(sdoku, &emptyList[1], numEmptyList - 1);
            sdoku[emptyList[0].x + emptyList[0].y * NUM_X * NUM_Y] = 0;
            if(tempResult > 1){
                result = 2;
                break;
            }
            result += tempResult;
        }
    }
    
    delete []availableList;
    return result;
}
int NaiveSolver_0::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    return SolveSdoku(sdoku, emptyList->data(), emptyList->size());
    
    /*if(emptyList->size() == 0){
        int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
        memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

        m_solved.push_back(sdokuTemp);
        return 1;
    }
    int result = 0;
    int tempResult;
    
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    vector<COORD1>::iterator iter = emptyList->begin();
    vector<COORD1>::iterator iter1;
    
    vector<COORD1> emptyListTemp;
    
    
    numList = GetAvailableNumber(sdoku, iter->y, iter->x, availableList);
    if(numList == 0){
        delete []availableList;
        return 0;
    }
    else{
        result = 0;
        for(iter1 = emptyList->begin() + 1;iter1 != emptyList->end();iter1++){
            emptyListTemp.push_back(*iter1);
        }
        for(int i=0;i<numList;i++){
            sdoku[iter->x + iter->y * NUM_X * NUM_Y] = availableList[i];
            tempResult = SolveSdoku(sdoku, &emptyListTemp);
            sdoku[iter->x + iter->y * NUM_X * NUM_Y] = 0;
            if(tempResult > 1){
                result = 2;
                break;
            }
            result += tempResult;
        }
    }
    
    delete []availableList;
    return result;*/
}
