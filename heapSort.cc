/*
堆排序
先建立一个
*/
#include <iostream>
#include<limits>

class Heap
{
public:
    Heap(int* A,int length);
    ~Heap(){delete _A;}

    void buildMaxHeap();
    void heapSort();
    void print();
    void printHeap();

    //返回最大优先队列中优先级最高的元素
    int heapMaxmun()
    {
        return _A[0];
    }

    int heapExtractMax(); 
    void heapIncreaseKey(int i,int key);
    void maxHeapInsert(int key);

private:
    int parent(int i){return (i-1)/2;}
    int left(int i){ return 2*i+1;}
    int right(int i){ return 2*(i+1);}
    int exchange(int &i,int &j){ int temp = i;i = j;j = temp;}
    void maxHeapIfy(int i);

    int* _A = nullptr; //用于存放堆的动态数组
    int _length; //数组长度
    int _heapSize; //堆的长度
};

Heap::Heap(int* A,int length): _A(nullptr),_length(length),_heapSize(0)
{
    _A = new int[_length];
    if(A != nullptr)
    {
        for(int i = 0;i < _length;++i)
        {
            _A[i] = A[i];
        }
    }
    buildMaxHeap();
}

/*
维护大根堆的性质
将根节点i和它的左右节点做比较，将最大的元素换到根节点的位置，
然后递归的维护被换下去的节点位置的大根堆性质
*/
void Heap::maxHeapIfy(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if(l < _heapSize && _A[l] > _A[i])
        largest = l;
    if(r < _heapSize && _A[r] > _A[largest])
        largest = r;
    if(largest != i)
    {
        exchange(_A[largest],_A[i]);
        maxHeapIfy(largest);
    }
}

/*
建堆
更具堆的特点，后面一半的节点都是叶子节点，不需要维护大根堆的性质，
从n/2到0依次维护大根堆的性质
*/
void Heap::buildMaxHeap()
{
    _heapSize = _length;
    int mid = _length / 2;
    for(int i = mid;i >= 0;--i)
    {
        maxHeapIfy(i);
    }
}

/*
堆排序
每次都将大根堆的根节点（也就是当前堆最大的元素）和堆尾的元素交换，
然后将堆的size递减，再对根节点进行大根堆性质的维护，这样就能得到剩下的堆中最大的元素，
堆排序是从最后面开始有序
*/
void Heap::heapSort()
{
    for(int i = _length-1;i >= 1;--i)
    {
        exchange(_A[i],_A[0]);
        --_heapSize;
        maxHeapIfy(0);
    }
}

/*
打印数组
*/
void Heap::print()
{
    for(int i = 0;i < _length;++i)
    {
        std::cout << _A[i] << " ";
    }
    std::cout << std::endl;
}

/*
打印堆
*/
void Heap::printHeap()
{
    for(int i = 0;i < _heapSize;++i)
    {
        std::cout << _A[i] << " ";
    }
    std::cout << std::endl;
}

/*
去掉并返回最大优先队列中优先级最高的元素
*/
int Heap::heapExtractMax()
{
    if(_heapSize < 1)
    {
        std::cerr << "空堆";
        exit(1);
    }

    int max = _A[0];
    _A[0] = _A[_heapSize-1];
    --_heapSize;
    maxHeapIfy(0);

    return max;
}

/*
将第i个元素的值增加到key
*/
void Heap::heapIncreaseKey(int i,int key)
{
    if(i >= _heapSize)
    {
        std::cerr << "越界";
        exit(1);
    }
    if(key < _A[i])
    {
        std::cerr << "key无效";
        exit(1);
    }
    _A[i] = key;
    while(i >= 0 && _A[parent(i)] < _A[i])
    {
        exchange(_A[parent(i)],_A[i]);
        i = parent(i);
    }
}

void Heap::maxHeapInsert(int key)
{
    ++_heapSize;
    _A[_heapSize-1] = INT32_MIN;
    heapIncreaseKey(_heapSize-1,key);

}

int main()
{
    // 堆排序演示
    int A[] = {2,1,4,5,3,8,6,7,9};
    Heap heap1(A,sizeof(A)/sizeof(A[0]));
    heap1.heapSort();
    heap1.print();

    // 最大优先队列演示
    int B[] = {2,1,4,5,3,8,6,7,9};
    Heap heap2(B,sizeof(B)/sizeof(B[0]));
    heap2.buildMaxHeap();
    heap2.print();
    std::cout << heap2.heapMaxmun() << std::endl;
    std::cout << heap2.heapExtractMax() << std::endl;
    heap2.printHeap();
    heap2.heapIncreaseKey(7,10);
    heap2.printHeap();
    heap2.maxHeapInsert(99);
    heap2.printHeap();

    return 0;
}