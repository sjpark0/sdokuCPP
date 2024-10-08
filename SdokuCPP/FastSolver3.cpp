//
//  FastSolver3.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/27.
//
#include <algorithm>
#include "FastSolver3.hpp"


FastSolver3::FastSolver3()
{
    m_solved.clear();
}


FastSolver3::~FastSolver3()
{
}

int FastSolver3::GetAvailableNumber(int* sdoku, int i, int j, vector<int>* numList)
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
            numList->push_back(aa);
            //(*numList)[count] = aa;
            count++;
        }
    }
    //return (int)numList->size();
    return count;
}

int FastSolver3::AssignValue(int *sdoku, int x, int y, int val, vector<int> *availableList, vector<COORD1> *emptyList, vector<int> *indexList)
{
    int index = x + y * NUM_X * NUM_Y;
    sdoku[index] = val;
    vector<COORD1>::iterator iter;
    vector<int> *tmpList;
    indexList->clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        tmpList = &availableList[iter->x + iter->y * NUM_X * NUM_Y];
        int pre_len = tmpList->size();
        if(iter->x == x){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        else if(iter->y == y){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        else if(iter->group == (x / NUM_X + y / NUM_Y * NUM_Y)){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        int post_len = tmpList->size();
        if(pre_len != post_len){
            indexList->push_back(iter->x + iter->y * NUM_X * NUM_Y);
        }
        
    }
    return 0;
}

int FastSolver3::SolveSdokuR(int* sdoku, vector<int> *availableList, vector<COORD1> *emptyList)
{
    vector<int> *availableListTemp = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    vector<int> indexList;
    vector<COORD1> emptyListTemp;
    vector<COORD1>::iterator iter;
    vector<int>::iterator iterInt;
    int numList;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));

	emptyListTemp = *emptyList;
    //emptyListTemp.clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        //emptyListTemp.push_back(*iter);
        availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[iter->x + iter->y * NUM_X * NUM_Y];
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = (int)availableListTemp[iter->x + iter->y * NUM_X * NUM_Y].size();
        if(numList == 0){
            delete []sdokuTemp;
            delete []availableListTemp;
            return 0;
        }
        if(numList == 1){
            COORD1 tmp = (*iter);
            emptyListTemp.erase(iter);
            AssignValue(sdokuTemp, tmp.x, tmp.y, availableListTemp[tmp.x + tmp.y * NUM_X * NUM_Y][0], availableListTemp, &emptyListTemp, &indexList);
            
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        m_solved.push_back(sdokuTemp);
        delete []availableListTemp;
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    
    iter = emptyListTemp.begin();
    vector<int> tmpList = availableListTemp[iter->x + iter->y * NUM_X * NUM_Y];
    numList = (int)tmpList.size();
    COORD1 tmp = (*iter);
    emptyListTemp.erase(iter);
    result = 0;
    
    for(int i=0;i<numList;i++){
        AssignValue(sdokuTemp, tmp.x, tmp.y, tmpList[i], availableListTemp, &emptyListTemp, &indexList);
        tempResult = SolveSdokuR(sdokuTemp, availableListTemp, &emptyListTemp);
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
        for(iterInt = indexList.begin();iterInt != indexList.end();iterInt++){
            availableListTemp[*iterInt].push_back(tmpList[i]);
        }
    }
    delete []availableListTemp;
    delete []sdokuTemp;
    return result;
}
int FastSolver3::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    vector<COORD1>::iterator iter;
    vector<int> *availableList = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    int result;
    
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        GetAvailableNumber(sdoku, iter->y, iter->x, &availableList[iter->x + iter->y * NUM_X * NUM_Y]);
    }
    
    result = SolveSdokuR(sdoku, availableList, emptyList);
    
    delete []availableList;
    return result;
}
