/*
    红黑树的性质：
        1. 红黑树就是一棵平衡二叉搜索树，其中序遍历单调不减
        2. 节点是红色或黑色
        3. 根结点是黑色
        4. 每个叶子节点（目的是将红黑树变为真二叉树）是黑色的
        5. 每个红色节点的两个子节点都是黑色（即从每个叶子节点到根节点的所有路径上不能有两个连续的红色节点）
        6. 从根节点到叶子节点的所有路径都包含相同数目的黑色节点（黑高度）（若节点只有一个儿子则肯定是黑结点）
        7. 红黑树可变为等价B树
    节点：
        RB_Node结构体，维护信息，左右儿子，父亲，前驱后继函数，真后继函数
    迭代器：
        iterator结构体，各种重载
    搜索：
        private:find(T)和 public:lower_bound(T), upper_bound(T), search(T)
    插入与双红现象：
        为了尽可能维护性质6，每一次插入都要将节点作为红色节点插入。BST的插入应该比较容易实现，但问题在于，性质 5可能被破坏，
    即如果被插入的节点的父节点是红色，就会出现双红现象。
        和其他自平衡二叉树一样，红黑树只有在出现缺陷时才会进行修正，而双红缺陷就是红黑树可能遇到的两大缺陷之一。

    双红修正：
        对于双红现象，我们将会分为以下三种情况修正：
        RR—0（没有双红现象）：
            如果正在修正的节点的父节点是黑色，那么修正就已经结束了（RR-2的递归基）。
        RR-1（叔叔是黑色）（插入到等价 B-树的三节点中）：
            如果正在修正的节点的父亲是红色（祖父一定是黑色），但是叔叔是黑色，那么只需要做 1或 2次旋转，再进行 2次染色就可
        以解决（同时也是RR-2的递归基）。
        RR_2（叔叔是红色）（插入到等价 B-树的四节点中）：
            如果正在修正的节点的父亲是红色（祖父是黑色），而且叔叔也是红色，那么递归就开始了
    删除与失黑现象：
        先介绍删除的思路：一路找到被删除的节点的真后继，然后回来覆盖原节点，如此反复。过程中会出现失黑现象。违背第六条准则
    失黑修正：
        失黑修正有四种情况（根据父亲和兄弟颜色划分），不容易看出，做到心中有 B-树
        LB-1B（父亲为黑色，兄弟为红色）：
            旋转，使得兄弟节点成为父亲节点，兄弟染黑，父亲染红，这样不会导致缺陷上升。
        LB-2（没有红色侄子，且父亲为黑色，兄弟为黑色）：
            染红兄弟，然后递归修正父亲。
        以上两种是需要进行递归调用的修正情况，下面两种是不需要的。
        LB_2R（没有红色侄子，且父亲为红色，兄弟为黑色）：
            只需要对父亲和兄弟各做一次重染色即可。
        LB-3（有红色侄子）：
            旋转一至两次，然后重染色一至两次。
*/
#include <ctime>
#include <iostream>
using namespace std;

#define bro(x) (((x)->ftr->lc == (x)) ? ((x)->ftr->rc) : ((x)->ftr->lc))

typedef bool RB_COLOR;
#define RB_COLOR_RED true
#define RB_COLOR_BLACK false

template <typename T>
class redblacktree
{
protected:
    struct RB_Node;

    RB_Node *_root; //维护根节点
    RB_Node *_hot;  //维护父亲节点

    int _size;

    void init(T);

    RB_Node *zig(RB_Node *); //左旋
    RB_Node *zag(RB_Node *); //右旋

    void SolveDoubleRed(RB_Node *); //双红修正
    void SolveLostBlack(RB_Node *); //失黑修正

    RB_Node *find(T);

    void removetree(RB_Node *); //删除树,dfs后序遍历

public:
    struct iterator;

    redblacktree() : _root(NULL), _hot(NULL), _size(0) {}

    iterator insert(T);      //插入
    bool remove(T);          //删除
    bool remove(iterator &); //删除迭代器

    iterator search(T);      //寻找
    iterator lower_bound(T); //下界寻找
    iterator upper_bound(T); //上界寻找

    void clear(); //移除整棵树， dfs后序遍历入口

    int size();
    bool empty();
    iterator begin();
    static iterator end();
};

template <typename T>
struct redblacktree<T>::RB_Node
{
    T val;
    RB_COLOR RBc;
    RB_Node *ftr;
    RB_Node *lc;
    RB_Node *rc;

