#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void print_array(int RandomArray[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ",RandomArray[i]);
        printf("\n");
    }
}

void print_star(int RandomArray[], int n)
{
    int i, j;
    if (n <= 20){
        for(i = 0; i < n; i++){
            for(j = 0; j < RandomArray[i]; j++){
                printf("*");
            }
            printf("\n");
        }
        
    }
    
}

void *random_array(int RandomArray[],int n)
{
    int i;
    srand((unsigned)time(NULL));
    if(n<=20)
    {
        for(i=0;i<n;i++)
        {RandomArray[i]=rand()%15;}
    }
    else
    {
        for(i=0;i<n;i++)
        {RandomArray[i]=rand()%1000;}
    }
    return RandomArray;
}

void swap(int *a , int *b)
{int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void each_heap_sort(int RandomArray[],int n ,int size)
{
    int left=2*n;
    int right=2*n+1;
    int max=n;
    if(left<size && RandomArray[left]>RandomArray[max])
    {max=left;}
    if(right<size && RandomArray[right]>RandomArray[max])
    {max=right;}
    if(max!=n)
    {swap(&RandomArray[n],&RandomArray[max]);}
    //each_heap_sort(RandomArray,max,size);
}

void heap_sort(int RandomArray[],int size)
{
    int deep;
    for(deep=size/2;deep>=1;deep--)
    {
        each_heap_sort(RandomArray,deep,size);
    }
    int i;
    for(i=size;i>=2;i--)
    {
        swap(&RandomArray[0],&RandomArray[i-1]);
        each_heap_sort(RandomArray,1,i-1);
        print_array(RandomArray,size);
        print_star(RandomArray,size);
    }
}

int largestNum(int RandomArray[], int n)
{
    int largeNum = RandomArray[0], i;
    for(i = 1; i < n; i++)
    {
        if(largeNum < RandomArray[i])
            largeNum = RandomArray[i];
    }
    return largeNum;
}

void radix_sort(int RandomArray[], int n)
{
    int bucket[10][10], bucket_count[10];
    int i, j, k, remainder, NOP=0, divisor=1, largeNum, pass;
    
    largeNum = largestNum(RandomArray, n);
    printf("The large element %d\n",largeNum);
    while(largeNum > 0)
    {
        NOP++;
        largeNum/=10;
    }
    for(pass = 0; pass < NOP; pass++)
    {
        for(i = 0; i < 10; i++)
        {
            bucket_count[i] = 0;
        }
        for(i = 0; i < n; i++)
        {
            remainder = (RandomArray[i] / divisor) % 10;
            bucket[remainder][bucket_count[remainder]] = RandomArray[i];
            bucket_count[remainder] += 1;
        }
        
        i = 0;
        for(k = 0; k < 10; k++)
        {
            for(j = 0; j < bucket_count[k]; j++)
            {
                RandomArray[i] = bucket[k][j];
                i++;
            }
            
        }
        
        divisor *= 10;
        printf("\n");
        print_star(RandomArray,n);
        print_array(RandomArray,n);
    }
}


//_______________________________________________________________________main function_________________________________________________________

int main()
{
    int m,n;
    int RandomArray[1001];
    int *array=RandomArray;
    printf("please choose a sorting algorithm:\n");
    printf("1.heap sort.\n");
    printf("2.radix sort.\n");
    scanf("%d",&m);
    printf("please input a number of array:\n");
    scanf("%d",&n);
    if(n < 1 || n > 1000)
    {printf("please input n which more or equal than 1 and less or equal than 1000\n");}
    if(m==1)
    {
        array=random_array(array,n);
        heap_sort(array,n);
        printf("finally , the array is:\n");
        print_array(array,n);
    }
    else if(m==2){
        array=random_array(array, n);
        print_array(array, n);
        radix_sort(RandomArray, n);
        print_array(array, n);
    }
    return 0;
}
