/*
查找第K小的元素
*/
#include<iostream>

void exchange(int& a,int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 随机划分
int randomPartition(int* A,int p,int r)
{
    // 随机选择一个主元
    srand((unsigned)time(NULL));
    int random = (rand() %(r-p+1)+p);
    exchange(A[random],A[r]);

    int key = A[r];
    int i = p-1;
    for(int j = p;j < r;++j)
    {
        if(A[j] < key)
            exchange(A[++i],A[j]);
    }
    exchange(A[++i],A[r]); //这里交换的时候一定是传入A[r]而不是key
    return i;
}

// 返回A[p...r]中第K小的元素
int randomSelect(int* A,int p,int r,int k) 
{
    if(k > (r-p+1))
        exit(1);

    if(p == r) //当p==r时，k一定等于1
        return A[p];
    
    int q = randomPartition(A,p,r);
    int order = q-p+1; 
    if(k == order)
        return A[q];
    else if(k < order)
        return randomSelect(A,p,q-1,k);
    else
        return randomSelect(A,q+1,r,k-order);
}

int main()
{
    srand((unsigned)time(NULL));
    int len = 10;  
    int* A = new int[len];
    for(int i = 0;i < len;++i)
    {
        A[i] =  (rand()%100);
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    std::cout << randomSelect(A,0,len-1,4) << std::endl;
}