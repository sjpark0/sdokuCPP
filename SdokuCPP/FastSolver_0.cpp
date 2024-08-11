//
//  FastSolver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/26.
//

#include "FastSolver_0.hpp"


FastSolver_0::FastSolver_0()
{
    m_solved.clear();
}


FastSolver_0::~FastSolver_0()
{
}
int FastSolver_0::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    vector<COORD1>::iterator iter;
    vector<COORD1>::iterator iter1;
    vector<COORD1> assignList;
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    
    iter = emptyList->begin();
    while(iter != emptyList->end()){
        numList = GetAvailableNumber(sdoku, iter->y, iter->x, availableList);
        if(numList == 0){
            for(iter1 = assignList.begin();iter1 != assignList.end();iter1++){
                emptyList->push_back(*iter1);
                sdoku[iter1->x + iter1->y * NUM_X * NUM_Y] = 0;
            }
            delete []availableList;
            assignList.clear();
            return 0;
        }
        if(numList == 1){
            assignList.push_back(*iter);
            sdoku[iter->x + iter->y * NUM_X * NUM_Y] = availableList[0];
            emptyList->erase(iter);
            iter = emptyList->begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyList->size() == 0){
        int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
        memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

        m_solved.push_back(sdokuTemp);
        for(iter1 = assignList.begin();iter1 != assignList.end();iter1++){
            emptyList->push_back(*iter1);
            sdoku[iter1->x + iter1->y * NUM_X * NUM_Y] = 0;
        }
        delete []availableList;
        assignList.clear();
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    iter = emptyList->begin();
    numList = GetAvailableNumber(sdoku, iter->y, iter->x, availableList);
    
    COORD1 tmp = (*iter);
    assignList.push_back(*iter);
    emptyList->erase(iter);
    result = 0;
    for(int i=0;i<numList;i++){
        sdoku[tmp.x + tmp.y * NUM_X * NUM_Y] = availableList[i];
        tempResult = SolveSdoku(sdoku, emptyList);
        //sdoku[tmp.x + tmp.y * NUM_X * NUM_Y] = 0;
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
    }
    
    for(iter1 = assignList.begin();iter1 != assignList.end();iter1++){
        emptyList->push_back(*iter1);
        sdoku[iter1->x + iter1->y * NUM_X * NUM_Y] = 0;
    }
    delete []availableList;
    assignList.clear();
    return result;
    

}
