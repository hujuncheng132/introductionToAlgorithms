/*
动态规划二：矩阵链乘法
n个矩阵的乘积A1A2...An,通过加括号使计算代价最小
*/

#include<iostream>
#include<limits>
#include<algorithm>
#include<tuple>


std::tuple<int*,int*> matrixChainOrder(int* P,int n)
{
    int* m = new int[(n+1)*(n+1)]; //m[i][j]表示计算矩阵A[i...j]所需的乘法次数的最小值
    for(int i = 1;i <= n;++i)
        m[i*(n+1)+i] = 0; //m[i][i]表示一个单独的矩阵，故乘法次数自然为0
    int* s = new int[(n+1)*(n+1)]; //s保存每个子问题的最优解对应的k值,s[i][j] = k
    for(int i = 1;i <= n;++i)
        s[i*(n+1)+i] = i; //s[i][i]表示链长为1的情形时划分点就是其本身

    for(int len = 2;len <= n;++len) //按子问题的规模从小到大开始求解，设len表示矩阵子链的长度
    {
        for(int i = 1;i <= n-len+1;++i)
        {
            int j = i+len-1;
            m[i*(n+1)+j] = __INT_MAX__;
            for(int k = i;k < j;++k)
            {
                int q = m[i*(n+1)+k]+m[(k+1)*(n+1)+j]+P[i-1]*P[k]*P[j];
                if(m[i*(n+1)+j] > q)
                {
                    m[i*(n+1)+j] = q;
                    s[i*(n+1)+j] = k;
                }
            }
        }
    }
    return std::make_tuple(m,s);     
}

void printSolution(int* s,int start,int end,int n)
{
    if(start == end)
        std::cout << "A" << start;
    else
    {
        std::cout << "(";
        printSolution(s,start,s[start*(n+1)+end],n);
        printSolution(s,s[start*(n+1)+end]+1,end,n);
        std::cout << ")";
    }
}

int main()
{
    const int n = 6;
    int P[n+1] = {30,35,15,5,10,20,25};
    auto result = matrixChainOrder(P,n);
    int* m = std::get<0>(result);
    int* s = std::get<1>(result);
    std::cout << "矩阵链乘法的最少计算量是：" << m[1*(n+1)+n] << std::endl;
    std::cout << "对应的解决方案为：";
    printSolution(s,1,n,n);
    std::cout << std::endl;

    delete[] m;
    delete[] s;

    return 0;
}