    RB_Node(T v = T(), RB_COLOR RB = RB_COLOR_RED, RB_Node *f = NULL, RB_Node *lchild = NULL, RB_Node *rchild = NULL) : val(v), RBc(RB), ftr(f), lc(lchild), rc(rchild) {}

    RB_Node *succ()
    { //后继函数 successive
        RB_Node *ptn = rc;
        while (ptn->lc)
        {
            ptn = ptn->lc;
        }
        return ptn;
    }

    RB_Node *left_node()
    {
        RB_Node *ptn = this;
        if (!lc)
        { //如果当前节点（无左儿子）仍是父节点的左儿子，向上查找，直到节点是右儿子为止，则该节点的父节点就是要找的前驱节点
            while (ptn->ftr && ptn->ftr->lc == ptn)
            {
                ptn = ptn->ftr;
            }
            ptn = ptn->ftr;
        }
        else
        { //若有左儿子，则一直向左儿子的右儿子寻找
            ptn = ptn->lc;
            while (ptn->rc)
            {
                ptn = ptn->rc;
            }
        }
        return ptn;
    }
    RB_Node *right_node() //与上对称
    {
        RB_Node *ptn = this;
        if (!rc)
        {
            while (ptn->ftr && ptn->ftr->rc == ptn)
            {
                ptn = ptn->ftr;
            }
            ptn = ptn->ftr;
        }
        else
        {
            ptn = ptn->rc;
            while (ptn->lc)
            {
                ptn = ptn->lc;
            }
        }
        return ptn;
    }
};

template <typename T>
struct redblacktree<T>::iterator
{ //开始重载运算符
protected:
    RB_Node *_real__node;

public:
    T operator*()
    {
        return _real__node->val;
    }

    bool operator==(iterator const &itr)
    {
        return _real__node == itr._real__node;
    }

    bool operator!=(iterator const &itr)
    {
        return _real__node != itr._real__node;
    }

    bool operator!()
    {
        return !_real__node;
    }

    iterator &operator=(iterator const &itr)
    {
        _real__node = itr._real__node;
        return *this; //这是为了链式赋值
    }

    iterator &operator++()
    {
        _real__node = _real__node->right_node();
        return *this;
    }

    iterator &operator--()
    {
        _real__node = _real__node->left_node();
        return *this;
    }

    iterator(T const &val_vv) : _real__node(find(val_vv)) {}        //寻值构造
    iterator(RB_Node *node__nn = NULL) : _real__node(node__nn) {}   //节点构造
    iterator(iterator const &itr) : _real__node(itr._real__node) {} //迭代器构造
};

//一系列的搜索
template <typename T>
typename redblacktree<T>::RB_Node *redblacktree<T>::find(T v)
{
    RB_Node *ptn = _root;
    _hot = NULL;
    while (ptn && ptn->val != v)
    {
        _hot = ptn;
        if (ptn->val > v)
            ptn = ptn->lc;
        else
            ptn = ptn->rc;
    }
    return ptn;
}

template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::search(T v)
{
    return iterator(find(v));
}

template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::lower_bound(T v)
{
    RB_Node *ptn = _root;
    _hot = NULL;
    while (ptn)
    {
        _hot = ptn;
        if (ptn->val >= v)
            ptn = ptn->lc;
        else
            ptn = ptn->rc;
    }
    if (_hot->val >= v)
        ptn = _hot;
    else
        ptn = _hot->right_node();
    return iterator(ptn);
}

template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::upper_bound(T v)
{
    RB_Node *ptn = _root;
    _hot = NULL;
    while (ptn)
    {
        _hot = ptn;
        if (ptn->val > v)
            ptn = ptn->lc;
        else
            ptn = ptn->rc;
    }
    if (_hot->val > v)
        ptn = _hot;
    else
        ptn = _hot->right_node();
    return iterator(ptn);
}

//开始插入
template <typename T>
void redblacktree<T>::init(T v)
{ //初始化，根节点为黑色
    _root = new RB_Node(v, RB_COLOR_BLACK, NULL, NULL, NULL);
    _size = 1;
}

//右旋
template <typename T>
typename redblacktree<T>::RB_Node *redblacktree<T>::zig(RB_Node *ptn)
{
    ptn->lc->ftr = ptn->ftr;
    if (ptn->ftr)
    {
        if (ptn->ftr->lc == ptn)
            ptn->ftr->lc = ptn->lc;
        else
            ptn->ftr->rc = ptn->lc;
    }
    if (ptn->lc->rc)
        ptn->lc->rc->ftr = ptn;
    ptn->ftr = ptn->lc;
    ptn->lc = ptn->lc->rc;
    ptn->ftr->rc = ptn;
    return ptn->ftr;
}

