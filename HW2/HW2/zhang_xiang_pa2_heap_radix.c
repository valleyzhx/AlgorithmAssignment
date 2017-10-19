//
//  zhang_xiang_pa2_heap_radix.c
//  HW2
//
//  Created by Xiang on 2017/10/18.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int _showStars;


void print_starts(int num){
    if (_showStars) {
        for (int j=0; j<num; j++) {
            printf("*");
            if (j%5 == 4) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void print_Array_stars(int array[],int count, int step){
    if (_showStars) {
        printf("step: %d\n",step);
        for (int i=0; i<count; i++) {
            print_starts(array[i]);
        }
    }
}




void printArray(int array[],int count){
    for (int i=0; i<count ; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

void generate_Array(int array[],int count){
    printf("generate array:\n");
    int base = _showStars?16:999;
    for (int i = 0; i < count; i++) {
        int random = rand()%base;
        array[i] = random;
        printf("%d ",random);
    }
    printf("\n");
}


void max_heapify(int array[], int heap_index,int count){
    
    int left_index = 2*heap_index;
    int right_index = 2*heap_index+1;;
    
    int largest = heap_index;
    
    if (left_index <= count && array[left_index-1] > array[largest-1]) {
        largest = left_index;
    }
    if (right_index <= count && array[right_index-1] > array[largest-1]) {
        largest = right_index;
    }
    
    if (largest != heap_index) {
        int temp = array[heap_index-1];
        array[heap_index-1] = array[largest-1];
        array[largest-1] = temp;
        max_heapify(array, largest, count);
    }
    
}


void heapSort(int array[], int count){
    
    int step = 0;
    //heap index from 1 to count
    for (int i = count/2; i >= 1; i--){
        max_heapify(array, i, count);
        print_Array_stars(array, count, ++step);
    }
    
    for (int i=count-1; i>=1; i--)
    {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        max_heapify(array, 1, i);// heep index : 1, from root -> down
        print_Array_stars(array, count, ++step);
    }
    
    
}


void radix_sort_at(int base, int array[], int count){
    int countArr[999] = {0};
    
    for (int i=0; i<count; i++) {//count array
        int num = array[i];
        int n_digit = num%(base*10)/(base);
        countArr[n_digit]++;
    }
    for (int i=1; i<999; i++) { // contain offset
        countArr[i] += countArr[i-1];
    }
    
    int resultArr[count];
    for (int i=count-1; i>=0; i--) {
        int num = array[i];
        int n_digit = num%(base*10)/(base);
        
        int index = countArr[n_digit]-1;
        resultArr[index] = num;
        countArr[n_digit]--;
    }
    for (int i=0; i<count; i++) {
        array[i] = resultArr[i];
    }
}


void radixSort(int array[],int count){
    int base = 1;
    while (base<=100) {
        radix_sort_at(base, array, count);
        base *= 10;
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    srand((int)time(NULL));

    int n;

    while (1) {
        printf("please select the algorithm:\n1.heap sort\n2.radix sort\n:");
        scanf("%d",&n);
        if (n>2||n<1) {
            printf("incorrect select!please select again:");
        }else{
            printf("please input an integer between 1 and 1000:");
            int input_num = 0;
            while (input_num<1 || input_num>1000) {
                scanf("%d",&input_num);
                if (input_num<1 || input_num>1000) {
                    printf("input error number, please input again\n");
                }
            }
            
            
            _showStars = input_num<=20;
            
            int array[input_num];
            generate_Array(array,input_num);
            
            
            if (n == 1) {
                
                heapSort(array, input_num);
                printf("heap sort:\n");
                printArray(array, input_num);
                
            }else if (n == 2){
                
                radixSort(array, input_num);
                printf("radix sort:\n");
                printArray(array, input_num);
            }
            
            
        }
        
    }
    
    return 0;
}

