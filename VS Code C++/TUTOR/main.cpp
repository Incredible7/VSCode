#include "GrandList.h"

int main()
{
    GrandList L;
First:
    cout << "-----��ӭʹ���о�����ʦ�Ʋ�ѯϵͳ!----" << endl;
    cout << "------      1�������Ա         ------" << endl;
    cout << "------      2��ɾ����Ա         ------" << endl;
    cout << "------      3����ѯ��Ա         ------" << endl;
    cout << "------      4����Ա����         ------" << endl;
    cout << "------       ��л֧��!          ------" << endl;
    int i = 0, x = -1;
    string str;
    cin >> i;
    system("cls");
    switch (i)
    {
    case 1:
        cout << "------      1����ӵ�ʦ         ------" << endl;
        cout << "------      2������о���       ------" << endl;
        cout << "------      3����ӱ�����       ------" << endl;
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
        cout << "------      1��ɾ���о���       ------" << endl;
        cout << "------      2��ɾ��������       ------" << endl;
        while (x < 1 || x > 2)
            cin >> x;
        cout << "����Ҫɾ������Ա������";
        cin >> str;
        if (x == 1)
            if (L.GraduDE(str))
                cout << "ɾ���ɹ���" << endl;
            else
                cout << "ɾ��ʧ�ܣ�" << endl;
        else if (L.UnderDE(str))
            cout << "ɾ���ɹ���" << endl;
        else
            cout << "ɾ��ʧ�ܣ�" << endl;
        system("pause");
        system("cls");
        goto First;
    case 3:
        cout << "------      1����ѯ��ʦ         ------" << endl;
        cout << "------      2����ѯ�о���       ------" << endl;
        cout << "------      3����ѯ������       ------" << endl;
        while (x < 1 || x > 3)
            cin >> x;
        if (x == 1)
        {
            cout << "���뵼ʦ������";
            cin >> str;
            List *r = L.SearchT(str);
            if (r != NULL)
            {
                cout << "��ʦ���ƣ�" << r->name << " ��ʦְ�ƣ�" << r->state << "�������о���Ϊ��";
                r = r->nextlevel;
                while (r != NULL)
                {
                    cout << r->name << "��";
                    r = r->next;
                }
                cout << endl;
            }
        }

        if (x == 2)
        {
            cout << "�����о���������";
            cin >> str;
            List *r = L.SearchG(str);
            if (r != NULL)
            {
                cout << "�о���������" << r->name << " �о����༶��" << r->state
                     << "\nֱ����ʦ��" << r->up->name << " �����������У�";
                r = r->nextlevel;
                while (r != NULL)
                {
                    cout << r->name << "��";
                    r = r->next;
                }
                cout << endl;
            }
        }

        if (x == 3)
        {
            cout << "�����뱾����������";
            cin >> str;
            List *r = L.SearchU(str);
            if (r != NULL)
            {
                cout << "������������" << r->name << " �������༶��" << r->state
                     << "\nֱ����" << (r->up->level == 1 ? "��ʦ��" : "�о�����") << r->up->name << endl;
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