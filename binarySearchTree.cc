/*
二叉搜索树
*/
#include<stack>
#include<iostream>
#include<string>

struct BinaryTreeNode
{
    int key = 0;
    int value = 0;
    BinaryTreeNode* pLeft = nullptr;
    BinaryTreeNode* pRight = nullptr;
    BinaryTreeNode* pParent = nullptr;
    BinaryTreeNode(int k = 0):key(k){}

};

class BinarySearchTree
{
public:
    void preOrderTreeWalk(); //先序遍历
    void inOrderTreeWalk(); //中序遍历:二叉搜索树的中序遍历为严格递增的顺序
    void afterOrderTreeWalk(); //后序遍历
    BinaryTreeNode* TreeSearch(int key); //查找关键字为key的节点
    BinaryTreeNode* TreeMin(); //查找最小关键字元素
    BinaryTreeNode* TreeMax(); //查找最大关键字元素
    BinaryTreeNode* TreePredecessor(BinaryTreeNode* x); //查找中序遍历x的前驱
    BinaryTreeNode* TreSuccessor(BinaryTreeNode* x); //查找中序遍历x的后继
    void TreeInsert(BinaryTreeNode &x); //将节点x插入到二叉搜索树
    void TreeDelete(BinaryTreeNode* x); //将节点x从二叉搜索树中删除

    BinarySearchTree(BinaryTreeNode* root):pRoot(root){}
private:
    void transplant(BinaryTreeNode* u,BinaryTreeNode* v); //用子树v替换子树u
    BinaryTreeNode* pRoot = nullptr;
};


void BinarySearchTree::preOrderTreeWalk()
{
    std::stack<BinaryTreeNode*> BinaryTreeStack;
    BinaryTreeNode* p = pRoot;
    while(p || !BinaryTreeStack.empty())
    {
        while(p)
        {
            std::cout << p->key << " ";
            BinaryTreeStack.push(p); //第一次遇到
            p = p->pLeft;
        }
        if(!BinaryTreeStack.empty())
        {
            p = BinaryTreeStack.top();
            BinaryTreeStack.pop();
            p = p->pRight;
        }
    }
    std::cout << std::endl;   
}

void BinarySearchTree::inOrderTreeWalk()
{
    std::stack<BinaryTreeNode*> BinaryTreeStack;
    BinaryTreeNode* p = pRoot;
    while(p || !BinaryTreeStack.empty())
    {
        while(p)
        {
            BinaryTreeStack.push(p);
            p = p->pLeft;
        }
        if(!BinaryTreeStack.empty())
        {
            p = BinaryTreeStack.top();//第二次遇到
            std::cout << p->key << " ";
            BinaryTreeStack.pop();
            p = p->pRight;
        }
    }
    std::cout << std::endl;   
}

void BinarySearchTree::afterOrderTreeWalk()
{
    std::stack<BinaryTreeNode*> BinaryTreeStack;
    BinaryTreeNode* p = pRoot;
    BinaryTreeNode* lastVisit = nullptr; //lastVisit用于存储最近访问的一个结点
    while(p || !BinaryTreeStack.empty())
    {
        while(p)
        {
            BinaryTreeStack.push(p);
            p = p->pLeft;
        }
        if(!BinaryTreeStack.empty())
        {
            p = BinaryTreeStack.top();
            if(p->pRight != nullptr  && p->pRight != lastVisit) //第二次遇到
            {
                p = p->pRight;
            }
            else //第三次遇到
            {
                std::cout << p->key << " ";
                BinaryTreeStack.pop();
                lastVisit = p;
                p = nullptr;
            }
        }
    }
    std::cout << std::endl;   
}

BinaryTreeNode* BinarySearchTree::TreeSearch(int key)
{
    BinaryTreeNode* p = pRoot;
    while(p != nullptr && key != p->key)
    {
        if(key < p->key)
            p = p->pLeft;
        else
            p = p->pRight;
    }
    return p;
}

BinaryTreeNode* BinarySearchTree::TreeMin()
{
    BinaryTreeNode* p = pRoot;
    if(p == nullptr)
        return nullptr;
    while(p->pLeft != nullptr)
        p = p->pLeft;

    return p;  
}

BinaryTreeNode* BinarySearchTree::TreeMax()
{
    BinaryTreeNode* p = pRoot;
    if(p == nullptr)
        return nullptr;
    while(p->pRight != nullptr)
        p = p->pRight;

    return p;  
}

