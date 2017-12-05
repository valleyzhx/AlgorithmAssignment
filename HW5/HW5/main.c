//
//  main.c
//  HW5
//
//  Created by Xiang on 2017/11/29.
//  Copyright © 2017年 Xiang. All rights reserved.
//

#include "HW5.h"
#define TEST 0

typedef struct{
    int profit;
    int weight;
}Item;

int _W;

void creatTestItems(Item array[],int *num){
    Item item0 = {16,5};
    Item item1 = {25,20};
    Item item2 = {15,18};
    Item item3 = {15,9};
    Item item4 = {19,16};
    Item item5 = {28,19};
    Item item6 = {21,17};
    Item item7 = {22,11};
    
    *num = 8;
    array[0]=item0;array[1]=item1;array[2]=item2;array[3]=item3;
    array[4]=item4;array[5]=item5;array[6]=item6;array[7]=item7;
    int sum = item0.weight+item1.weight+item2.weight+item3.weight+
              item4.weight+item5.weight+item6.weight+item7.weight;
    _W = (int)(0.6*sum);

}


void createItems(Item array[],int num){
    int i = 0;
    int sum = 0;
    while (i<num) {
        int profit = rand()%21+10;
        int weight = rand()%16+5;
        sum += weight;
        Item item = {profit,weight};
        array[i] = item;
        i++;
    }
    _W = (int)(0.6*sum);
}
void printArray(Item array[],int num){
    int i = 0;
    while (i<num) {
        Item item = array[i];
        printf("{%d,%d} ",item.profit,item.weight);
        if (i==3) {
            printf("\n");
        }
        i++;
    }
    printf("\n");
}

#pragma mark- brute_force_method
void brute_force_method(Item array[],int num){
    int max = 0;
    int index = 0;
    int saveWeight = 0;
    for (int i=0; i<pow(2, num); i++) {
        int temp = i;
        int value = 0;
        int weight = 0;
        
        for (int k=num-1; k>=0; k--) {
            int bit = temp&1;
            if (bit) {
                Item item = array[k];
                weight+=item.weight;
                if (weight>_W) {
                    break;
                }
                value += item.profit;
            }
            temp = temp>>1;
        }
        if (value>max) {
            max = value;
            saveWeight = weight;
            index = i;
        }else if(value == max){
            if (weight < saveWeight) {
                saveWeight = weight;
                index = i;
            }
        }
    }
    
    printf("brute_force_method => contains:\n");
    int get_first = pow(2, num-1);
    for (int i=0; i<num; i++) {
        int bit = get_first&index;
        if (bit) {
            Item item = array[i];
            printf("{%d,%d} ",item.profit,item.weight);
        }
        index = index<<1;
    }
    printf("\ntotal profile: "L_RED"%d"WHITE", weight: "L_RED"%d\n"WHITE,max,saveWeight);
    
    
}
#pragma mark- refinement_method

int findProfit(int row, int weight,Item array[],int rowArr[],int num){
    Item item = array[row-1];
    
    if (row == 1) {
        if (weight>=item.weight) {
            rowArr[row] = 1;
            return item.profit;
        }
    }else{
        int tempA[num+1]; // seperate to 2 version
        int tempB[num+1];
        for (int i=0; i<num+1; i++) {
            tempA[i]=0;
            tempB[i]=0;
        }
        
       int valueA = findProfit(row-1, weight, array,tempA,num);
        if (item.weight<=weight) {
            int valueB = findProfit(row-1, weight-item.weight, array,tempB,num) + item.profit;
            if (valueB>valueA) {// record B rowArr version
                for (int i=1; i<num+1; i++) {
                    if (tempB[i]) {
                        rowArr[i] = 1;
                    }
                }
                rowArr[row] = 1;
                return valueB;
            }
        }
        for (int i=1; i<num+1; i++) { //or record A rowArr version
            if (tempA[i]) {
                rowArr[i] = 1;
            }
        }
        return valueA;
    }
    return 0;
}


