#include <iostream>
#include <string>
using namespace std;

struct List
{
    int level;
    string name;
    string state;
    int judge;
    List* up;        //指代上级的指针
    List* next;      //指代同属的next指针
    List* nextlevel; //指代下级的next指针
    List* Next;      //指代同级的next指针
};

class GrandList
{
public:
    GrandList()
    {
        ListIN(L1);
        ListIN(L2);
        ListIN(L3);
    }
    void ListIN(List*& L)
    {
        L = new List;
        L->level = 0;
        L->name = ' ';
        L->next = NULL;
        L->nextlevel = NULL;
        L->Next = NULL;
        L->up = NULL;
    }
    void TutorIN();
    void GraduIN();
    void UnderIN();
    bool GraduDE(string str);
    bool UnderDE(string str);
    List* SearchT(string str);
    List* SearchG(string str);
    List* SearchU(string str);
    void Output();

private:
    List* L1; //导师
    List* L2; //研究生
    List* L3; //本科生
};

List* GrandList::SearchT(string str)
{
    List* r1 = L1;
    while (r1->name != str)
    {
        r1 = r1->Next;
        if (r1 == NULL)
        {
            cout << "查无此人！" << endl;
            return NULL;
        }
    }
    return r1;
}

List* GrandList::SearchG(string str)
{
    List* r2 = L2;
    while (r2->name != str)
    {
        r2 = r2->Next;
        if (r2 == NULL)
        {
            cout << "查无此人！" << endl;
            return NULL;
        }
    }
    return r2;
}

List* GrandList::SearchU(string str)
{
    List* r3 = L3;
    while (r3->name != str)
    {
        r3 = r3->Next;
        if (r3 == NULL)
        {
            cout << "查无此人！" << endl;
            return NULL;
        }
    }
    return r3;
}

void GrandList::TutorIN()
{
    List* p = new List;
    p->level = 1;
    p->up = NULL;
    p->nextlevel = NULL;
    p->next = NULL;
    p->Next = NULL;
    cout << "请输入导师姓名：";
    cin >> p->name;
    cout << "请输入导师职称：";
    cin >> p->state;
    cout << "导师是否带研究生？ 1、是  0、否";
    cin >> p->judge;
    while (p->judge != 1 && p->judge != 0)
    {
        cout << "\n输入有误！请重新输入：";
        cin >> p->judge;
    }
    p->Next = L1->Next;
    L1->Next = p;
    cout << "已录入！" << endl;
}

void GrandList::GraduIN()
{
    List* r1 = L1->Next;
    List* p = new List;
    p->up = NULL;
    p->nextlevel = NULL;
    p->next = NULL;
    p->Next = NULL;
    p->level = 2;
    string str;
    cout << "请输入研究生姓名：";
    cin >> p->name;
    cout << "请输入研究生班级：";
    cin >> p->state;
    cout << "请输入" << p->name << "所属导师：";
    cin >> str;
    r1 = SearchT(str);
    if (r1 == NULL)
        return;
    if (!r1->judge)
    {
        cout << "该导师不带研究生！" << endl;
        r1->nextlevel = NULL;
        return;
    }

    p->Next = L2->Next;
    L2->Next = p;
    if (r1->nextlevel == NULL)
    {
        p->nextlevel = r1->nextlevel;
        r1->nextlevel = p;
        p->up = r1;
    }
    else
    {
        p->next = r1->nextlevel->next;
        p->up = r1;
        r1->nextlevel->next = p;
    }
    cout << "已录入！" << endl;
}

void GrandList::UnderIN()
{
    int judge;
    string str;
    List* r1 = L1->Next;
    List* r2 = L2->Next;
    List* p = new List;
    p->up = NULL;
    p->nextlevel = NULL;
    p->next = NULL;
    p->Next = NULL;
    p->level = 3;
    cout << "请输入本科生姓名：";
    cin >> p->name;
    cout << "请输入本科生班级：";
    cin >> p->state;
    cout << p->name << "直属于导师还是研究生？ 1、导师  2、研究生：";
    cin >> judge;
    while (judge != 1 && judge != 2)
    {
        cout << "输入有误！请重新输入：";
        cin >> judge;
    }
    cout << "请输入直属人员姓名：";
    cin >> str;

    if (judge == 1)
    {
        r1 = SearchT(str);
        if (r1 == NULL)
            return;
        p->Next = L3->Next;
        L3->Next = p;
        if (r1->nextlevel == NULL)
        {
            p->nextlevel = r1->nextlevel;
            r1->nextlevel = p;
            p->up = r1;
        }
        else
        {
            p->next = r1->nextlevel->next;
            p->up = r1;
            r1->nextlevel->next = p;
        }
        cout << "已录入！" << endl;
    }

    if (judge == 2)
    {
        r2 = SearchG(str);
        if (r2 == NULL)
            return;
        p->Next = L3->Next;
        L3->Next = p;
        if (r2->nextlevel == NULL)
        {
            p->nextlevel = r2->nextlevel;
            r2->nextlevel = p;
            p->up = r2;
        }
        else
        {
            p->next = r2->nextlevel->next;
            p->up = r2;
            r2->nextlevel->next = p;
        }
        cout << "已录入！" << endl;
    }
}

bool GrandList::GraduDE(string str)
{
    List* r2 = L2;
    r2->Next = SearchG(str);
    if (r2->Next == NULL)
        return false;
    while (r2->Next->nextlevel != NULL)
    {
        UnderDE(r2->Next->nextlevel->name);
    }
    if (r2->Next->up != NULL)
        r2->Next->up->nextlevel = r2->Next->next;
    r2->Next = r2->Next->Next;
    return true;
}

bool GrandList::UnderDE(string str)
{
    List* r3 = L3;
    r3->Next = SearchU(str);
    if (r3->Next == NULL)
        return false;
    if (r3->Next->up != NULL)
        r3->Next->up->nextlevel = r3->Next->next;
    r3->Next = r3->Next->Next;
    return true;
}


void GrandList::Output()
{
    List* r1 = L1->Next;
    while(r1!=NULL)
    {
        cout<<r1->name<<"（";
        while(r1->nextlevel!=NULL)
        {
            cout<<r1->nextlevel->name<<"（";
            while(r1->nextlevel->nextlevel!=NULL)
            {
                cout<<r1->nextlevel->nextlevel->name<<" ";
                r1->nextlevel->nextlevel = r1->nextlevel->nextlevel->next;
            }
            cout<<"）";
            r1->nextlevel = r1->nextlevel->next;
        }
        cout<<"）";
        r1 = r1->Next;
    }
}