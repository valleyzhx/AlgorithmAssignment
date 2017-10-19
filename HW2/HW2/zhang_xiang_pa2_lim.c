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
    bool shouldStart = false;
    for (int i=0; ; i++) {
        if (array[i]>=0) {
            if (array[i]>0) {
                shouldStart = true;
            }
            if (shouldStart) {
                printf("%d ",array[i]);
            }
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

int convert_to_int(large_int large){
   int digits = digts_large_int(large);
    int result = 0;
    int loop = 0;
    while (digits--) {
        result += large[digits]*pow(10, loop++);
    }
    return result;
}



//
//
large_int add_function(large_int A,large_int B){
    int a_len = digts_large_int(A);
    int b_len = digts_large_int(B);
//    printArray(A);
//    printArray(B);
    
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

large_int insert_zero_infront(large_int large,int count){
    if (count == 0) {
        return large;
    }
    int len = digts_large_int(large);
    large_int new_large = (int*)malloc(sizeof(int)*(len+count+1));
    for (int i=0; i<=len+count; i++) {
        if (i<count) {
            new_large[i] = 0;
        }else{
            new_large[i] = large[i-count];
        }
    }
    return new_large;
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
        
        int u_Num = convert_to_int(u);
        int v_num = convert_to_int(v);
        
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

    add_digits(&ax, 4*k);
//    printf("ax: ");
//    printArray(ax);
    
    large_int ay_bx = add_function(ay, bx);
    add_digits(&ay_bx, 3*k);
//    printf("ay_bx: ");
//    printArray(ay_bx);
    free(ay);
    free(bx);
    
    large_int az_by = add_function(az, by);
//    printf("az_by: ");
//    printArray(az_by);
    free(az);
    free(by);
    
    
    large_int az_by_cz = add_function(az_by, cx);
    add_digits(&az_by_cz, 2*k);
//    printf("az_by_cz: ");
//    printArray(az_by_cz);
    free(az_by);
    free(cx);
    
    large_int bz_cy = add_function(bz, cy);
    add_digits(&bz_cy, k);
//    printf("bz_cy: ");
//    printArray(bz_cy);
    free(bz);
    free(cy);

    //printf("\n");
    large_int first = add_function(ax, ay_bx);
//    printf("ax+ay_bx: ");
//    printArray(first);
    free(ax);
    free(ay_bx);
    
    large_int second = add_function(az_by_cz, bz_cy);
//    printf("az_by_cz+bz_cy: ");
//    printArray(second);
    free(az_by_cz);
    free(bz_cy);
    
    large_int fir_sec = add_function(first, second);
    free(first);
    free(second);
    
    large_int result = add_function(fir_sec, cz);
    free(fir_sec);
    free(cz);
    
    return result;
}

large_int standard_large_int_multiplication(large_int u, large_int v, int digit){
    if (is_zero(u, digit)||is_zero(v, digit)) {
        large_int large = malloc(sizeof(int)*(digit+1));
        for (int i=0; i<digit; i++) {
            *(large+i) = 0;
        }
        *(large+digit) = -1;
        return large;
    }
    if (digit<=kThreshold) {
        int u_Num = convert_to_int(u);
        int v_num = convert_to_int(v);
        return convert_to_large_int(u_Num*v_num);
    }
    //u	× v =	xw	× 102m +	(xz	+	wy)	× 10m +	yz
    
    int k = digit/2;
    
    large_int x = copy_from(u, 0, k);
    large_int y = copy_from(u, k, k);
    
    large_int w = copy_from(v, 0, k);
    large_int z = copy_from(v, k, k);
    
    large_int xw = standard_large_int_multiplication(x, w, k);
    large_int xz = standard_large_int_multiplication(x, z, k);
    large_int wy = standard_large_int_multiplication(w, y, k);
    large_int yz = standard_large_int_multiplication(y, z, k);

    free(x);free(y);free(w);free(z);
    
    
    
    large_int xz_wy = add_function(xz, wy);
    
    
    add_digits(&xw, 2*k);
    add_digits(&xz_wy, k);
    
    large_int first = add_function(xw, xz_wy);
    large_int result = add_function(first, yz);
    
    free(xw);free(xz);free(wy);free(yz);
    free(xz_wy);free(first);
    
    
    return result;

}





int main(int argc, const char * argv[]) {
    // insert code here...
   
    srand((int)time(NULL));

    int n = 1;
    while (1) {
        printf("input an n digits integer,n = 6k:");
        scanf("%d",&n);

        while (n%6 != 0) {
            printf("n is not 6*k, please input again");
            scanf("%d",&n);
        }
        
        large_int A = generateInteger(n);
        large_int B = generateInteger(n);
        
        int a = n/6;
        int change_n = n;
        if (n!=6 && a%3 != 0) {
            change_n = 6*(a+3-a%3);
        }
        
        large_int cus_A = insert_zero_infront(A, change_n-n);
        large_int cus_B = insert_zero_infront(B, change_n-n);

        large_int C = large_int_multiplication(cus_A,cus_B,change_n);
        printf("=\n\n");
        printArray(C);
        
        if (change_n != n) {
            free(cus_A);
            free(cus_B);
        }
        
     
        a = ceil(log2(n));
        change_n = pow(2, a);
        large_int std_A = insert_zero_infront(A, change_n-n);
        large_int std_B = insert_zero_infront(B, change_n-n);
        
        large_int std_C = standard_large_int_multiplication(std_A,std_B,change_n);
        printf("\n");
        printf("standard large multiplication result:\n");
        printArray(std_C);
        printf("\n");
        
        if (change_n != n) {
            free(std_A);
            free(std_B);
        }
        
        
        free(A);
        free(B);
        free(C);
        free(std_C);
        
        
        n=1;
    }
    
    
    return 0;
}