void refinement_method(Item array[],int num){
    int rowArr[num+1];
    
    printf("\n");
    int weight = 0;
    int profit = 0;
    for (int row=1; row<num+1; row++) {
        for (int i=0; i<num+1; i++) {
            rowArr[i] = 0;
        }
        weight = 0;
        profit = findProfit(row, _W, array,rowArr,num);
        printf("NO.%d row profit:%d and entrys:",row,profit);
        for (int i=0; i<num+1; i++) {
            if (rowArr[i] == 1) {
                Item item = array[i-1];
                weight += item.weight;
                printf("{%d,%d} ",item.profit,item.weight);
            }
        }
        printf("\n");
    }
    
   // int profit = findProfit(num, _W, array,rowArr,num);
    weight = 0;
    printf("refinement_method => contains:\n");
    for (int row = 1; row<num+1; row++) {
        if (rowArr[row] == 1) {
            Item item = array[row-1];
            weight += item.weight;
            printf("{%d,%d} ",item.profit,item.weight);
        }
    }
    printf("\ntotal profile: "L_RED"%d"WHITE", weight: "L_RED"%d\n"WHITE,profit,weight);


}


#pragma mark- backtracking_method

void sort_itemArr(Item array[],int num){
    for (int i=0; i<num; i++) {
        for (int j=i+1; j<num; j++) {
            Item itemA = array[i];
            Item itemB = array[j];
            float pA = itemA.profit*1.0/itemA.weight;
            float pB = itemB.profit*1.0/itemB.weight;
            if (pB>pA) {
                array[i] = itemB;
                array[j] = itemA;
            }
        }
    }
}

float kwf2(Item array[], int num, int nodeindex, int weight,int profit){
    float bound = profit;

    while (weight<_W&&nodeindex<=num) {
        Item item = array[nodeindex-1];

        if (weight+item.weight<=_W) {
            weight += item.weight;
            bound += item.profit;
        }else{
            float k = (_W-weight)*1.0/item.weight;
            weight = _W;
            bound += (k*item.profit);
        }
        nodeindex++;
    }
    return bound;
}

bool isPromosing(Item array[],int num,int nodeindex,int weight, int profit,int maxProfit){
    if (weight>=_W) {
        return false;
    }
    float bound = kwf2(array, num, nodeindex+1, weight, profit);
    
    return bound>maxProfit;
}

void knapSack(Item array[],int num,int index,int profit,int weight,int *maxProfit,int bestset[],int include[]){
    if (weight<=_W && profit>*maxProfit) {
        *maxProfit = profit;
        for (int i=0; i<num; i++) {
            bestset[i] = include[i];
        }
    }
    if (isPromosing(array, num, index, weight, profit, *maxProfit)) {
        Item item = array[index];
        include[index]=1;
        knapSack(array, num, index+1, profit+item.profit, weight+item.weight, maxProfit, bestset, include);
        // add item
        include[index]=0;
        knapSack(array, num, index+1, profit, weight, maxProfit, bestset, include);// not add item
    }
}


void backtracking_method(Item array[],int num){
    sort_itemArr(array, num);
    for (int i=0; i<num; i++) {
        Item item = array[i];
        float bound = kwf2(array, num, i+1, 0, 0);
        printf("node {%d,%d}'s boud is %.2f\n",item.profit,item.weight,bound);
    }
    printf("\n");
    
    int bestset[num];
    int include[num];
    for (int i=0; i<num; i++) {
        bestset[i]=0;
        include[i]=0;
    }
    int maxprofit=0;
    knapSack(array, num, 0, 0, 0, &maxprofit, bestset, include);
    
    printf("backtracking_method => contains:\n");
    int weight = 0;
    for (int i = 0; i<num; i++) {
        if (bestset[i] == 1) {
            Item item = array[i];
            weight += item.weight;
            printf("{%d,%d} ",item.profit,item.weight);
        }
    }
    printf("\ntotal profile: "L_RED"%d"WHITE", weight: "L_RED"%d\n"WHITE,maxprofit,weight);

}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf(CYAN "\n===== Program Begin! =====\n\n" WHITE);
    srand((unsigned int)time(0));
    int num = 4+rand()%5;
    Item array[8];
    if (TEST) {
        creatTestItems(array, &num);
    }else{
        createItems(array, num);
    }
    
    printf("create %d items:\n",num);
    printArray(array, num);
    printf(PURPLE"W is %d\n"WHITE,_W);
    printf(BROWN"\n===== brute_force_method =====\n\n" WHITE);
    brute_force_method(array, num);
    printf(BROWN"\n===== refinement_method =====\n\n"WHITE);
    refinement_method(array,num);
    printf(BROWN"\n===== backtracking =====\n\n"WHITE);
    backtracking_method(array,num);
    
    printf("\n");
    
    return 0;
}

