#pragma once
#include"entrybank.h"


//¼�������ʵ��   ������ map �������ĵ����ȡ���ݣ������޷����������
void plugin()
{
	system("cls");
	int i = 0;
	cout << "��һ��Ҫ¼�뼸���⣿";
	cin >> i;
	while (i > 0)
	{
		cout << "���е������ţ�" << endl;
		codeput();
		cout << endl;
		question qus;             //���������
		qus.Question();
		qus.output();              //��Ϣ�����ĵ�
		i--;
	}

	cout << "�����³ɹ����������ز˵�����" << endl;
	system("pause");
	system("cls");
}



//�鿴����
void find()
{
	choice2:
	system("cls");
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;
	cout << "**********               *************" << endl;
	cout << "**********  1��ȫ������  *************" << endl;
	cout << "**********  2����������  *************" << endl;
	cout << "**********               *************" << endl;
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;

	string title, m_A, m_B, m_C, m_D, code;
	char answer = ' ';
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		fstream file("���.txt", ios::in);
		string str;
		while (getline(file,str))
		{
			file >> code;
			cout << code << "   ";
			file >> title;
			cout << title << "\n";
			file >> m_A;
			cout << "A.  " << m_A;
			file >> m_B;
			cout << "   B.  " << m_B << endl;
			file >> m_C;
			cout << "C.  " << m_C;
			file >> m_D;
			cout << "   D.  " << m_D << endl;
			file >> answer;
			cout << "�𰸣�" << answer;
			cout << "\n\n";
		}
	}

	if (i == 2)     //����map���������������ñ�Ų���
	{
		cout << "����ı���У�" << endl;
		codeput();
		cout << "\n�����������ҵ������ţ�";
		question qus;
		qus.m_map();
	}
	cout << "�Ƿ�����鿴��   1����   2����";
	int j = 0;
	while (1)
	{
		cin >> j;
		if (j == 1)
			goto choice2;
		if (j == 2)
		{
			cout << "�����������˵�����" << endl;
			system("pause");
			system("cls");
			break;
		}
		else
			cout << "������������������";
	}
}



//ɾ������
void modification()
{
	system("cls");
	cout << "��ֱ���޸���Ҫ�޸ĵ�����(ע�Ᵽ��,ע�⽫һ����ȫɾ��)" << endl;
	system("start \"\" \"C:\\����\\����ѡ�����׼������ϵͳ\\���.txt\"");
	system("pause");
	cout << "���ٴ��޸ı�ż���(ע�Ᵽ�棬ע�⽫һ����ȫɾ��)" << endl;
	system("start \"\" \"C:\\����\\����ѡ�����׼������ϵͳ\\��ż���.txt\"");
	cout << "�����������˵�����" << endl;
	system("pause");
	system("cls");
}


//����ඣ�
void examine()
{
	system("cls");
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;
	cout << "**********               *************" << endl;
	cout << "**********  1��ѡ������  *************" << endl;
	cout << "**********  2���������  *************" << endl;
	cout << "**********               *************" << endl;
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;

	int cho = 0;
	question qus;
	cout << "��ѡ��" << endl;
	cin >> cho;
	if (cho == 1)
		qus.choose();
	if (cho == 2)
		random();
}