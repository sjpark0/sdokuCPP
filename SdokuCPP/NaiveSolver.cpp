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
    DeleteSolvedList();
}

void NaiveSolver::MakeSdoku(int *sdoku)
{
    srand(5);
    
    bool bSuccess = false;
    int totalNum = 0;
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    
    int temp = -1;
    
    while(!bSuccess) {
        totalNum++;
        bSuccess = true;
        for(int i=0;i<NUM_X * NUM_Y;i++){
            for(int j=0;j<NUM_X * NUM_Y;j++){
                sdoku[j + i * NUM_X * NUM_Y] = 0;
            }
        }
        for(int i=0;i<NUM_X * NUM_Y;i++){
            if(bSuccess){
                for(int j=0;j<NUM_X * NUM_Y;j++){
                    numList = GetAvailableNumber(sdoku, i, j, availableList);
                    if(numList == 0){
                        bSuccess = false;
                        break;
                    }
                    sdoku[j + i * NUM_X * NUM_Y] = availableList[rand() % numList];
                }
                
            }
        }
    }
    
    delete []availableList;
}

void NaiveSolver::GenerateSdoku(int* sdoku, int numRemove)
{
    MakeSdoku(sdoku);
    PrintSdoku(sdoku);
    int result = 0;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    vector<COORD> emptyList;
    while(result != 1){
        m_solved.clear();
        emptyList.clear();
        
        memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
        RemoveComponentSdoku(sdokuTemp, numRemove, &emptyList);
        result = SolveSdoku(sdokuTemp, &emptyList);
        printf("%d\n", result);
    }
    
    memcpy(sdoku, sdokuTemp, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    delete []sdokuTemp;
}


int NaiveSolver::GetAvailableNumber(int* sdoku, int i, int j, int* numList)
{
    int index1, index2;
    int count = 0;
    bool isAvail;
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
            numList[count] = aa;
            count++;
        }
    }
    return count;
}


void NaiveSolver::RemoveComponentSdoku(int* sdoku, int numRemove, vector<COORD> *emptyList)
{
    int index1, index2;
    COORD tmpCoord;
    
    for (int i = 0; i < numRemove; ) {
        index1 = rand() % (NUM_X * NUM_Y);
        index2 = rand() % (NUM_X * NUM_Y);
        if (sdoku[index2 + index1 * NUM_X * NUM_Y] != 0) {
            sdoku[index2 + index1 * NUM_X * NUM_Y] = 0;
            tmpCoord.x = index2;
            tmpCoord.y = index1;
            emptyList->push_back(tmpCoord);
            i++;
        }
    }
}

void NaiveSolver::PrintSdoku(int *sdoku)
{
    for (int i = 0; i < NUM_X * NUM_Y; i++) {
        for (int j = 0; j < NUM_X * NUM_Y; j++) {
            printf("%d\t", sdoku[j + i * NUM_X * NUM_Y]);
        }
        printf("\n");
    }
}

int NaiveSolver::SolveSdoku(int* sdoku, vector<COORD> *emptyList)
{
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

    if(emptyList->size() == 0){
        m_solved.push_back(sdokuTemp);
        return 1;
    }
    bool bMultiple;
    int num;
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

void NaiveSolver::SolveSdoku(int *sdoku)
{
    vector<COORD> emptyList;
    m_solved.clear();
    COORD tmpCoord;
    for (int i = 0; i < NUM_X * NUM_Y; i++) {
        for (int j = 0; j < NUM_X * NUM_Y; j++) {
            if (sdoku[j + i * NUM_X * NUM_Y] == 0) {
                tmpCoord.x = j;
                tmpCoord.y = i;
                emptyList.push_back(tmpCoord);
            }
        }
    }
    SolveSdoku(sdoku, &emptyList);
    memcpy(sdoku, m_solved[0], NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
}

void NaiveSolver::DeleteSolvedList()
{
    vector<int*>::iterator iter;
    int *temp;
    for (iter = m_solved.begin(); iter != m_solved.end(); iter++) {
        temp = (*iter);
        delete[]temp;
    }
    m_solved.clear();
}


int* NaiveSolver::GetSdoku(int index)
{
    return m_solved[index];
}
int NaiveSolver::GetNumOfSdoku()
{
    return m_solved.size();
}
