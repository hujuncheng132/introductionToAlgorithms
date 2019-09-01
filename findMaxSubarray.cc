/*
寻找最大子数组，即求一个数组中和最大的连续子数组
*/

/*
方法一：分治法
原问题可以递归分解成子问题，再由子问题合并得到解；
一个数组的最大连续子数组：max{左半边数组的最大连续子数组，右半边数组的最大连续子数组，跨越中点的最大连续子数组}
*/
#include<iostream>
#include<algorithm>
#include<limits.h>

int findMidMax(int A[],int p,int q,int r)
{
    int sumLeft = 0,maxLeft = INT_MIN;
    for(int i = q;i >= p;--i)
    {
        sumLeft += A[i];
        if(sumLeft > maxLeft)
            maxLeft = sumLeft;
    }

    int sumRight = 0,maxRight = INT_MIN;
    for(int j = q+1;j <= r;++j)
    {
        sumRight += A[j];
        if(sumRight > maxRight)
            maxRight = sumRight;
    }

    return maxLeft + maxRight;

}

int findMaxSubarray1(int A[],int p,int r)
{
    if(p < r)
    {
        int q = (p+r)/2;
        int maxLeft = findMaxSubarray1(A,p,q); // 递归求解左半数组的最大子数组和
        int maxRight = findMaxSubarray1(A,q+1,r); // 递归求解右半数组的最大子数组和
        int maxMid = findMidMax(A,p,q,r); //合并步骤，求跨越中间的最大子数组和
        return std::max<int>(std::max<int>(maxLeft,maxLeft),maxMid);
    }
    else if(p == r)
        return A[p];
}



/*
方法二：动态规划（在线算法）
从左到右，每读入一个数，就计算从新起点开始到这个数的和currentSum，
如果currentSum比当前的最大子数组和大maxSum，则更新最大值并继续读入下一个数，
如果currentSum小于0，则抛弃这段子数组(因为不管后面的数是什么，这一段子数组都会使总和变小)，将下一个点设置为新的起点继续计算
*/
int findMaxSubarray2(int A[],int length)
{
    int maxSum = INT_MIN;
    int currentSum = 0;
    for(int i = 0;i < length;++i)
    {
        currentSum += A[i];
        if(currentSum > maxSum)
            maxSum = currentSum; // 如果当前的子数组之和大于当前的最大子数组和，则更新当前的最大子数组和
        if(currentSum < 0)
            currentSum = 0; //  如果当前的子数组之和小于0，则抛弃这段子数组
    }
    return maxSum;
}

int main()
{
    int A[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7}; //最大子数组为18,20，-7,12
    std::cout << findMaxSubarray1(A,0,sizeof(A) / sizeof(*A)-1) << std::endl;
    std::cout << findMaxSubarray2(A,sizeof(A) / sizeof(*A)) << std::endl;
    return 0;
}