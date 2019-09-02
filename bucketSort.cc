/*
桶排序
设置K个桶，将每个数都分到其中的某个桶中，然后对桶内的元素再进行排序
*/
#include<iostream>
#include<limits>

const int BUCKET_COUNTS = 128; //桶的数量为128

struct listNode
{
    int value;
    listNode* pNext;
    listNode(int val = 0,listNode* p = nullptr):value(val),pNext(p){}
};

void insertToBucket(listNode* item,listNode* buckets,int bucketNumber)
{
    listNode* head = &buckets[bucketNumber];
    listNode* p = head->pNext;
    listNode* pre = head;
    while(p)
    {
        if(item->value >= p->value)
        {
            pre = p;
            p = p->pNext;
        }
        else
            break;
    }
    pre->pNext = item;
    item->pNext = p;
}

// 将元素插入桶内
void bucketSort(int* A,int len)
{
    int min = __INT_MAX__,max = INT32_MIN;
    for(int i = 0;i < len;++i)
    {
        if(A[i] < min)
            min = A[i];
        else if(A[i] > max)
            max = A[i];
    }
    double preBucketSize = (max-min+1)*1.0 / (BUCKET_COUNTS-1); //每个桶中的数据范围大小(BUCKET_COUNTS-1是防止由于误差导致越界)
    listNode* buckets = new listNode[BUCKET_COUNTS]; //创建BUCKET_COUNTS个桶
    
    for(int i = 0;i < len;++i)
    {
        int bucketNumber = static_cast<int>((A[i]-min+1) / preBucketSize);
        listNode* item = new listNode(A[i]);
        insertToBucket(item,buckets,bucketNumber);
        delete item;
    }
    
    int index = 0;
    for(int i = 0;i < BUCKET_COUNTS;++i)
    {
        if(buckets[i].pNext)
        {
            listNode* p = buckets[i].pNext;
            while(p)
            {
                A[index++] = p->value;
                p = p->pNext;
            }
        }
    }
    delete[] buckets;
}


int main()
{
    srand((unsigned)time(NULL));  
    int* A = new int[100000000];
    for(int i = 0;i < 100000000;++i)
    {
        A[i] =  (rand() % (100000000-1))+1;
    }
    std::cout << "ok\n";

    bucketSort(A,100000000);
    for(int i = 0;i < sizeof(A)/sizeof(A[0]);++i)
        std::cout << A[i] << " ";
    std::cout << std::endl;
    std::cout << "ok\n";

    return 0;
}