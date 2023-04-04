//
//  FastSolver3.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/03/27.
//

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

int FastSolver3::AssignValue(int *sdoku, int x, int y, int val, vector<int> *availableList, vector<COORD> *emptyList)
{
    int index = x + y * NUM_X * NUM_Y;
    sdoku[index] = val;
    vector<COORD>::iterator iter;
    vector<int> *tmpList;
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        tmpList = &availableList[iter->x + iter->y * NUM_X * NUM_Y];
        
        if(iter->x == x){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        else if(iter->y == y){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        /*else if((iter->x / NUM_X == x / NUM_X) && (iter->y / NUM_Y == y / NUM_Y)){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }*/
        else if(iter->group == (x / NUM_X + y / NUM_Y * NUM_Y)){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
    }
    return 0;
}

int FastSolver3::SolveSdokuR(int* sdoku, vector<int> *availableList, vector<COORD> *emptyList)
{
    vector<int> *availableListTemp = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    vector<int> *availableListTemp2 = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    
    vector<COORD> emptyListTemp;
    vector<COORD>::iterator iter;
    
    int numList;
    int *sdokuTemp = new int[NUM_X * NUM_Y * NUM_X * NUM_Y];
    memcpy(sdokuTemp, sdoku, NUM_X * NUM_Y * NUM_X * NUM_Y * sizeof(int));
    emptyListTemp.clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
        availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[iter->x + iter->y * NUM_X * NUM_Y];
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = (int)availableListTemp[iter->x + iter->y * NUM_X * NUM_Y].size();
        if(numList == 0){
            delete []sdokuTemp;
            delete []availableListTemp;
            delete []availableListTemp2;
            return 0;
        }
        if(numList == 1){
            COORD tmp = (*iter);
            emptyListTemp.erase(iter);
            AssignValue(sdokuTemp, tmp.x, tmp.y, availableListTemp[tmp.x + tmp.y * NUM_X * NUM_Y][0], availableListTemp, &emptyListTemp);
            
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        m_solved.push_back(sdokuTemp);
        delete []availableListTemp;
        delete []availableListTemp2;
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    
    iter = emptyListTemp.begin();
    vector<int> tmpList = availableListTemp[iter->x + iter->y * NUM_X * NUM_Y];
    numList = (int)tmpList.size();
    COORD tmp = (*iter);
    emptyListTemp.erase(iter);
    result = 0;
    
    for(iter = emptyListTemp.begin();iter != emptyListTemp.end();iter++){
        availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp[iter->x + iter->y * NUM_X * NUM_Y];
    }
    for(int i=0;i<numList;i++){
        AssignValue(sdokuTemp, tmp.x, tmp.y, tmpList[i], availableListTemp, &emptyListTemp);
        tempResult = SolveSdokuR(sdokuTemp, availableListTemp, &emptyListTemp);
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
        for(iter = emptyListTemp.begin();iter != emptyListTemp.end();iter++){
            if(iter->x == tmp.x){
                availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y];
            }
            else if(iter->y == tmp.y){
                availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y];
            }
            /*else if((iter->x / NUM_X == tmp.x / NUM_X) && (iter->y / NUM_Y == tmp.y / NUM_Y)){
                availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y];
            }*/
            else if(iter->group == (tmp.x / NUM_X + tmp.y / NUM_Y * NUM_Y)){
                availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y];
            }
        }
    }
    delete []availableListTemp;
    delete []availableListTemp2;
    delete []sdokuTemp;
    return result;
}
int FastSolver3::SolveSdoku(int* sdoku, vector<COORD> *emptyList)
{
    vector<COORD>::iterator iter;
    vector<int> *availableList = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    int result;
    
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        GetAvailableNumber(sdoku, iter->y, iter->x, &availableList[iter->x + iter->y * NUM_X * NUM_Y]);
    }
    
    result = SolveSdokuR(sdoku, availableList, emptyList);
    
    delete []availableList;
    return result;
}
