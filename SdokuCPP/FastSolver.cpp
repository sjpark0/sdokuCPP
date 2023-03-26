//
//  FastSolver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/26.
//

#include "FastSolver.hpp"


FastSolver::FastSolver()
{
    m_solved.clear();
}


FastSolver::~FastSolver()
{
}
int FastSolver::SolveSdoku(int* sdoku, vector<COORD> *emptyList)
{
    vector<COORD> emptyListTemp;
    vector<COORD>::iterator iter;
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    emptyListTemp.clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, availableList);
        if(numList == 0){
            delete []sdokuTemp;
            delete []availableList;
            return 0;
        }
        if(numList == 1){
            sdokuTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[0];
            emptyListTemp.erase(iter);
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        m_solved.push_back(sdokuTemp);
        delete []availableList;
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    iter = emptyListTemp.begin();
    numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, availableList);
    
    COORD tmp = (*iter);
    emptyListTemp.erase(iter);
    result = 0;
    for(int i=0;i<numList;i++){
        sdokuTemp[tmp.x + tmp.y * NUM_X * NUM_Y] = availableList[i];
        tempResult = SolveSdoku(sdokuTemp, &emptyListTemp);
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
    }
    
    delete []sdokuTemp;
    delete []availableList;
    return result;
    

}
