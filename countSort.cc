/*
计数排序：假设n个输入元素中的每一个都是在(0,k)区间内的一个整数
*/
#include<iostream>

void countSort(int* A,int len,int k)
{
    int* B = new int[len];
    int* C = new int[k+1];

    for(int i = 0;i <= k;++i)
        C[i] = 0;

    for(int i = 0;i < len;++i)
        ++C[A[i]];

    for(int i = 1;i <= k;++i)
        C[i] += C[i-1];

    for(int i = len-1;i >= 0;--i)
    {
        B[C[A[i]]] = A[i];
        --C[A[i]];
    }

    for(int i = 0;i < len;++i)
    {
        A[i] = B[i];
    }

    delete B;
    delete C;
}

int main()
{
    int A[] = {6,8,0,4,1,6,8,0,4,2,6,8,9,0,5,3,2,1,3,5,7,8,0,8,6,4,4,4,6,7,3};
    countSort(A,sizeof(A)/sizeof(A[0]),9);
    for(int i = 0;i < sizeof(A)/sizeof(A[0]);++i)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    return 0;
}