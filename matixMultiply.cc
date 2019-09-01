/*
矩阵乘法
*/
#include<iostream>

template <typename T>
T* sourgeMatrixMultiply(T* A,T* B,size_t M,size_t N,size_t S)
{
    T* C = new T[M*S];
    for(auto m = 0;m < M;++m)
    {
        for(auto s = 0;s < S;++s)
        {
            C[m*S+s] = 0;
            for(int n = 0;n < N;++n)
            {
                C[m*S+s] += A[m*N+n]*B[n*S+s];
            }
        }
    }
    return C;
}

int main()
{
    int A[2][3] = {{1,2,3},{4,5,6}};
    int B[3][2] = {{1,2},{3,4},{5,6}};
    int* C = sourgeMatrixMultiply(reinterpret_cast<int*>(A),reinterpret_cast<int*>(B),2,3,2);
    for(int i = 0;i < 2;++i)
    {
        for(int j = 0;j < 2;++j)
        {
            std::cout << C[i*2+j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
