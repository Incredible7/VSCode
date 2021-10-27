#include "GrandList.h"

int main()
{
    GrandList L;
First:
    cout << "-----欢迎使用研究生导师制查询系统!----" << endl;
    cout << "------      1、添加人员         ------" << endl;
    cout << "------      2、删除人员         ------" << endl;
    cout << "------      3、查询人员         ------" << endl;
    cout << "------      4、人员总览         ------" << endl;
    cout << "------       感谢支持!          ------" << endl;
    int i = 0, x = -1;
    string str;
    cin >> i;
    system("cls");
    switch (i)
    {
    case 1:
        cout << "------      1、添加导师         ------" << endl;
        cout << "------      2、添加研究生       ------" << endl;
        cout << "------      3、添加本科生       ------" << endl;
        while (x < 1 || x > 3)
            cin >> x;
        if (x == 1)
            L.TutorIN();
        else if (x == 2)
            L.GraduIN();
        else
            L.UnderIN();
        system("pause");

        system("cls");
        goto First;
    case 2:
        cout << "------      1、删除研究生       ------" << endl;
        cout << "------      2、删除本科生       ------" << endl;
        while (x < 1 || x > 2)
            cin >> x;
        cout << "输入要删除的人员姓名：";
        cin >> str;
        if (x == 1)
            if (L.GraduDE(str))
                cout << "删除成功！" << endl;
            else
                cout << "删除失败！" << endl;
        else if (L.UnderDE(str))
            cout << "删除成功！" << endl;
        else
            cout << "删除失败！" << endl;
        system("pause");
        system("cls");
        goto First;
    case 3:
        cout << "------      1、查询导师         ------" << endl;
        cout << "------      2、查询研究生       ------" << endl;
        cout << "------      3、查询本科生       ------" << endl;
        while (x < 1 || x > 3)
            cin >> x;
        if (x == 1)
        {
            cout << "输入导师姓名：";
            cin >> str;
            List *r = L.SearchT(str);
            if (r != NULL)
            {
                cout << "导师名称：" << r->name << " 导师职称：" << r->state << "，所带研究生为：";
                r = r->nextlevel;
                while (r != NULL)
                {
                    cout << r->name << "、";
                    r = r->next;
                }
                cout << endl;
            }
        }

        if (x == 2)
        {
            cout << "输入研究生姓名：";
            cin >> str;
            List *r = L.SearchG(str);
            if (r != NULL)
            {
                cout << "研究生姓名：" << r->name << " 研究生班级：" << r->state
                     << "\n直属导师：" << r->up->name << " 所带本科生有：";
                r = r->nextlevel;
                while (r != NULL)
                {
                    cout << r->name << "、";
                    r = r->next;
                }
                cout << endl;
            }
        }

        if (x == 3)
        {
            cout << "请输入本科生姓名：";
            cin >> str;
            List *r = L.SearchU(str);
            if (r != NULL)
            {
                cout << "本科生姓名：" << r->name << " 本科生班级：" << r->state
                     << "\n直属于" << (r->up->level == 1 ? "导师：" : "研究生：") << r->up->name << endl;
            }
        }
        system("pause");
        system("cls");
        goto First;
    case 4:
        L.Output();

        system("pause");
        system("cls");
        goto First;
    };
    system("pause");
}