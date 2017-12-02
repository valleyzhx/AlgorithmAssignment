//
//  main.c
//  HW4
//
//  Created by Xiang on 2017/11/21.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int x;
    int y;
    int edge;
}Edge;

int _nodeArr[100];
int _node_count = 0;

int _non_nodeArr[100];

Edge _edgeArr[100];
int _edgeCount = 0;
int _setArr[10] = {0,1,2,3,4,5,6,7,8,9};
int _height[100] = {0};

void printA(int *A,int n){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf(" %d",A[i*n+j]);
        }
        printf("\n");
    }
}

#pragma mark- Prim's

void makequeue(int *G,int n){
    int node = _nodeArr[0];
    int min = 100;
    int index = 0;
    
    for (int j=0; j<_node_count; j++) {
        for (int i=1; i<n; i++) {
            int a = _non_nodeArr[i];// out
            int b = _nodeArr[j];// inside

            if (a!=0) {
                if (min>G[a*n+b]) {
                    min = G[a*n+b];
                    index = i;
                    node = b;
                }
            }
        }
    }
    printf("%d - %d: %d\n",node,index,min);
    _nodeArr[_node_count++] = index;
    _non_nodeArr[index] = 0;
}

void prim(int *G,int n){
    _nodeArr[_node_count++] = 0;
    for (int i=0; i<n; i++) {
        _non_nodeArr[i] = i;
    }
    
    while(_node_count<n) {
        makequeue(G, n);
    }
    
}

#pragma mark- Kruskal's
int partition(Edge arr[], int low, int high){
    Edge key = arr[low];
    while(low<high){
        while(low <high && arr[high].edge >= key.edge )
            high--;
        if(low<high)
            arr[low++] = arr[high];
        while( low<high && arr[low].edge <=key.edge )
            low++;
        if(low<high)
            arr[high--] = arr[low];
    }
    arr[low] = key;
    return low;
}
void quick_sort(Edge arr[], int start, int end){
    int pos;
    if (start<end){
        pos = partition(arr, start, end);
        quick_sort(arr,start,pos-1);
        quick_sort(arr,pos+1,end);
    }
    return;
}


void setEdgeSet(int *A, int n){
    
    for (int i=0; i<n; i++) {
        for (int j= i+1; j<n; j++) {
            Edge edge = {i,j,A[i*n+j]};
            _edgeArr[_edgeCount++] = edge;
        }
    }
    
    quick_sort(_edgeArr, 0, _edgeCount-1);
}

void union3(int repx, int repy,int edge){ // repy -> repx
    if	(_height[repx]	==	_height	[repy]){
        _height[repx]++;
        _setArr[repy] = repx;//y’s	tree	points	to	x’s	tree
        printf("%d - %d: %d\n",repx,repy,edge);

    }
    else if	(_height[repx] > _height[repy]){
        _setArr[repy] = repx; //y’s	tree	points	to	x’s	tree
        printf("%d - %d: %d\n",repx,repy,edge);

    }
    else{
        _setArr[repx] = repy; //x’s	tree	points	y’s	tree
        printf("%d - %d: %d\n",repy,repx,edge);

    }
}

int find3(int x){
    int root = x;
    while(root != _setArr[root]) root = _setArr[root];//find root
    
    int node = x;
    while(node != root){
        int parent = _setArr[node];
        _setArr[node]	= root;	//	node points	to	root
        node = parent;
    }
    return	root;
}

void Kruskal(int *A,int n){
    setEdgeSet(A, n);
    
    for (int i=0; i<_edgeCount; i++) {
        Edge edge = _edgeArr[i];
       int ucomp = find3(edge.x);
       int vcomp = find3(edge.y);
        if (ucomp != vcomp) {
            union3 (ucomp,vcomp,edge.edge);
        }
    }
}


#pragma mark- main

int main(int argc, const char * argv[]) {
    // insert code here...
    srand((int)time(NULL));
    printf("input the number of vertices between 5 and 10:");
    int n = 0;
    scanf("%d",&n);
    
    int A[n][n];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j) {
                A[i][j] = 0;
            }else if(j>i){
                A[i][j] = rand()%10 + 1;
                A[j][i] = A[i][j];
            }
        }
    }
    printA((int*)A,n);
    printf("prim: \n");
    prim((int*)A, n);
    printf("Kruskal: \n");
    Kruskal((int*)A,n);
    
    
    
    return 0;
}




