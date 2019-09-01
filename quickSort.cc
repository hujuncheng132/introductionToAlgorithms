/*
快速排序也使用了分治思想，不过和归并排序不同的是，在划分子数组的过程中就进行了排序
*/
#include<iostream>

int partition(int *A,int p,int r)
{
    int key = A[r];
    int i = p-1; 
    for(int j = p;j < r;++j)
    {
        if(A[j] <= key)
        {
            int temp = A[j];
            A[j] = A[++i];
            A[i] = temp;
        }
    }

    A[r] = A[i+1];
    A[i+1] = key;
    return i+1;
}

void quickSort1(int *A,int p,int r)
{
    if(p<r)
    {
        int q = partition(A,p,r);
        quickSort1(A,p,q-1);
        quickSort1(A,q+1,r);
    }
}

// 尾递归优化
void quickSort2(int *A,int p,int r)
{
    while(p<r)
    {
        int q = partition(A,p,r);
        quickSort2(A,p,q-1);
        p = q+1;
    }
}

int main()
{
    int A[] = {0,1,3,2,0,5,7,9,4,8,4,4,8,6,7,9,9};
    quickSort2(A,0,sizeof(A)/sizeof(A[0]-1));
    for(int i = 0;i < sizeof(A)/sizeof(A[0]);++i)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}