/*
计数排序：假设n个输入元素中的每一个都是在(0,k)区间内的一个整数
用一个长度为k+1的计数数组，统计元素的每个值一共有多少个，然后再通过逐项递加的方式得到该值前面一共还有多少个数；
为了保证排序的稳定，需要对原输入数组从后往前遍历，这样才能保证排序的稳定
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
        //这里尤其注意，应该是先递减在取值（和算法导论上的伪代码不同）
        --C[A[i]]; 
        B[C[A[i]]] = A[i];
    }

    for(int i = 0;i < len;++i)
    {
        A[i] = B[i];
    }

    delete[] B;
    delete[] C;
}

int main()
{
    int A[] = {1,2,3,3,2,1,4,5,6,6,5,4,7,8,9,9,8,7};
    countSort(A,sizeof(A)/sizeof(A[0]),9);
    for(int i = 0;i < sizeof(A)/sizeof(A[0]);++i)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    return 0;
}