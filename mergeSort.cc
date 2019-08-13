/*
归并排序
归并排序运用了分治法的思想：
将原问题分解为规模较小但是类似于原问题的子问题，递归的求解这些子问题，最后再合并这些子问题的解来建立原问题的解；
分治法的主要工作是在合并的过程，递归分解子问题的过程只是做了一个简单的划分；
归并排序首先将数组递归分解成最小子问题（即只有一个元素的情况，此时自然有序），然后再将两个有序的子数组合并成一个有序数组
*/
#include <iostream>

// 合并函数，合并A[p:q]和A[q+1:r]这两个子数组
void merge(int A[],int p,int q,int r)
{
    // 新建两个数组用于临时存放两个子数组
    int length1 = q-p+1;
    int length2 = r-q;
    int *lhs = new int[length1];
    int *rhs = new int[length2];
    for(int i = 0;i < length1;++i)
        lhs[i] = A[p+i];
    for(int i = 0;i < length2;++i)
        rhs[i] = A[q+1+i];

    // 分别比较两个子数组中的元素，进行合并
    int m = 0,n = 0,k = p;
    while(m < length1 && n < length2)
        if(lhs[m] <= rhs[n])
            A[k++] = lhs[m++];
        else
            A[k++] = rhs[n++];

    if(m < length1)
    {
        while(m < length1)
            A[k++] = lhs[m++];
    }
    else if(n < length2)
    {
        while(n < length2)
            A[k++] = rhs[n++];
    }

    return;
}


void mergeSort(int A[],int p,int r)
{
    if(p < r)
    {
        int q = (p+r)/2;
        // 递归解决子问题
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        // 合并子问题
        merge(A,p,q,r);
    }

    return;
}

int main()
{
    int A[] = {1,2,7,0,5,8,7,23,56,23,9,23,1,6,3};
    mergeSort(A,0,sizeof(A) / sizeof(A[0])-1);
    for(int i = 0;i < sizeof(A) / sizeof(*A);++i)
    {
        std::cout << A[i] << " ";
    }
    return 0;
}