/*
简单实现hash table
*/
#include<iostream>
#include<string>
#include<cmath>
#include<vector>

/*
将关键字转换为自然数
假设关键字都是由标准的ASCII码组成（前7位表示，共128位）
*/
unsigned int keyToInt(std::string str)
{
    unsigned int len = str.size();
    unsigned int key = 0;
    unsigned int d = 128;
    for(int i = len-1;i >= 0;--i)
    {
        key += static_cast<unsigned int>(str[i])*static_cast<unsigned int>(pow(d,i));
    }
    return key;
}

/*
散列函数
*/

//除法散列法：用一个特定的素数来除所给的关键字，所得的余数即为该关键字的散列值
//通常选择一个不太接近2的整数幂的素数,如果M1设为2^p，则h(key)的结果就是key的p个最低位数字，这样容易出现冲突
//除非已知各种最低P位的排列形式为等可能的，否则在设计散列函数时最好考虑关键字的所有位
const unsigned int M1 = 701;// 假设关键字的范围为2000,则装载因子为2000/701=3
unsigned int hashFunction1(std::string str)
{
    unsigned int key = keyToInt(str);
    return key%M1;
}

//乘法散列法：第一步用关键字key乘上常数A(0<A<1),并提取key*A的小数部分，第二步用M2乘这个值再向下取整，K有一个比较理想的值0.618
//乘法散列法在计算机上比较容易实现，计算机字长假设为32位，上述步骤可以转换成key*S,然后取低32位的前14位
const unsigned int p = 14; //用于取前14位，散列表的大小为pow(2,14)
const double A = (sqrt(5.0)-1)/2; //A的最佳取值为根号5-1再除2，约等于0.618
const unsigned int S = static_cast<unsigned int>(A*pow(2,32)); 
unsigned int hashFunction2(std::string str)
{
    unsigned int key = keyToInt(str);
    return (S*key)>>(32-p); //取高14位作为结果
}

//全域散列法：从一组精心设计的函数中，随机选取一个作为散列函数
//由于随机选取散列函数，算法在每次执行时都会有所不同，甚至对于相同的输入都会如此

//装载因子：假设关键字的范围大小是N，散列表的范围大小是M，则装载因子为N/M


/*
开放寻址中的探查方法：均匀散列要求有m!个探查序列
*/

//线性探查：只能得到m种不同的探查序列，存在一次群集问题，
//即随着连续被占用的槽不断增加，平均查找时间也不断增减
std::vector<unsigned int> linearProbing(std::string key,unsigned int i)
{
    std::vector<unsigned int> T;
    //采用的辅助散列函数假设为除法散列法
    for(unsigned int j = 0;j < M1;++j)
    {
        T.push_back((hashFunction1(key)+i+j) % M1);
    }
    return T;
}

//二次探查：也只能得到m种不同的探查序列，存在二次群集问题
//为了能够充分利用散列表，c1,c2,M的值都要受到限制
std::vector<unsigned int> quadraticProbing(std::string key,unsigned int i)
{
    std::vector<unsigned int> T;
    unsigned int c1 = 13;
    unsigned int c2 = 33; 
    //采用的辅助散列函数假设为除法散列法
    for(unsigned int j = 0;j < M1;++j)
    {
        T.push_back((hashFunction1(key)+c1*(i+j)+c2*(i+j)*(i+j)) % M1);
    }
    return T;
}

//双重散列：解决开放寻址法最好的方法之一，当m为素数或者2的幂时，双重散列能够得到m^2种探查序列
//为了能够查找整个散列表，值h2(k)必须要与表的大小m互素，有以下两种方法：
//一种方法是，取m为2的幂，并设计一个总产生奇数的h2;
//另一种方法是，取m为素数，并设计一个总返回较m小的正整数的函数h2
const unsigned int M = 701;
unsigned int h1(std::string str)
{
    unsigned int key = keyToInt(str);
    return key%M;
}
unsigned int h2(std::string str)
{
    unsigned int key = keyToInt(str);
    return 1+key%(M-1);
}
std::vector<unsigned int> doubleHashing(std::string key,unsigned int i)
{
    std::vector<unsigned int> T;
    //采用的辅助散列函数假设为除法散列法
    for(unsigned int j = 0;j < M;++j)
    {
        T.push_back((h1(key)+(i+j)*h2(key))%M);
    }
    return T;
}


int main()
{
    std::cout << hashFunction1("hello") << std::endl;
    std::cout << hashFunction2("hello") << std::endl;
    std::vector<unsigned int> T = doubleHashing("hello",2);
    std::cout << T.size() << std::endl;
    for(auto item:T)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
