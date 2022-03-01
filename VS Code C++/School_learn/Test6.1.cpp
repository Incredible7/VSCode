#include <iostream>
#include <List>
using namespace std;

const int Max = 10;

typedef class UnDirectedGragh
{
public:
    UnDirectedGragh() //二维数组初始化
    {
        edge = 0;
        for (int i = 0; i < Max; i++)
        {
            node[i] = -1; //初始化结点数组
            for (int j = 0; j < Max; j++)
                gragh[i][j] = 99999;
        }
    }
    void Create(); //创建、自定义图结构7
    bool Judge();  //判断是否是树
    //一个无向图G是一棵树的条件为：G必须是无回路的连通图或n-1条边的连通图
    void Floyd();                                 //弗洛伊德最短路径算法
    void print();                                 //打印图结构
    void search(int entrance, int mid, int exit); //递归查找最短路径
    void next(int x);                             //遍历node[]判断是否为无环图

private:
    int gragh[Max][Max]; //二维数组储存图
    int node[Max];       //结点数组用于判断结点是否创立
    int path[Max][Max];
    list<int> List; //最短路径
    int edge;       //图边数
} UGragh;

void UGragh::Create()
{
    int x, y;
    bool judge = true;
    while (judge)
    {
        cout << "请输入建立连通的两节点下标：";
        cin >> x >> y;
        node[x] = node[y] = 0;
        cout << "请输入路径长度：";
        cin >> gragh[x][y];
        gragh[y][x] = gragh[x][y];
        cout << "建立成功！是否继续输入？ 1、是 0、否";
        edge++;
        cin >> judge;
        system("cls");
    }
}

void UGragh::print()
{
    for (int i = 0; i < Max; i++)
    {
        if (node[i] == 0)
        {
            cout << "G[" << i << "] -> ";
            for (int j = 0; j < Max; j++)
            {
                if (gragh[i][j] != 99999)
                    cout << "G[" << j << "] = " << gragh[i][j] << "  ";
            }
            cout << endl;
        }
    }
}

void UGragh::next(int x)
{
    for (int i = 0; i < Max; i++)
    {
        if (gragh[x][i] != 99999)
        {
            node[x] = 1;
            node[i] = 1;
            next(++i);
        }
    }
}

bool UGragh::Judge()
{
    int x = 0;
    for (int i = 0; i < Max; i++)
        if (node[i] == 0)
            x++;
    if (edge == x - 1)
    {
        for (int i = 0; i < Max; i++)
            if (node[i] == 0)
                next(i);
        for (int i = 0; i < Max; i++)
        {
            if (node[i] == 0)
                return false;
        }
        return true;
    }
    else
        return false;
}

void UGragh::Floyd()
{
    int entrance, exit;
    cout << "请输入 入口和出口：";
    cin >> entrance >> exit;

    for (int i = 0; i < Max; i++)
        for (int j = 0; j < Max; j++)
            path[i][j] = -1;
    for (int k = 0; k < Max; k++)
        for (int i = 0; i < Max; i++)
            for (int j = 0; j < Max; j++)
            {
                if (gragh[i][j] > gragh[i][k] + gragh[k][j])
                {
                    gragh[i][j] = gragh[i][k] + gragh[k][j];
                    path[i][j] = k;
                }
            }
    cout << "最短路径长度为：" << gragh[entrance][exit] << endl;

    List.push_back(entrance);
    List.push_back(exit);
    search(entrance, path[entrance][exit], exit);
    cout << "最短路径为：";
    for (list<int>::iterator it = List.begin(); it != List.end(); it++)
        cout << "G[" << (*it) << "] -> ";
    cout << "NULL" << endl;
}

void UGragh::search(int entrance, int mid, int exit)
{
    list<int>::iterator m;
    for (list<int>::iterator it = List.begin(); it != List.end(); it++)
    {
        if (*it == entrance)
            m = ++it;
    }
    if (mid != -1)
    {
        List.insert(m, mid);
        search(entrance, path[entrance][mid], mid);
        search(mid, path[mid][exit], exit);
    }
}

int main()
{
    UGragh G;
    G.Create();
    G.print();
    cout << (G.Judge() ? "该图是树 " : "该图不是树 ") << endl;
    G.Floyd();

    system("pause");
}