/*
动态规划：最长公共子序列
通过比较最后x和y的最后一位字符是否相同，进而将问题划分成规模更小的子问题
*/
#include<iostream>
#include<algorithm>
#include<tuple>
#include<stack>

enum class Move{UP,LEFT,DIAGONAL}; //UP表示上移，LEFT表示左移，DIAGONAL表示左上对角移

std::tuple<int*,Move*> lcsLength(const char* x,const char* y,int m,int n)
{
    int* c = new int[(m+1)*(n+1)]; //c用来保存LCS的值，c[i][j]表示X(i)和Y(j)的LCS长度
    Move* b = new Move[(m+1)*(n+1)]; //b用来保存最优解
    // X或Y为空，则LCS为0
    for(int i = 0;i <= m;++i)
    {
        c[i*(n+1)] = 0; //c[i][0] = 0 
    }
    for(int j = 0;j <= n;++j)
    {
        c[j] = 0; //c[0][j] = 0
    }

    for(int i = 1;i <= m;++i)
    {
        for(int j = 1;j <= n;++j)
        {
            if(x[i-1] == y[j-1]) //如果最后一位字符相等
            {
                //如果x[i] == y[j]，则c[i][j] = c[i-1][j-1]+1
                c[i*(n+1)+j] = c[(i-1)*(n+1)+(j-1)] + 1; 
                b[i*(n+1)+j] = Move::DIAGONAL;
            }
            else //如果最后一位字符不等
            {
                //如果x[i] != y[j]，则c[i][j] = max(c[i][j-1],c[i-1][j])
                c[i*(n+1)+j] = std::max<int>(c[(i-1)*(n+1)+j],c[i*(n+1)+(j-1)]);
                if(c[i*(n+1)+j] == c[(i-1)*(n+1)+j])
                    b[i*(n+1)+j] = Move::UP;
                else
                    b[i*(n+1)+j] = Move::LEFT;
            }
        }
    }
    return std::make_tuple(c,b);
}

void printSolution(Move* b,char* x,char* y,int m,int n)
{
    std::stack<char> lcs;
    int i = m,j = n;
    while(i > 0 && j > 0)
    {
        switch(b[i*(n+1)+j])
        {
            case Move::UP:
                --i;
                break;
            case Move::LEFT:
                --j;
                break;
            case Move::DIAGONAL:
                lcs.push(x[i-1]);
                // lcs.push(y[j-1]);
                --i;
                --j;
                break;
            default:
                break;
        }
    }
    while(!lcs.empty())
    {
        std::cout << lcs.top();
        lcs.pop();
    }
    std::cout << std::endl;
}

int main()
{
    const int m = 7;
    const int n =6;
    char x[m] = {'A','B','C','B','D','A','B'};
    char y[n] = {'B','D','C','A','B','A'};
    auto result = lcsLength(x,y,m,n);
    int* c = std::get<0>(result);
    Move* b = std::get<1>(result);
    for(int i = 0;i <= m;++i)
    {
        for(int j = 0;j <= n;++j)
        {
            switch(b[i*(n+1)+j])
            {
                case Move::UP:
                    std::cout << "上移" << c[i*(n+1)+j] << " ";
                    break; 
                case Move::LEFT:
                    std::cout << "左移" << c[i*(n+1)+j] << " ";
                    break;
                case Move::DIAGONAL:
                    std::cout << "斜移" << c[i*(n+1)+j] << " ";
                    break;
                default:
                    std::cout << "空  " << c[i*(n+1)+j] << " ";
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "LCS长度为：" << c[m*(n+1)+n] << std::endl;
    printSolution(b,x,y,m,n);

    delete[] c;
    delete[] b;
    return 0;
}