//左旋
template <typename T>
typename redblacktree<T>::RB_Node *redblacktree<T>::zag(RB_Node *ptn)
{
    ptn->rc->ftr = ptn->ftr;
    if (ptn->ftr)
    {
        if (ptn->ftr->lc == ptn)
            ptn->ftr->lc = ptn->rc;
        else
            ptn->ftr->rc = ptn->rc;
    }
    if (ptn->rc->lc)
        ptn->rc->lc->ftr = ptn;
    ptn->ftr = ptn->rc;
    ptn->rc = ptn->rc->lc;
    ptn->ftr->lc = ptn;
    return ptn->ftr;
}

template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::insert(T v)
{
    RB_Node *ptn = find(v);
    if (ptn)
        return iterator(ptn);
    if (!_hot) // assert(_size == 0)
    {
        init(v);
        return iterator(_root);
    }
    ++_size;
    ptn = new RB_Node(v, RB_COLOR_RED, _hot, NULL, NULL);
    if (_hot->val < v)
        _hot->rc = ptn;
    else
        _hot->lc = ptn;
    SolveDoubleRed(ptn);
    return iterator(ptn);
}

//双红修正
template <typename T>
void redblacktree<T>::SolveDoubleRed(RB_Node *nn)
{
    while (nn->ftr && nn->ftr->RBc == RB_COLOR_RED)
    { //排除递归到根和 RR-0的情况
        RB_Node *pftr = nn->ftr;
        RB_Node *uncle = bro(pftr); //最上面定义的兄弟宏
        RB_Node *grdftr = pftr->ftr;
        if (uncle && uncle->RBc == RB_COLOR_RED)
        { // RR-2
            grdftr->RBc = RB_COLOR_RED;
            uncle->RBc = RB_COLOR_BLACK;
            pftr->RBc = RB_COLOR_BLACK;
            nn->RBc = grdftr;
        }
        else
        { // RR-1
            if (grdftr->lc == pftr)
            {
                if (pftr->lc == nn)
                {
                    if (grdftr == _root)
                    {
                        _root = pftr;
                    }
                    zig(grdftr);
                    pftr->RBc = RB_COLOR_BLACK;
                    grdftr->RBc = RB_COLOR_RED;
                }
                else
                {
                    if (grdftr == _root)
                    {
                        _root = nn;
                    }
                    zag(pftr);
                    zig(grdftr);
                    nn->RBc = RB_COLOR_BLACK;
                    grdftr->RBc = RB_COLOR_RED;
                }
            }
            else
            {
                if (pftr->lc == nn)
                {
                    if (grdftr == _root)
                    {
                        _root = nn;
                    }
                    zig(pftr);
                    zag(grdftr);
                    nn->RBc = RB_COLOR_BLACK;
                    grdftr->RBc = RB_COLOR_RED;
                }
                else
                {
                    if (grdftr == _root)
                    {
                        _root = pftr;
                    }
                    zag(grdftr);
                    pftr->RBc = RB_COLOR_BLACK;
                    grdftr->RBc = RB_COLOR_RED;
                }
            }
            return;
        }
    }
    if (nn == _root)
        nn->RBc = RB_COLOR_BLACK;
}

template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::begin()
{
    RB_Node *ptn = _root;
    while (ptn->lc)
    {
        ptn = ptn->lc;
    }
    return iterator(ptn);
}

//外部接口具体实现（内部接口无法被直接访问，调用外部接口访问）
template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::end() { return iterator((RB_Node *)NULL); }

template <typename T>
int redblacktree<T>::size() { return _size; }

template <typename T>
bool redblacktree<T>::empty() { return !_size; }

template <typename T>
void redblacktree<T>::clear()
{
    removetree(_root);
    _size = 0;
    _root = NULL;
}

//内部接口
template <typename T>
void redblacktree<T>::removetree(RB_Node *ptn)
{
    if (!ptn)
        return;
    removetree(ptn->lc);
    removetree(ptn->rc);
    delete ptn;
}

