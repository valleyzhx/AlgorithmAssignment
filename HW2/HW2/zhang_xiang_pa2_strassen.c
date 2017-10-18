//
//  zhang_xiang_pa2_strassen.c
//  HW2
//
//  Created by Xiang on 2017/10/16.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

typedef enum {
    MethodAdd = 0,
    MethodReduce,
    
} Method;

void generateMatrix(int *array, int n){
    int maxRandom = sqrt(INT32_MAX/n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int num = rand()%maxRandom;
            *(array + i*n +j) = num;
            printf("%d ",num);
        }
        printf("\n");
    }
}
void divideMatrix(int *array, int size, int startX, int startY, int *orignArr){
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            *(array + i*size +j) = *(orignArr +(startY + i)*(2*size) + startX + j);
        }
    }
}


int *matrixMethod(int size, int *A,int *B, Method method){
   int *result = (int*)malloc(sizeof(int*)*size*size);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (method == MethodAdd) {
                *(result + i*size +j) = *(A + i*size +j) + *(B + i*size + j);
            }else{
                *(result + i*size +j) = *(A + i*size +j) - *(B + i*size + j);
            }
        }
    }
    return result;
}



void strassen_matrix_multiply(int n, int *A, int *B, int *C){
    
    if (n == 1) {
        *C = A[0]*B[0];
        return;
    }
    
    
    int size = n/2;
    int *A11 = (int*)malloc(sizeof(int*)*size*size);
    int *A12 = (int*)malloc(sizeof(int*)*size*size);
    int *A21 = (int*)malloc(sizeof(int*)*size*size);
    int *A22 = (int*)malloc(sizeof(int*)*size*size);
    divideMatrix(A11, size, 0, 0, A);
    divideMatrix(A12, size, size, 0, A);
    divideMatrix(A21, size, 0, size, A);
    divideMatrix(A22, size, size, size, A);

    int *B11 = (int*)malloc(sizeof(int*)*size*size);
    int *B12 = (int*)malloc(sizeof(int*)*size*size);
    int *B21 = (int*)malloc(sizeof(int*)*size*size);
    int *B22 = (int*)malloc(sizeof(int*)*size*size);
    divideMatrix(B11, size, 0, 0, B);
    divideMatrix(B12, size, size, 0, B);
    divideMatrix(B21, size, 0, size, B);
    divideMatrix(B22, size, size, size, B);
    
    int *A11_p_A22 = matrixMethod(size, A11, A22, MethodAdd);
    int *B11_p_B22 = matrixMethod(size, B11, B22, MethodAdd);
    int *A21_p_A22 = matrixMethod(size, A21, A22, MethodAdd);
    int *A11_p_A12 = matrixMethod(size, A11, A12, MethodAdd);
    int *B11_p_B12 = matrixMethod(size, B11, B12, MethodAdd);
    int *B21_p_B22 = matrixMethod(size, B21, B22, MethodAdd);

    int *B12_r_B22 = matrixMethod(size, B12, B22, MethodReduce);
    int *B21_r_B11 = matrixMethod(size, B21, B11, MethodReduce);
    int *A21_r_A11 = matrixMethod(size, A21, A11, MethodReduce);
    int *A12_r_A22 = matrixMethod(size, A12, A22, MethodReduce);
    
    int *m1 = (int*)malloc(sizeof(int*)*size*size);
    int *m2 = (int*)malloc(sizeof(int*)*size*size);
    int *m3 = (int*)malloc(sizeof(int*)*size*size);
    int *m4 = (int*)malloc(sizeof(int*)*size*size);
    int *m5 = (int*)malloc(sizeof(int*)*size*size);
    int *m6 = (int*)malloc(sizeof(int*)*size*size);
    int *m7 = (int*)malloc(sizeof(int*)*size*size);
    strassen_matrix_multiply(size, A11_p_A22, B11_p_B22, m1);
    strassen_matrix_multiply(size, A21_p_A22, B11, m2);
    strassen_matrix_multiply(size, A11, B12_r_B22, m3);
    strassen_matrix_multiply(size, A22, B21_r_B11, m4);
    strassen_matrix_multiply(size, A11_p_A12, B22, m5);
    strassen_matrix_multiply(size, A21_r_A11, B11_p_B12, m6);
    strassen_matrix_multiply(size, A12_r_A22, B21_p_B22, m7);
//    M1 = (A11 + A22)(B11+B22)
//    M2 = (A21 + A22) B11
//    M3 = A11 (B12 – B22)
//    M4 = A22 (B21 – B11)
//    M5 = (A11 + A12) B22
//    M6 = (A21 – A11) (B11+B12)
//    M7 = (A12 – A22)(B21 + B22)
    
    
    
//    *(C) = m1+m4-m5+m7;
//    *(C+1) = m3+m5;
//    *(C+2) = m2+m4;
//    *(C+3) = m1+m3-m2+m6;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i<size&&j<size) {//left up
                *(C+i*n+j) = *(m1+i*size+j) + *(m4+i*size+j)-*(m5+i*size+j)+*(m7+i*size+j);
            }else if (i<size){//right up
                *(C+i*n+j) = *(m3+i*size+j-size) + *(m5+i*size+j-size);
            }else if (j<size){//left down
                *(C+i*n+j) = *(m2+(i-size)*size+j) + *(m4+(i-size)*size+j);
            }else{//right down
                *(C+i*n+j) = *(m1+(i-size)*size+j-size) + *(m3+(i-size)*size+j-size)-*(m2+(i-size)*size+j-size)+*(m6+(i-size)*size+j-size);
            }
        }
    }
}



void standard_matrix_multiply(int n, int* A, int* B, int* C){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            *(C+n*i+j) = 0;
            for (int k=0; k<n; k++) {
                int num = *(A+n*i+k)*(*(B+n*k+j));
                *(C+n*i+j) += num;
            }
            printf("%d ",*(C+i*n+j));
        }
        printf("\n");
    }
    
    
}




int main(int argc, const char * argv[]) {
    // insert code here...
    srand((int)time(NULL));

    int n = 0;
    while (1) {
        while (n<1||n>1024) {
            printf("input an integer between 1 and 1024:");
            scanf("%d",&n);
        }
        
        int log = log2(n);
        int changeN = pow(2, log);
        if (n!=changeN) {
            printf("to ensure n=2^k, input changed to %d\n",changeN);
            n = changeN;
        }
        
        int *A = (int*)malloc(sizeof(int*)*n*n);
        int *B = (int*)malloc(sizeof(int*)*n*n);
        int *C = (int*)malloc(sizeof(int*)*n*n);
        
        printf("A matrix:\n");
        generateMatrix(A, n);
        printf("B matrix:\n");
        generateMatrix(B, n);
        
        strassen_matrix_multiply(n,A,B,C);
        printf("A*B matrix:\n");
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                printf("%d ",*(C+i*n+j));
            }
            printf("\n");
        }
        printf("Compare stadard matrix:\n");
        standard_matrix_multiply(n,A,B,C);
        n = 0;
    }
    return 0;
}





