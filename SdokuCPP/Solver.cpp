//
//  Solver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#include "Solver.hpp"

#include <time.h>
#include <stdlib.h>


Solver::Solver()
{
    m_solved.clear();
}


Solver::~Solver()
{
    DeleteSolvedList();
}

void Solver::MakeSdoku(int *sdoku)
{
    srand(5);
    
    bool bSuccess = false;
    int totalNum = 0;
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    
    
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

void Solver::GenerateSdoku(int* sdoku, int numRemove)
{
    MakeSdoku(sdoku);
    PrintSdoku(sdoku);
    int result = 0;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    vector<COORD1> emptyList;
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


int Solver::GetAvailableNumber(int* sdoku, int i, int j, int* numList)
{
    int index1, index2;
    int count = 0;
    bool isAvail;
    /*for(int i=0;i<NUM_X * NUM_Y;i++){
        numList[i] = -1;
    }*/
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


void Solver::RemoveComponentSdoku(int* sdoku, int numRemove, vector<COORD1> *emptyList)
{
    int index1, index2;
    COORD1 tmpCoord;
    
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

void Solver::PrintSdoku(int *sdoku)
{
    for (int i = 0; i < NUM_X * NUM_Y; i++) {
        for (int j = 0; j < NUM_X * NUM_Y; j++) {
            printf("%d\t", sdoku[j + i * NUM_X * NUM_Y]);
        }
        printf("\n");
    }
}


void Solver::SolveSdoku(int *sdoku)
{
    vector<COORD1> emptyList;
    m_solved.clear();
    COORD1 tmpCoord;
    for (int i = 0; i < NUM_X * NUM_Y; i++) {
        for (int j = 0; j < NUM_X * NUM_Y; j++) {
            if (sdoku[j + i * NUM_X * NUM_Y] == 0) {
                tmpCoord.x = j;
                tmpCoord.y = i;
                tmpCoord.group = (j / NUM_X) + (i / NUM_Y) * NUM_Y;
				tmpCoord.val = 0;
                emptyList.push_back(tmpCoord);
            }
        }
    }
    SolveSdoku(sdoku, &emptyList);
	if (m_solved.size() != 0) {
		memcpy(sdoku, m_solved[0], NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
	}
}

void Solver::DeleteSolvedList()
{
    vector<int*>::iterator iter;
    int *temp;
    for (iter = m_solved.begin(); iter != m_solved.end(); iter++) {
        temp = (*iter);
        delete[]temp;
    }
    m_solved.clear();
}


int* Solver::GetSdoku(int index)
{
    return m_solved[index];
}
int Solver::GetNumOfSdoku()
{
    return (int)m_solved.size();
}