template <typename T>
void redblacktree<T>::SolveLostBlack(RB_Node *nn)
{
    while (nn != _root)
    {
        RB_Node *pftr = nn->ftr;
        RB_Node *bthr = bro(nn);
        if (bthr->RBc == RB_COLOR_RED)
        { // LB-1
            bthr->RBc = RB_COLOR_BLACK;
            pftr->RBc = RB_COLOR_RED;
            if (_root == pftr)
            {
                _root = bthr;
            }
            if (pftr->lc == nn)
            {
                zag(pftr);
            }
            else
            {
                zig(pftr);
            }
            bthr = bro(nn);
            pftr = nn->ftr;
        }

        if (bthr->lc && bthr->lc->RBc == RB_COLOR_RED)
        { // LB-3
            RB_COLOR oldRBc = pftr->RBc;
            pftr->RBc = RB_COLOR_BLACK;
            if (pftr->lc == nn)
            {
                if (_root == pftr)
                {
                    _root = bthr->lc;
                }
                zig(bthr);
                zag(pftr);
            }
            else
            {
                bthr->lc->RBc = RB_COLOR_BLACK;
                if (_root == pftr)
                {
                    _root = bthr;
                }
                zig(pftr);
            }
            pftr->ftr->RBc = oldRBc;
            return;
        }
        else if (bthr->rc && bthr->rc->RBc == RB_COLOR_RED)
        { // LB-3
            RB_COLOR oldRBc = pftr->RBc;
            pftr->RBc = RB_COLOR_BLACK;
            if (pftr->lc == nn)
            {
                bthr->rc->RBc = RB_COLOR_BLACK;
                if (_root == pftr)
                {
                    _root = bthr;
                }
                zag(pftr);
            }
            else
            {
                if (_root == pftr)
                {
                    _root = bthr->rc;
                }
                zag(bthr);
                zig(pftr);
            }
            pftr->ftr->RBc = oldRBc;
            return;
        }

        if (pftr->RBc == RB_COLOR_RED)
        { // LB-2R
            pftr->RBc = RB_COLOR_BLACK;
            bthr->RBc = RB_COLOR_RED;
            return;
        }
        else
        { // LB-2B
            bthr->RBc = RB_COLOR_RED;
            nn = pftr;
        }
    }
}

//删除
template <typename T>
bool redblacktree<T>::remove(T v)
{
    RB_Node *ptn = find(v);
    RB_Node *node_suc; //节点的后继
    if (!ptn)
        return false;
    --_size;
    while (ptn->lc || ptn->rc)
    {
        if (!(ptn->lc))
            node_suc = ptn->rc;
        else if (!(ptn->rc))
            node_suc = ptn->lc;
        else
            node_suc = ptn->succ();
        ptn->val = node_suc->val;
        ptn = node_suc;
    }
    if (ptn->RBc == RB_COLOR_BLACK)
        SolveLostBlack(ptn);
    if (ptn->ftr)
    {
        if (ptn->ftr->lc == ptn)
            ptn->ftr->lc = NULL;
        else
            ptn->ftr->rc = NULL;
    }
    if (_root == ptn)
    {
        // assert(_size == 0);
        _root = NULL;
    }
    delete ptn;
    return true;
}

template <typename T>
bool redblacktree<T>::remove(iterator &itr)
{
    RB_Node *ptn = itr._real__node;
    itr._real__node = itr._real__node->right_node(); //进行维护，保证删除过后iterator仍旧指向正常结点
    if (!(itr._real__node))
        itr._real__node = ptn->left_node();
    RB_Node *node_suc;
    --_size;
    while (ptn->lc || ptn->rc)
    {
        if (!(ptn->lc))
            node_suc = ptn->rc;
        else if (!(ptn->rc))
            node_suc = ptn->lc;
        else
            node_suc = ptn->succ();
        ptn->val = node_suc->val;
        ptn = node_suc;
    }
    if (ptn->RBc == RB_COLOR_BLACK)
        SolveLostBlack(ptn);
    if (ptn->ftr)
    {
        if (ptn->ftr->lc == ptn)
            ptn->ftr->lc = NULL;
        else
            ptn->ftr->rc = NULL;
    }
    if (_root == ptn)
    {
        // assert(_size == 0);
        _root = NULL;
    }
    delete ptn;
    return true;
}

redblacktree<int> s;
int i;

int main()
{
    srand(time(NULL));
    for (i = 0; i < 256; ++i)
    {
        // s.insert(rand() & 1023);   //限制为0~1023
        s.insert(i);
    }

    redblacktree<int>::iterator it;
    s.remove(100);
    s.remove(0);
    s.remove(1);
    s.remove(233);
    for (it = s.begin(); it != s.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}