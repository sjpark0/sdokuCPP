//
//  NewFastSolver2.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/29.
//
#include <algorithm>

#include "NewFastSolver2.hpp"


NewFastSolver2::NewFastSolver2()
{
    m_solved.clear();
}


NewFastSolver2::~NewFastSolver2()
{
}

int NewFastSolver2::GetAvailableNumber(int* sdoku, int i, int j, vector<int>* numList)
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

int NewFastSolver2::AssignValue(vector<COORD3> *assignList, int x, int y, int val, vector<COORD3> *emptyList, vector<int> *indexList)
{
    (*assignList)[assignList->size() - 1].val = val;
    vector<COORD3>::iterator iter;
    vector<int> *tmpList;
    int cnt = 0;
    indexList->clear();
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        tmpList = &iter->availableList;
        int pre_len = tmpList->size();
        if(iter->x == x){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        else if(iter->y == y){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        /*else if((iter->x / NUM_X == x / NUM_X) && (iter->y / NUM_Y == y / NUM_Y)){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }*/
        else if(iter->group == (x/NUM_X + y/NUM_Y*NUM_Y)){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
        int post_len = tmpList->size();
        if(pre_len != post_len){
            indexList->push_back(cnt);
        }
        cnt++;
    }
    return 0;
}

int NewFastSolver2::SolveSdokuR(vector<COORD3> *assignList, vector<COORD3> *emptyList)
{
    vector<COORD3> emptyListTemp;
    
    vector<COORD3> *assignListTemp = new vector<COORD3>();
    vector<COORD3>::iterator iter, iter1, iter2;
    vector<int> indexList;
    vector<int>::iterator iterInt;
    int numList;
    
	*assignListTemp = *assignList;
	emptyListTemp = *emptyList;
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = iter->availableList.size();
        if(numList == 0){
            assignListTemp->clear();
            return 0;
        }
        if(numList == 1){
            COORD3 tmp = (*iter);
            assignListTemp->push_back(tmp);
            emptyListTemp.erase(iter);
            
            AssignValue(assignListTemp, tmp.x, tmp.y, tmp.availableList[0], &emptyListTemp, &indexList);
            
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
        m_vecSolved.push_back(assignListTemp);
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    
    iter = emptyListTemp.begin();
    vector<int> tmpList = iter->availableList;
    numList = (int)tmpList.size();
    COORD3 tmp = (*iter);
    assignListTemp->push_back(tmp);
    emptyListTemp.erase(iter);
    result = 0;
    
	
    for(int i=0;i<numList;i++){
        AssignValue(assignListTemp, tmp.x, tmp.y, tmp.availableList[i], &emptyListTemp, &indexList);
        tempResult = SolveSdokuR(assignListTemp, &emptyListTemp);
        if(tempResult > 1){
            result = 2;
            break;
        }
        result += tempResult;
        
        for(iterInt = indexList.begin();iterInt != indexList.end();iterInt++){
            emptyListTemp[*iterInt].availableList.push_back(tmp.availableList[i]);
        }
        
        
    }
    delete assignListTemp;
    return result;
}


int NewFastSolver2::SolveSdoku(int* sdoku, vector<COORD3> *emptyList)
{
    vector<COORD3>::iterator iter;
    vector<COORD3> assignList;
    int result;

    for (iter = emptyList->begin(); iter != emptyList->end(); iter++) {
        GetAvailableNumber(sdoku, iter->y, iter->x, &iter->availableList);
    }

    result = SolveSdokuR(&assignList, emptyList);
    
    for (iter = m_vecSolved[0]->begin(); iter != m_vecSolved[0]->end(); iter++) {
        sdoku[iter->x + iter->y * NUM_X * NUM_Y] = iter->val;
    }

    return result;
}

int NewFastSolver2::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
    vector<COORD3> emptyListCOORD3;
    emptyListCOORD3.clear();
    vector<COORD1>::iterator iter;
    
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        COORD3 tmp;
        tmp.x = iter->x;
        tmp.y = iter->y;
        tmp.val = iter->val;
        tmp.group = iter->group;
        tmp.availableList.clear();
        emptyListCOORD3.push_back(tmp);
    }
    
    return SolveSdoku(sdoku, &emptyListCOORD3);
}
