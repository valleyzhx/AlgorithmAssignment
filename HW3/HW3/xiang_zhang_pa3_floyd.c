//
//  xiang_zhang_pa3_floyd.c
//  HW3
//
//  Created by Xiang on 2017/11/4.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n;

void floyd_path(int *A, int *P){
    
    for(int k=0;k<n;k++){
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (j!=k && i!=k && i!=j) {
                    if (A[i*n+k] + A[k*n+j] < A[i*n+j]) {
                        A[i*n+j] = A[i*n+k] + A[k*n+j];
                        P[i*n+j] = k;
                    }
                }
            }
        }
    }
}


void printPaths(int *A, int *P, int i, int j, int *length){
    int k = P[i*n+j];
    if (k) {
        printPaths(A,P,i,k,length);
        printPaths(A, P, k, j, length);
    }else{
        printf(" > (%d,%d)",i,j);
        *length += A[i*n+j];
    }
}



int main(int argc, const char * argv[]) {

    srand((int)time(NULL));
    
    n = 9;//rand()%6 + 5;
    printf("%d vertices are created!\n",n);
    
    int A[n][n];
    int P[n][n];
    int C[n][n];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            A[i][j] = 0;
            P[i][j] = 0;
            C[i][j] = 0;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j) {
                A[i][j] = 0;
            }else if(A[j][i]){
                A[i][j] = A[j][i];
            }else{
                A[i][j] = rand()%10 + 1;
            }
        }
    }
    printf("adjacency matrix:\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    floyd_path((int*)A, (int*)P);
    printf("P:\n");

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ",P[i][j]);
        }
        printf("\n");
    }
    
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j||C[j][i]) {
                continue;
            }
            C[i][j] = 1;
            printf("path (%d,%d):",i,j);
            int length = 0;
            printPaths((int*)A, (int*)P, i, j, &length);
            printf(" length %d\n",length);
        }
    }
    

    return 0;
}
