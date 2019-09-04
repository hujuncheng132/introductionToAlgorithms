/*
动态规划一：钢条切割
每段长度为i的钢条能够带来P(i)的收益，如何将长度为n的钢条进行切割才能得到最大的收益R(n)；
一种切割方法是，首先将钢条切割为长度为i和n-i的两段，接着求这两段的最优切割收益R(i)和R(n-i),最终的最大切割收益即为两段最优收益之和的最大值：
R(n) = max(P(n),R(1)+R(n-1),R(2)+R(n-2),...,R(i)+R(n-i),...,R(n-1)+R(1));
另一种更简单的切割方法是，将钢条从左边切割下长度为i的一段，只对右边剩下的长度为n-i的一段进行切割，对左边的一段不再进行切割：
R(n) = max(P(1)+R(n-1),P(2)+R(n-2),...,P(i)+R(n-i),...,P(n)+R(0));
钢条切割问题符合最优子结构问性质：问题的最优解由相关子问题的最后解组合而成，而这些子问题可以独立求解；
*/

#include<iostream>
#include<limits>
#include<algorithm>
#include<tuple>
/*
有两种方法可以对动态规划进行求解：一是带备忘录的自顶向下法，另一种是自底向上法
*/

// 第一种方法：带备忘录的自顶向下法
// 该方法仍然按照自然的递归形式编写程序，但是在递归过程中会保存每个子问题的解(用数组或者散列表),
// 当需要一个子问题的解时，首先检查是否已经保存过此解，如果是则直接返回，这样就节省了计算时间；
int memoizedCutRodAux(int* P,int n,int* R)
{
    if(R[n] >= 0)
        return R[n]; //如果之前已经求解过这个子问题，则直接返回结果
    
    int q; //q保存最大收益
    if(n == 0) //当n等于0时，最大收益自然为0
        q = 0;
    else //当n大于0时，按照公式：R(n) = max(P(1)+R(n-1),P(2)+R(n-2),...,P(i)+R(n-i),...,P(n)+R(0))求最大值
    {
        q = INT32_MIN;
        for(int i = 1;i <= n;++i)
        {
            q = std::max<int>(q,P[i]+memoizedCutRodAux(P,n-i,R)); //这里进行递归求解
        }
    }
    R[n] = q;
    return q;
}

int memoizedCutRod(int* P,int n) //p为不同长度的钢条的收益，n为钢条的长度
{
    int* R = new int[n+1]; //用于记录递归调用过程中子问题的结果，如果这个子问题之前已经求解过就直接返回结果
    for(int i = 0;i <= n;++i)
        R[i] = INT32_MIN; //初始时，所有子问题的解都设为负无穷
    return memoizedCutRodAux(P,n,R);
    delete[] R;
}

//如果直接采用递归方法，不通过备忘录保存子问题的解，则会造成许多重复计算问题
int CutRodAux(int* P,int n)
{
    if(n == 0)
        return 0;
    int q = INT32_MIN;
    for(int i = 1;i <= n;++i)
    {
        q =  std::max<int>(q,P[i]+CutRodAux(P,n-i));
    }
    return q;
}

// 第二种方法：自底向上法
// 这种方法通过对子问题的求解顺序进行调整，例如按子问题规模从小到大进行求解，
// 当第一次求解某个子问题时，保证它所依赖的那些更小的子问题已经求解完毕，且结果也已保存
int bottomUpCutRod(int* P,int n)
{
    int* R = new int[n+1]; //用于保存子问题的解
    R[0] = 0;
    for(int j = 1;j <= n;++j) //按子问题的规模从小到大开始求解
    {
        int q = INT32_MIN;
        for(int i = 1;i <= j;++i)
        {
            q = std::max<int>(q,P[i]+R[j-i]); //R(n) = max(P(1)+R(n-1),P(2)+R(n-2),...,P(i)+R(n-i),...,P(n)+R(0)
        }
        R[j] = q;
    }
    int result = R[n];
    delete[] R;
    return result;
}


/*
重构解:前面的动态规划算法只返回了最优解的收益值，并未返回解本身
可以通过扩展前面的算法，使之对每个子问题不仅保存最优收益值，同时还保存对应的切割方案
*/
std::tuple<int*,int*> extendedBottomUpCutRod(int* P,int n)
{
    int* R = new int[n+1]; //保存每个子问题的最优解
    int* S = new int[n+1]; //保存每个子问题的最优解对应的i值：R(n) = max(P(1)+R(n-1),P(2)+R(n-2),...,P(i)+R(n-i),...,P(n)+R(0))
    R[0] = 0;
    S[0] = 0;
    for(int j = 1;j <= n;++j)
    {
        int q = INT32_MIN;
        for(int i = 1;i <= j;++i)
        {
            if(q < P[i]+R[j-i])
            {
                q = P[i]+R[j-i];
                S[j] = i; //S[j] = i表示切割的第一段钢条的长度为i
            }
        }
        R[j] = q;
    }

    return std::make_tuple(R,S);
}

//打印最优解已经最优解决方案
void printCutRodSolution(int* P,int n)
{
    auto solution = extendedBottomUpCutRod(P,n);
    int* R = std::get<0>(solution);
    int* S = std::get<1>(solution);
    std::cout << n << ":最优解为：" << R[n] << std::endl;
    std::cout << "对应的最优解决方案为：";
    while(n > 0)
    {
        std::cout << S[n] << " ";
        n = n-S[n];
    }
    std::cout << std::endl;
}

int main()
{
    int P[] = {0,1,5,8,9,10,17,17,20,24,30};
    for(int i = 0;i <= 10;++i)
    {
        std::cout << memoizedCutRod(P,i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0;i <= 10;++i)
    {
        std::cout << bottomUpCutRod(P,i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0;i <= 10;++i)
    {
        std::cout << CutRodAux(P,i) << " ";
    }
    std::cout << std::endl;

    for(int i = 0;i <= 10;++i)
    {
       printCutRodSolution(P,i);
    }

    return 0;
}