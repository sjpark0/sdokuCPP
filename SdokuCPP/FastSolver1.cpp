//
//  FastSolver1.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/08.
//


#include "FastSolver1.hpp"


FastSolver1::FastSolver1()
{
    m_solved.clear();
}


FastSolver1::~FastSolver1()
{
}

int FastSolver1::GetAvailableNumber(int* sdoku, int i, int j, int* numList, int m)
{
    int index1, index2;
    int count = 0;
    bool isAvail;
    for(int mm=0;mm<NUM_X * NUM_Y;mm++){
        numList[mm] = 0;
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
            count++;
        }
    }
    return count;
}
int FastSolver1::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    vector<COORD1> emptyListTemp;
    vector<COORD1>::iterator iter;
    int *availableList = new int[NUM_X * NUM_Y];
    int numList;
    int idx;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    /*emptyListTemp.clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
    }*/
	emptyListTemp = *emptyList;
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, availableList, 0);
        if(numList == 0){
            delete []sdokuTemp;
            delete []availableList;
            return 0;
        }
        if(numList == 1){
            for(int i=0;i<NUM_X * NUM_Y;i++){
                if(availableList[i]){
                    idx = i;
                    break;
                }
            }
            sdokuTemp[iter->x + iter->y * NUM_X * NUM_Y] = idx + 1;
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
    numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, availableList, 0);
    
    COORD1 tmp = (*iter);
    emptyListTemp.erase(iter);
    result = 0;
    for(int i=0;i<NUM_X * NUM_Y;i++){
        if(availableList[i] == 0) continue;
        sdokuTemp[tmp.x + tmp.y * NUM_X * NUM_Y] = i + 1;
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
