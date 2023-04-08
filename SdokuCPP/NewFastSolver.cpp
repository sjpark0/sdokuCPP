//
//  NewFastSolver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/08.
//
#include <algorithm>
#include "NewFastSolver.hpp"


NewFastSolver::NewFastSolver()
{
    m_solved.clear();
}


NewFastSolver::~NewFastSolver()
{
}

/*
int NewFastSolver::GetAvailableNumber(int* sdoku, int i, int j, int* numList)
{
    int index1, index2;
    bool isAvail;
    int count = 0;
    for(int i=0;i<NUM_X * NUM_Y;i++){
        numList[i] = 0;
    }
    for (int aa = 1; aa < 1 + NUM_X * NUM_Y; aa++) {
        isAvail = true;
        for (int m = 0; m < NUM_X * NUM_Y; m++) {
            if (sdoku[m + i * NUM_X * NUM_Y] == aa) {
                isAvail = false;
                break;
            }
            if (sdoku[j + m * NUM_X * NUM_Y] == aa) {
                isAvail = false;
                break;
            }
        }
        
    
        if (isAvail == true) {
            index1 = (i / NUM_Y) * NUM_Y;
            index2 = (j / NUM_X) * NUM_X;
            for (int m = index1; m < index1 + NUM_Y; m++) {
                if (isAvail == true) {
                    for (int n = index2; n < index2 + NUM_X; n++) {
                        if (sdoku[n + m * NUM_X * NUM_Y] == aa) {
                            isAvail = false;
                            break;
                        }
                    }
                }
            }
        }
        if (isAvail == true) {
            numList[aa - 1] = 1;
            //numList->push_back(aa);
            //(*numList)[count] = aa;
            count++;
        }
    }
    //return (int)numList->size();
    return count;
}*/
int NewFastSolver::GetAvailableNumber(int y, int x, vector<COORD2> *originalEmptyList, vector<COORD1> *assignList, int *numList)
{
    int numListTemp[NUM_X * NUM_Y];
    int count = 0;
    vector<COORD1>::iterator iter1;
    vector<COORD2>::iterator iter2;
    /*for (int i = 0; i < NUM_X * NUM_Y; i++) {
        numListTemp[i] = 0;
    }*/
    memset(numListTemp, 0, NUM_X * NUM_Y * sizeof(int));
    for(iter2 = originalEmptyList->begin();iter2 != originalEmptyList->end();iter2++){
        if(iter2->x == x && iter2->y == y){
            for(int i=0;i<NUM_X * NUM_Y;i++){
                if(iter2->availableList[i] > 0){
                    numListTemp[iter2->availableList[i] - 1] = 1;
                }
                /*else {
                    numListTemp[iter2->availableList[i] - 1] = 0;
                }*/
            }
            //memcpy(numList, iter2->availableList, NUM_X * NUM_Y * sizeof(int));
            break;
        }
    }
    
    for(iter1 = assignList->begin();iter1 != assignList->end();iter1++){
        
        if(iter1->x == x){
            numListTemp[iter1->val - 1] = 0;
        }
        else if(iter1->y == y){
            numListTemp[iter1->val - 1] = 0;
        }
        else if(iter1->group == iter2->group){
            numListTemp[iter1->val - 1] = 0;
        }
    }
    count = 0;
    for(int i=0;i<NUM_X * NUM_Y;i++){
        numList[i] = 0;
    }
    for(int i=0;i<NUM_X * NUM_Y;i++){
        //if(numList[i] > 0) count++;
        if(numListTemp[i] > 0){
            numList[count] = i + 1;
            count++;
        }
    }
    //return (int)numList->size();
    return count;
}

int NewFastSolver::SolveSdokuR(vector<COORD2> *originalEmptyList, vector<COORD1> *emptyList, vector<COORD1> *assignList)
{
    vector<COORD1> emptyListTemp;
    vector<COORD1> assignListTemp;
    
    vector<COORD1>::iterator iter;
    
    int availableList[NUM_X * NUM_Y];// = new int[NUM_X * NUM_Y];
    int numList;
    emptyListTemp.clear();
    assignListTemp.clear();
    for(iter=emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
    }
    for(iter=assignList->begin();iter != assignList->end();iter++){
        assignListTemp.push_back(*iter);
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = GetAvailableNumber(iter->y, iter->x, originalEmptyList, &assignListTemp, availableList);
        if(numList == 0){
            //delete []availableList;
            return 0;
        }
        if(numList == 1){
            COORD1 tmp = (*iter);
            emptyListTemp.erase(iter);
            
            tmp.val = availableList[0];
            assignListTemp.push_back(tmp);
            
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        vector<COORD1> *solvedList = new vector<COORD1>();
        solvedList->clear();
        for(iter = assignListTemp.begin();iter != assignListTemp.end();iter++){
            solvedList->push_back(*iter);
        }
        m_assignList.push_back(solvedList);
        //delete []availableList;
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    
    iter = emptyListTemp.begin();
    
    numList = GetAvailableNumber(iter->y, iter->x, originalEmptyList, &assignListTemp, availableList);
    
    COORD1 tmp = (*iter);
    emptyListTemp.erase(iter);
    assignListTemp.push_back(tmp);
    result = 0;
    
    for(int i=0;i<numList;i++){
        assignListTemp[assignListTemp.size() - 1].val = availableList[i];
        
        tempResult = SolveSdokuR(originalEmptyList, &emptyListTemp, &assignListTemp);
        
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
        
    }
    return result;
}
int NewFastSolver::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    vector<COORD1> assignList;
    vector<COORD2> originalEmptyList;
    
    vector<COORD1>::iterator iter;
    vector<int> *availableList = new vector<int>[emptyList->size()];
    int result;
    COORD2 tmp;
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        tmp.x = (*iter).x;
        tmp.y = (*iter).y;
        tmp.group = (*iter).group;
        tmp.val = (*iter).val;
        Solver::GetAvailableNumber(sdoku, iter->y, iter->x, tmp.availableList);
        originalEmptyList.push_back(tmp);
    }
    
    result = SolveSdokuR(&originalEmptyList, emptyList, &assignList);
    
    for(iter = m_assignList[0]->begin();iter != m_assignList[0]->end();iter++){
        sdoku[iter->x + iter->y * NUM_X * NUM_Y] = iter->val;
    }
    delete []availableList;
    return result;
}
