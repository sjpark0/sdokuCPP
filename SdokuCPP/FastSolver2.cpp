//
//  FastSolver2.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/27.
//

#include "FastSolver2.hpp"


FastSolver2::FastSolver2()
{
    m_solved.clear();
}


FastSolver2::~FastSolver2()
{
}

int FastSolver2::GetAvailableNumber(int* sdoku, int i, int j, vector<int>* numList)
{
    int index1, index2;
    bool isAvail;
    //numList->clear();
    int count = 0;
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
            //numList->push_back(aa);
            (*numList)[count] = aa;
            count++;
        }
    }
    //return (int)numList->size();
    return count;
}

int FastSolver2::SolveSdoku(int* sdoku, vector<COORD> *emptyList)
{
    vector<COORD> emptyListTemp;
    vector<COORD>::iterator iter;
    vector<int> availableList(NUM_X * NUM_Y);
    
    int numList;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    emptyListTemp.clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, &availableList);
        if(numList == 0){
            delete []sdokuTemp;
            return 0;
        }
        if(numList == 1){
            COORD tmp = (*iter);
            emptyListTemp.erase(iter);
            sdokuTemp[tmp.x + tmp.y * NUM_X * NUM_Y] = availableList[0];
            
            //sdokuTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[0];
            //emptyListTemp.erase(iter);
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        m_solved.push_back(sdokuTemp);
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    iter = emptyListTemp.begin();
    numList = GetAvailableNumber(sdokuTemp, iter->y, iter->x, &availableList);
    
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
    return result;
    

}
