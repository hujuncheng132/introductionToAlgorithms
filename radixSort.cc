/*
基数排序
从最低有效位到最高有效位，分别用稳定排序算法（计数排序）进行排序
*/
#include<iostream>

struct Digit
{
    int digit;
    int index;
    Digit(int dit = 0,int inx = 0):digit(dit),index(inx){}
    ~Digit(){}
};


void countSort(Digit* A,int len,int k)
{
    Digit* B = new Digit[len];
    int* C = new int[k+1];

    for(int i = 0;i <= k;++i)
        C[i] = 0;

    for(int i = 0;i < len;++i)
        ++C[A[i].digit];

    for(int i = 1;i <= k;++i)
        C[i] += C[i-1];

    for(int i = len-1;i >= 0;--i)
    {
        --C[A[i].digit];
        B[C[A[i].digit]] = A[i];
    }

    // 打印每次计数排序后的结果
    for(int i = 0;i < len;++i)
    {
        A[i] = B[i];
        std::cout << A[i].digit << " " << A[i].index << ";";
    }
    std::cout << std::endl;

    delete[] B;
    delete[] C;
}

void radixSort(int* A,int len,int d)
{
    Digit* D = new Digit[len];
    int* B = new int[len];
    for(int i = 0;i < d;++i)
    {
        for(int j = 0;j < len;++j)
        {
            int temp = A[j];
            for(int k = 0;k < i;++k)
                temp = temp/10;
            D[j].digit = temp % 10;
            D[j].index = j;
        }
        countSort(D,len,9);
        for(int j = 0;j < len;++j)
            B[j] = A[D[j].index];

        for(int j = 0;j < len;++j)
        {
            A[j] = B[j];
            std::cout << A[j] << " ";
        }
        std::cout << std::endl;

    }
    delete[] D;
    delete[] B;
}

int main()
{
    int A[] = {765,345,234,987,2,981,232,5,345,13};
    radixSort(A,sizeof(A)/sizeof(A[0]),3);
    for(int i = 0;i < sizeof(A)/sizeof(A[0]);++i)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    return 0;
}