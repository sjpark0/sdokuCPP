//
//  IFastSolver.cpp
//  SdokuCPP
//
//  Created by sjpark on 2023/04/06.
//
#include <algorithm>
#include "IFastSolver.hpp"


IFastSolver::IFastSolver()
{
    m_solved.clear();
}


IFastSolver::~IFastSolver()
{
}

int IFastSolver::GetAvailableNumber(int* sdoku, int i, int j, vector<int>* numList)
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

int IFastSolver::AssignValue(vector<COORD1> *assignList, int x, int y, int val, vector<int> *availableList, vector<COORD1> *emptyList)
{
    int index = x + y * NUM_X * NUM_Y;
	COORD1 tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.group = (x / NUM_X + y / NUM_Y * NUM_Y);
	tmp.val = val;

    //assignList->push_back(tmp);
    (*assignList)[assignList->size() - 1].val = val;
    vector<COORD1>::iterator iter;
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
        else if(iter->group == tmp.group){
            tmpList->erase(remove(tmpList->begin(), tmpList->end(), val), tmpList->end());
        }
    }
    return 0;
}

int IFastSolver::SolveSdokuR(vector<COORD1> *assignList, vector<int> *availableList, vector<COORD1> *emptyList)
{
    vector<int> *availableListTemp = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    vector<int> *availableListTemp2 = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
    
    vector<COORD1> emptyListTemp;
	vector<COORD1> *assignListTemp = new vector<COORD1>();
    vector<COORD1>::iterator iter;
    
    int numList;
    emptyListTemp.clear();
	for (iter = assignList->begin(); iter != assignList->end(); iter++) {
		assignListTemp->push_back(*iter);
	}
    for(iter = emptyList->begin();iter != emptyList->end();iter++){
        emptyListTemp.push_back(*iter);
        availableListTemp[iter->x + iter->y * NUM_X * NUM_Y] = availableList[iter->x + iter->y * NUM_X * NUM_Y];
    }
    
    iter = emptyListTemp.begin();
    while(iter != emptyListTemp.end()){
        numList = (int)availableListTemp[iter->x + iter->y * NUM_X * NUM_Y].size();
        if(numList == 0){
			assignListTemp->clear();
            delete []availableListTemp;
            delete []availableListTemp2;
            return 0;
        }
        if(numList == 1){
            COORD1 tmp = (*iter);
            assignListTemp->push_back(tmp);
            emptyListTemp.erase(iter);
            
            AssignValue(assignListTemp, tmp.x, tmp.y, availableListTemp[tmp.x + tmp.y * NUM_X * NUM_Y][0], availableListTemp, &emptyListTemp);
            
            iter = emptyListTemp.begin();
        }
        else{
            iter++;
        }
    }
    
    if(emptyListTemp.size() == 0){
		m_vecSolved.push_back(assignListTemp);
        delete []availableListTemp;
        delete []availableListTemp2;
        return 1;
    }
    
    int result = 0;
    int tempResult;
    
    
    iter = emptyListTemp.begin();
    vector<int> tmpList = availableListTemp[iter->x + iter->y * NUM_X * NUM_Y];
    numList = (int)tmpList.size();
    COORD1 tmp = (*iter);
    assignListTemp->push_back(tmp);
    emptyListTemp.erase(iter);
    result = 0;
    
    for(iter = emptyListTemp.begin();iter != emptyListTemp.end();iter++){
        availableListTemp2[iter->x + iter->y * NUM_X * NUM_Y] = availableListTemp[iter->x + iter->y * NUM_X * NUM_Y];
    }
    for(int i=0;i<numList;i++){
        AssignValue(assignListTemp, tmp.x, tmp.y, tmpList[i], availableListTemp, &emptyListTemp);
        tempResult = SolveSdokuR(assignListTemp, availableListTemp, &emptyListTemp);
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
    delete assignListTemp;
    return result;
}

int IFastSolver::SolveSdoku(int* sdoku, vector<COORD1> *emptyList)
{
	vector<COORD1>::iterator iter;
	vector<int> *availableList = new vector<int>[NUM_X * NUM_Y * NUM_X * NUM_Y];
	vector<COORD1> assignList;
	int result;

	for (iter = emptyList->begin(); iter != emptyList->end(); iter++) {
		GetAvailableNumber(sdoku, iter->y, iter->x, &availableList[iter->x + iter->y * NUM_X * NUM_Y]);
	}

	result = SolveSdokuR(&assignList, availableList, emptyList);
	
	for (iter = m_vecSolved[0]->begin(); iter != m_vecSolved[0]->end(); iter++) {
		sdoku[iter->x + iter->y * NUM_X * NUM_Y] = iter->val;
	}

	delete[]availableList;
	return result;
}
