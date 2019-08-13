/*
插入排序
依次将右边未排序的元素，与左边排好序的从后往前逐个进行比较并后移比它大的元素，直到找到比它小的元素，并插入到这个元素后面
*/
#include<iostream>


void insertSort(int A[],int length)
{
    // 参数有效性检查
    if(A == nullptr || length <= 0)
        return;

    // 数组的第一个元素默认是有序的，故从第二个元素开始比较
    for(int i = 1;i < length;++i)
    {
        int j = i-1; // 从左边有序序列从后往前依次比较
        int current = A[i]; // 待比较插入的元素
        while(j >= 0 && A[j] > current) //一直循环比较，直到出现比current小的元素或者全部比较完（此时说明current是最小的）
        {
            A[j+1] = A[j];  // 如果比current大则后移一位
            --j;
        }
        A[j+1] = current;
    }

    return;
}


int main()
{
    int A[] = {1,2,7,0,5,8,7,23,56,23,9,23,1,6,3};
    insertSort(A,sizeof(A) / sizeof(A[0]));
    for(int i = 0;i < sizeof(A) / sizeof(*A);++i)
    {
        std::cout << A[i] << " ";
    }
    return 0;
}