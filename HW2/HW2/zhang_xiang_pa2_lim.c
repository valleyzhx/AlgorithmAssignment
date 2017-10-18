//
//  zhang_xiang_pa2_lim.c
//  HW2
//
//  Created by Xiang on 2017/10/17.
//  Copyright © 2017年 xianng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <stdbool.h>

#define large_int int*
#define kThreshold 2


void printArray(large_int array){
    for (int i=0; ; i++) {
        if (array[i]>=0) {
            printf("%d ",array[i]);
        }else{
            break;
        }
    }
    printf("\n");
}

large_int generateInteger(int digit){
    large_int num = malloc(sizeof(int)*(digit+1));
    for (int i=0; i<digit; i++) {
        int random = rand()%10;
        if (i==0) {
            random = rand()%9 + 1;
        }
        *(num+i) = random;
        printf("%d",random);
    }
    printf("\n");
    *(num+digit) = -1;
    return num;
}

large_int convert_to_large_int(int num){
    int a = num;
    int digit = 0;
    while (a) {
        digit++;
        a=a/10;
    }
    large_int large = malloc(sizeof(int)*(digit+1));
    int temp = num;
    for (int i=0; i<digit; i++) {
        *(large+i) = temp/pow(10, digit-i-1);
        temp -= *(large+i)*pow(10, digit-i-1);
    }
    *(large+digit) = -1;
    return large;
}

large_int copy_from(large_int num,int index,int length){
    large_int large = malloc(sizeof(int)*(length+1));
    *(large+length) = -1;
    while (length--) {
        *(large+length) = *(num+index+length);
    }
    return large;
}

bool is_zero(large_int num, int digit){
    for (int i=0; i<digit; i++) {
        if (*(num+i)!=0) {
            return false;
        }
    }
    return true;
}

int digts_large_int(large_int num){
    int count = 0;
    for (int i=0; ; i++) {
        int a = num[i];
        if (a >=0) {
            count++;
        }else{
            break;
        }
    }
    return count;
}
//
//
large_int add_function(large_int A,large_int B){
    int a_len = digts_large_int(A);
    int b_len = digts_large_int(B);
    printArray(A);
    printArray(B);
    
    int max_len = fmax(a_len, b_len);
    int length = max_len;
    int carry = 0;
    int *array = (int*)malloc(sizeof(int)*(max_len+1));
    
    for (int i=1; i<=max_len; i++) {
        int a_val = i<=a_len?A[a_len-i]:0;
        int b_val = i<=b_len?B[b_len-i]:0;
        
        int value = a_val+b_val+carry;
            carry = value/10;
            value = value%10;
        array[max_len+1-i] = value;
    }
    if (carry) {
        array[0] = carry;
        length++;
    }
    large_int large = copy_from(array, max_len+1-length, length);
    free(array);
    return large;
}

void add_digits(large_int *large,int count){
   int len = digts_large_int(*large);
    //large_int new_large = (int*)malloc(sizeof(int)*(len+count+1));
    *large = (int *)realloc(*large, sizeof(int)*(len+count+1));
    for (int i=0; i<len+count; i++) {
        if (i>=len) {
            (*large)[i] = 0;
        }

    }
    (*large)[len+count] = -1;
}



large_int large_int_multiplication(large_int u, large_int v, int digit){

    if (is_zero(u, digit)||is_zero(v, digit)) {
        large_int large = malloc(sizeof(int)*(digit+1));
        for (int i=0; i<digit; i++) {
            *(large+i) = 0;
        }
        *(large+digit) = -1;
        return large;
    }
    
    if (digit<=kThreshold) {
        
        int u_Num = *(u)*10+*(u+1);
        int v_num = *(v)*10+*(v+1);
        
        return convert_to_large_int(u_Num*v_num);
    }
    int k = digit/3;

    large_int a = copy_from(u, 0, k);
    large_int b = copy_from(u, k, k);
    large_int c = copy_from(u, 2*k, k);
    
    large_int x = copy_from(v, 0, k);
    large_int y = copy_from(v, k, k);
    large_int z = copy_from(v, 2*k, k);
    
    //    Let A = a | b | c = a * 10 ^(2k) + b * 10 ^ (k) + c;
    //    Let B = x | y | z = x * 10 ^(2k) + y * 10 ^ (k) + z;
    //    A * B = ax * 10^4k + (ay + bx) * 10^3k + (az + by + cx ) * 10^2k + (bz + cy) * 10^k + cz
    
    large_int ax = large_int_multiplication(a, x, k);
    large_int ay = large_int_multiplication(a, y, k);
    large_int bx = large_int_multiplication(b, x, k);
    large_int az = large_int_multiplication(a, z, k);
    large_int by = large_int_multiplication(b, y, k);
    large_int cx = large_int_multiplication(c, x, k);
    large_int bz = large_int_multiplication(b, z, k);
    large_int cy = large_int_multiplication(c, y, k);
    
    large_int cz = large_int_multiplication(c, z, k);

    
    free(a);free(b);free(c);
    free(x);free(y);free(z);

//    printf("ax\n");
//    printArray(ax);
    add_digits(&ax, 4*k);
//    printf("ax add 0\n");
//    printArray(ax);
    
    large_int ay_bx = add_function(ay, bx);
    printf("ay_bx\n");
    printArray(ay_bx);
    add_digits(&ay_bx, 3*k);
    printf("ay_bx ad 000\n");
    printArray(ay_bx);
    
    large_int az_by = add_function(az, by);
    printf("az_by\n");
    printArray(az_by);
    
    
    large_int az_by_cz = add_function(az_by, cx);
    add_digits(&az_by_cz, 2*k);
    
    printf("az_by_cz\n");
    printArray(az_by_cz);
    
    large_int bz_cy = add_function(bz, cy);
    add_digits(&bz_cy, k);
    printf("bz_cy\n");
    printArray(bz_cy);
    
    printf("\n");
    large_int first = add_function(ax, ay_bx);
    printf("ax+ay_bx\n");
    printArray(first);
    large_int second = add_function(az_by_cz, bz_cy);
    printf("az_by_cz+bz_cy\n");
    printArray(second);
    return add_function(add_function(first, second), cz);
}


int main(int argc, const char * argv[]) {
    // insert code here...
   
    srand((int)time(NULL));

    int n = 1;
    while (1) {
        
        while (n%6 != 0) {
            printf("input an n digits integer,n=6k:");
            scanf("%d",&n);
        }
        int a = n/6;
        if (a%3 != 0) {
            int changeN = 6*(a+3-a%3);
            if (n!=changeN) {
                printf("to ensure always have 6k digits, input changed to %d\n",changeN);
                n = changeN;
            }
        }
        
        
        large_int A = generateInteger(n);
        large_int B = generateInteger(n);
        
        
        //digts_large_int(A);

        large_int C = large_int_multiplication(A,B,n);
        printf("=\n");
        printArray(C);
        
        
        n=1;
    }
    
    
    return 0;
}






