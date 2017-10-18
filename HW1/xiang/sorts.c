//
//  main.c
//  HW1
//
//  Created by Xiang on 2017/9/26.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdbool.h>

int _array[1000] = {0};
int _count;
bool _largerThan20 = false;
int _step;

void print_starts(int num){
    for (int j=0; j<num; j++) {
        printf("*");
        if (j%5 == 4) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_Array_stars(bool showStep){
    if (_largerThan20 == false) {
        if (showStep) {
            printf("Step :%d\n",++_step);
        }
        for (int i=0; i< _count; i++) {
            int number = _array[i];
            print_starts(number);
        }
    }
}

void print_array(){
    printf("\nResult: \n\n");
    if (_largerThan20) {
        for (int i=0; i<_count; i++) {
            printf("%d ",_array[i]);
        }
    }else{
        print_Array_stars(false);
    }
    printf("\n\n");
}



void set_array(){
    _largerThan20 = _count>20;
    printf("\norigin array is:\n\n");
    srand((int)time(NULL));
    int base = _largerThan20?1000:15;
    for (int i=0; i<_count; i++) {
        
        int random = rand()%base+1;
        _array[i] = random;
        if (_largerThan20) {
            printf("%d ",random);
        }else{
            print_starts(random);
        }
    }
    printf("\n");
}

void swap(int indexA,int indexB){
    _array[indexA] += _array[indexB];
    _array[indexB] = _array[indexA] - _array[indexB];
    _array[indexA] -= _array[indexB];
    print_Array_stars(true);
}

void copy_arr(int start,int end , int *arr, int *init_arr){
    
    for (int i=0; i<=end-start; i++) {
        arr[i] = init_arr[start+i];
    }
}



void exchange_sort(){
    for (int i=0; i<_count; i++) {
        for (int j= i+1; j<_count; j++) {
            if (_array[j]<_array[i]) {
                swap(i, j);
            }
        }
    }
}

void insert_sort(){
    for (int i=1; i<_count; i++) {
        for (int j=i; j>=1; j--) {
            if (_array[j]<_array[j-1]) {
                swap(j, j-1);
            }else{
                break;
            }
        }
    }

}

void merge_array(int left_count, int right_count, int *left_arr, int *right_arr ,int *array){

    int l_index = 0 , r_index = 0 , index = 0;
    
    while (l_index<left_count || r_index<right_count) {
        
        int left = l_index<left_count?left_arr[l_index]:100000;
        int right = r_index<right_count?right_arr[r_index]:100000;
        if (left<right) {
            array[index] = left;
            l_index++;
        }else {
            array[index] = right;
            r_index++;
        }
        index++;
    }
    
}



void merge_sort(int count,int* array){
    int left_count = count/2;
    int right_count = count-left_count;
    int left_arr[left_count];
    int right_arr[right_count];
    copy_arr(0, left_count-1, left_arr,array);
    copy_arr(left_count, count-1, right_arr,array);
    
    if (left_count>1) {
        merge_sort(left_count, left_arr);
    }
    if (right_count>1) {
        merge_sort(right_count, right_arr);
    }
    
    merge_array(left_count,right_count,left_arr, right_arr, array);
}

void randomized_quick_sort(int count, int *array){
    int ran_index = rand()%count;
    int left_arr[count];
    int right_arr[count];
    int left_count = 0, right_count = 0;
    int mid = array[ran_index];
    for(int i=0;i<count;i++){
        if (i==ran_index) {
            continue;
        }
        if (array[i]<mid){
            left_arr[left_count]=array[i];
            left_count++;
        }else{
            right_arr[right_count]=array[i];
            right_count++;
        }
        
    }
    if (left_count>1) {
        randomized_quick_sort(left_count, left_arr);
    }
    if (right_count>1) {
        randomized_quick_sort(right_count, right_arr);
    }
    
    for (int i=0; i<left_count+1+right_count; i++) {
        if (i<left_count) {
            array[i] = left_arr[i];
        }else if (i>left_count){
            array[i] = right_arr[i-left_count-1];
        }else{
            array[i]= mid;
        }
    }
    //print_Array_stars(true);
}




int main(int argc, const char * argv []) {
    
    while (1) {
        printf("\nplease select an sort algorithm:\n\n");
        printf("1: exchange sort \n2: insertion sort \n3: merge sort \n4: randomized quick sort\n\nplease type the id of the algorithms: ");
        int select_id;
        scanf("%d",&select_id);
        
        while (select_id>4||select_id<1) {
            printf("id Error, please input again:");
            scanf("%d",&select_id);
        }
        
        printf("\nplease input n: ");
        scanf("%d",&_count);
        
        while (_count>1000||_count<1) {
            printf("n Error, please input again:");
            scanf("%d",&_count);
        }
        
        set_array();
        _step = 0;
        switch (select_id) {
            case 1:
                exchange_sort();
                break;
            case 2:
                insert_sort();
                break;
            case 3:
                merge_sort(_count, _array);
                break;
            case 4:
                randomized_quick_sort(_count,_array);
                break;
            default:
                
                break;
        }
            print_array();

    }
    return 0;
}








