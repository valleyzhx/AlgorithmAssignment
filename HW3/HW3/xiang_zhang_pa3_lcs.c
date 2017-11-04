//
//  main.c
//  HW3
//
//  Created by Xiang on 2017/11/4.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define my_max(a,b) (a>b?a:b)

int LCS_Length(char *str_x, char *str_y){
    unsigned long x_len = strlen(str_x);
    unsigned long y_len = strlen(str_y);
    int length[y_len+1][x_len+1];
    
    for (int y=0; y<=y_len; y++) {
        for (int x=0; x<=x_len; x++) {
            if (x == 0 || y==0) {
                length[y][x] = 0;
            }else if (str_x[x-1] == str_y[y-1]){
                length[y][x] = length[y-1][x-1] + 1;//diagonal
            }else{// not match , set the max of its up or left
                length[y][x] = my_max(length[y-1][x], length[y][x-1]);
            }
        }
    }
    
    return length[y_len][x_len];
}





int main(int argc, const char * argv[]) {
    // insert code here...
    char *X = (char*)argv[1];
    char *Y = (char*)argv[2];
    
    if (X && Y) {
        int length = LCS_Length(X, Y);
        printf("%s and %s LCS is: %d\n",X,Y,length);
    }else{
        while (1) {
            printf("input two strings:");
            char str_1[100];
            char str_2[100];
            scanf("%s %s",str_1,str_2);
            if (str_1[0]&&str_2[0]) {
                int length = LCS_Length(str_1, str_2);
                printf("%s and %s LCS 's is: %d\n",str_1,str_2,length);
            }else{
                printf("input error");
            }
        }
    }
    
    
    return 0;
}
