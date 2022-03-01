#include <iostream>
#include <string.h>
using namespace std;
#define BinNodePosi(T) BinNode<T>*

template <typename T>
class BinNode {
public:
    BinNode(const T& data)
        : _data(data)
        , lchild(nullptr)
        , rchild(nullptr)
        , parent(nullptr)
        , Ltag(0)
        , Rtag(0)
    {
    }
    char _data;
    BinNodePosi(T) lchild;
    BinNodePosi(T) rchild;
    BinNodePosi(T) parent;
    bool Ltag, Rtag;
};

template <typename T>
void travIn_R(BinNodePosi(T) x, int n)
{
    if (!x)
        return;
    ++n;
    travIn_R(x->lchild, n);
    cout << x->_data <<":"<< n << "  ";
    travIn_R(x->rchild, n);
}


template <typename T>
class Thread_BiTree {
public:
    //先序 --创建树
    Thread_BiTree(string s)
        : _pRoot(nullptr)
        , Prev(nullptr)
    {
        size_t index = 0;
        _CreatTree(_pRoot, s, s.size(), index); //创建二叉树
    }

protected:
    void _CreatTree(BinNodePosi(T) & Root, string s, size_t size, size_t& index)
    {
        if (size == 0) {
            cout << "输入有误 " << endl;
            return;
        }
        if (index < size && s[index] != '#') {
            Root = new BinNode<T>(s[index]);
            _CreatTree(Root->lchild, s, size, ++index);
            _CreatTree(Root->rchild, s, size, ++index);
        }
    }

public:
    void travIn(){
        travIn_R(_pRoot,0);
    }

public:
    //先序--线索化二叉树
    void PreOrderThreading()
    {
        _PreOrderThreading(this->_pRoot);
    }
    //先序--遍历 线索二叉树
    void PreOrder()
    {
        _PreOrder(this->_pRoot);
    }

protected:
    //先序--线索化二叉树--C
    //思路：先看左子树， 找下一个节点的时候，再检测上一个节点的右节点
    void _PreOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        if (Root->lchild == NULL) //没有左子树
        {
            Root->lchild = Prev; //前驱
            Root->Ltag = 1;
        }
        if (Prev != NULL && Prev->rchild == NULL) // 上一个节点有没有右子树
        { //Prev第一次进来 为空
            Prev->rchild = Root; //后继
            Prev->Rtag = 1;
        }
        Prev = Root; //前驱,每次记住上次的节点

        //判断Root是否有左右孩子
        if (Root->Ltag == 0)
            _PreOrderThreading(Root->lchild);
        if (Root->Rtag == 0)
            _PreOrderThreading(Root->rchild);
    }
    //先序--遍历 线索二叉树--C
    void _PreOrder(BinNodePosi(T) Root)
    {
        if (Root == NULL) {
            return;
        }
        BinNodePosi(T) pCur = Root;
        while (pCur != NULL) {
            while (pCur->lchild != NULL && pCur->Ltag == 0) //找到最左边的节点,左标记一直为1
            {
                cout << pCur->_data << ' ';
                pCur = pCur->lchild;
            }
            //到这来，左边的的节点还没有访问
            cout << pCur->_data << ' ';

            if (pCur->Ltag == 1) //遇到线索 就看右节点
            {
                pCur = pCur->rchild;
            }
            while (pCur != NULL) //循环右节点
            {
                if (pCur->lchild != NULL && pCur->Ltag == 0) //遇到左节点存在 ， 则访问
                    break;
                cout << pCur->_data << ' ';
                pCur = pCur->rchild;
            }
        }
    }

public:
    //中序--线索化二叉树
    void InOrderThreading()
    {
        _InOrderThreading(_pRoot);
    }
    //中序--遍历线索二叉树
    void InOrder()
    {
        _InOrder(this->_pRoot);
    }

protected:
    //中序--线索化二叉树--C
    //思路:按 左-根-右的顺序   先找到最左边的节点-> 和先序线索一样 ,先链接左子树，执行到下一个节点在看上次节点的右子树 -> 右子树
    void _InOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        _InOrderThreading(Root->lchild); // 左

        if (Root->lchild == NULL) //根
        {
            Root->Ltag = 1;
            Root->lchild = Prev;
        }
        if (Prev != NULL && Prev->rchild == NULL) {
            Prev->rchild = Root;
            Prev->Rtag = 1;
        }
        Prev = Root;
        _InOrderThreading(Root->rchild); //右
    }
    //中序--遍历二叉树--C
    //思路：找到中序开始的节点（最左边的节点）-> (后继 )它的根节点，若没有则找右节点
    void _InOrder(BinNodePosi(T) Root)
    {
        if (Root == NULL) {
            return;
        }
        BinNodePosi(T) pCur = Root;
        while (pCur) {
            while (pCur->Ltag == 0) //找最左边的节点
            {
                pCur = pCur->lchild;
            }
            cout << pCur->_data << ' ';

            while (pCur && pCur->Rtag == 1) //找中序后继节点
            {
                pCur = pCur->rchild;
                cout << pCur->_data << ' ';
            }
            //没有后继，有右子树
            pCur = pCur->rchild;
        }
    }

public:
    //后序--线索二叉树
    void PostOrderThreading()
    {
        _PostOrderThreading(_pRoot);
    }

    void PostOrder()
    {
        _PostOrder(this->_pRoot);
    }

protected:
    //后序--线索二叉数--C
    //思路：左-右-根  和前面的一样
    void _PostOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        _PostOrderThreading(Root->lchild);
        _PostOrderThreading(Root->rchild);

        if (Root->lchild == NULL) {
            Root->lchild = Prev;
            Root->Ltag = 1;
        }
        if (Prev != NULL && Prev->rchild == NULL) {
            Prev->rchild = Root;
            Prev->Rtag = 1;
        }
        if(Prev!=NULL&&Prev->rchild!=NULL)
        Prev->parent=Root;
        Prev = Root;
    }

    void _PostOrder(BinNodePosi(T) Root)
    {
        if (Root) {
            BinNodePosi(T) pCur = Root;
            Prev = NULL;
            while (pCur != NULL) {
                //第一步：找树最左边的节点
                while (pCur->lchild != Prev && pCur->Ltag == 0) //左子树
                {
                    pCur = pCur->lchild;
                }
                //循环结束后 pCur== Root 或者为空

                //第二步：访问后继
                while (pCur && pCur->Rtag == 1) {
                    cout << pCur->_data << ' ';
                    Prev = pCur;
                    pCur = pCur->rchild;
                }
                //判断此时pCur是不是指向了根节点
                if (pCur == Root) {
                    cout << pCur->_data << ' ';
                    return;
                }
                while (pCur && pCur->rchild == Prev) {
                    cout << pCur->_data << ' ';
                    Prev = pCur;
                    pCur = pCur->parent; //往上一级走
                }
                //这里不能用NULL判断，而是用Rtag
                if (pCur && pCur->Rtag == 0) {
                    pCur = pCur->rchild;
                }
            }
            //end-while
        }
    }

public:
    void insert_as_lchild(BinNodePosi(T) p,const T& e){
        if(p->lchild==nullptr)
            p->lchild=new BinNode<T>(e);
    }
    
    void insert_as_rchild(BinNodePosi(T) p, const T& e){
        if(p->rchild==nullptr)
            p->rchild=new BinNode<T>(e);
    }

    
    BinNodePosi(T) _pRoot = nullptr;
    BinNodePosi(T) Prev = nullptr; //记录
};