//
//  common.h
//  SdokuCPP
//
//  Created by sjpark on 2023/03/25.
//

#ifndef common_h
#define common_h

#define NUM_X 3
#define NUM_Y 3
typedef struct _COORD1{
    int x;
    int y;
    int group;
	int val;
}COORD1;

typedef struct _COORD2{
    int x;
    int y;
    int group;
    int val;
    int availableList[NUM_X * NUM_Y];
}COORD2;
#endif /* common_h */
