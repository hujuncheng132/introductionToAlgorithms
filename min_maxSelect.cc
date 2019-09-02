/*
同时查找最大值和最小值
单独寻找最大值、最小值都需要进行n-1次比较（共需要2n-2次），但是同时寻找最大值和最小值只需要进行3/2*n次比较
我们并不是将每一个输入元素都和当前的最小值和最大值分别进行比较，这样每个元素都需要进行2次比较，
而是对输入元素进行成对处理，一对输入元素先相互进行比较，较小的与当前的最小值比较，较大的与当前的最大值比较，这样每两个元素只需要3次比较
*/
#include<iostream>
#include<tuple>

std::tuple<int,int> selectMinAndMax(int* A,int len)
{
    int min,max;
    //首先判断len是奇数还是偶数
    if(len&0x1) //奇数
    {
        min = max = A[0];
        int i = 1;
        while(i < len)
        {
            int a = A[i++];
            int b = A[i++];
            if(a < b)
            {
                if(a < min)
                    min = a;
                if(b > max)
                    max = b;
            }
            else
            {
                if(b < min)
                    min = b;
                if(a > max)
                    max = a;
            }
        }
    }
    else //偶数
    {
        min = __INT_MAX__,max = INT32_MIN;
        int i = 0;
        while(i < len)
        {
            int a = A[i++];
            int b = A[i++];
            if(a < b)
            {
                if(a < min)
                    min = a;
                if(b > max)
                    max = b;
            }
            else
            {
                if(b < min)
                    min = b;
                if(a > max)
                    max = a;
            }
        }

    }
   return std::make_tuple(min,max);
}

int main()
{
    int len = 10;
    srand((unsigned)time(NULL));  
    int* A = new int[len];
    for(int i = 0;i < len;++i)
    {
        A[i] =  (rand() % (100-1))+1;
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    auto result = selectMinAndMax(A,len);
    std::cout << "min:" << std::get<0>(result) << " max:" << std::get<1>(result) << std::endl;
    return 0;
}