BinaryTreeNode* BinarySearchTree::TreePredecessor(BinaryTreeNode* x)
{
    if(x->pLeft != nullptr) //左子树不为空
        return BinarySearchTree(x->pLeft).TreeMax(); //返回左子树中的最大节点
    BinaryTreeNode* p = x->pParent;
    // 如果左子树为空，首先找到x和x的祖先结点中第一个为左节点的节点，该节点的父节点即为后继
    while(p != nullptr && x == p->pLeft)
    {
        x = p;
        p = p->pParent;
    }
    return p;

}


BinaryTreeNode* BinarySearchTree::TreSuccessor(BinaryTreeNode* x)
{
    if(x->pRight != nullptr) //右子树不为空
        return BinarySearchTree(x->pRight).TreeMin(); //返回右子树中的最小节点
    BinaryTreeNode* p = x->pParent;
    // 如果右子树为空，首先找到x和x的祖先结点中第一个为右节点的节点，该节点的父节点即为后继
    while(p != nullptr && x == p->pRight)
    {
        x = p;
        p = p->pParent;
    }
    return p;
}

//二叉搜索树插入的节点一定位于叶节点，因此可能存在不平衡的现象
void BinarySearchTree::TreeInsert(BinaryTreeNode& z)
{
    BinaryTreeNode* pre = nullptr;
    BinaryTreeNode* p = pRoot;
    while(p != nullptr)
    {
        pre = p;
        if(z.key < p->key)
            p = p->pLeft;
        else
            p = p->pRight;
    }
    z.pParent = pre;
    if(pre == nullptr) //树为空
        pRoot = &z;
    else if(z.key < pre->key)
        pre->pLeft = &z;
    else
        pre->pRight = &z;
}

void BinarySearchTree::transplant(BinaryTreeNode* u,BinaryTreeNode* v)
{
    if(u == nullptr)
        return;

    if(u->pParent == nullptr) //u为根节点
        pRoot = v;
    else if(u == u->pParent->pLeft) //u为左节点
        u->pParent->pLeft = v;
    else //u为右节点
        u->pParent->pRight = v;
    
    //将v的父节点设为u的父节点(只负责节点的替换已经父节点的更改，子节点不进行更改，交由调用者自己去更改子节点)
    if(v != nullptr)
        v->pParent = u->pParent;
}

void BinarySearchTree::TreeDelete(BinaryTreeNode* x)
{
    if(x == nullptr)
        return;

    //只要其中一个子节点为空，就用另一个子节点替换该节点
    if(x->pLeft == nullptr)
        transplant(x,x->pRight);
    else if(x->pRight == nullptr)
        transplant(x,x->pLeft);
    //如果两个子节点都不为空
    else
    {
        // 寻找x的后继
        BinaryTreeNode* y = BinarySearchTree(x->pRight).TreeMin();
        if(y->pParent != x) //如果x的后继y不是x的右节点，则将用y的右节点替换y，并将y的右节点设为x的右节点
        {
            transplant(y,y->pRight);
            y->pRight = x->pRight;
            y->pRight->pParent = y;
        }
        transplant(x,y); // 最后再用y去替换x节点，并将y的左节点设为x的左节点
        y->pLeft = x->pLeft;
        y->pLeft->pParent = y;
    }
    
}


int main()
{
    BinaryTreeNode A,B,C,D,E,F,G,H,I;
    A.key = 5;
    B.key = 2;
    C.key = 8;
    D.key = 1;
    E.key = 3;
    F.key = 4;
    G.key = 6;
    H.key = 7;
    I.key = 9;
    A.pLeft = &B;
    A.pRight = &C;
    B.pParent = &A;
    C.pParent = &A;
    B.pLeft = &D;
    B.pRight = &F;
    D.pParent = &B;
    F.pParent = &B;
    C.pLeft = &G;
    C.pRight = &I;
    G.pParent = &C;
    I.pParent = &C;
    F.pLeft = &E;
    G.pRight = &H;
    E.pParent = &F;
    H.pParent = &G;

    BinarySearchTree BSTree(&A);
    BSTree.preOrderTreeWalk();
    BSTree.inOrderTreeWalk();
    BSTree.afterOrderTreeWalk();
    std::cout << (BSTree.TreeSearch(5))->key << std::endl;
    std::cout << BSTree.TreeMin()->key << std::endl;
    std::cout << BSTree.TreeMax()->key << std::endl;
    std::cout << (BSTree.TreePredecessor(&H))->key << std::endl;
    std::cout << (BSTree.TreSuccessor(&F))->key << std::endl;
    BinaryTreeNode J(10);
    BSTree.TreeInsert(J);
    BSTree.inOrderTreeWalk();
    BSTree.TreeDelete(&J);
    BSTree.inOrderTreeWalk();

    return 0;
}