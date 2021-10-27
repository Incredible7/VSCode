#pragma once
#include<iostream>
#include<fstream>
#include<windows.h>
#include<map>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<string>
using namespace std;


//����һ�������
class question
{
public:
	void Question();
	void input(string code ,string title , string m_A, string m_B, string m_C, string m_D, char answer);
	void show();
	void show1();
	void output();
	void m_map();
	void choose();
	friend void plugin();
private:
	string title, m_A, m_B, m_C, m_D, code;
	char answer = '0';
};


//������Ϣ
void question::Question()
{
	cout << "�������Ҫ��ӵ�������Ŀ" << endl;
	fstream file("��ż���.txt", ios::in);
	string code1;
	cout << "��Ŀ��ţ�";
	vector<string> vec;      //����vector��������ű��
	while (!file.eof())
	{
		file >> code1;
		vec.push_back(code1);
	}
	while (cin>>code)
	{
		int i = 1;
		for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			if (code == *it)
			{
				cout << "�������ظ������������룺";
				i = 0;
				break;
			}
		}
		if (i)
			break;
	}
	cout << "��Ŀ��";
	cin >> title;
	cout << "���������������ѡ��" << endl;
	cout << "A��";
	cin >> m_A;
	cout << "B��";
	cin >> m_B;
	cout << "C��";
	cin >> m_C;
	cout << "D��";
	cin >> m_D;
	cout << "������𰸣�";
	cin >> answer;
}


//����Ϣ�����ĵ��������Ŵ��������ĵ���
void question::output()
{
	cout << "�������ڱ����С���" << endl;

	fstream output("���.txt", ios::app);
	if (!output.is_open())
		cout << "�ļ�δ�򿪻��ļ����𻵣�" << endl;
	output << "\n" << this->code << "\t"
		<< this->title << "\t"
		<< this->m_A << "\t"
		<< this->m_B << "\t"
		<< this->m_C << "\t"
		<< this->m_D << "\t"
		<< this->answer;

	fstream output1("��ż���.txt", ios::app);
	if (!output.is_open())
		cout << "�ļ�δ�򿪻��ļ����𻵣�" << endl;
	output1 << "\n"<< code << "\t"<< answer;

	cout << "�����ѱ��棡" << endl;
}


//��ĸ�ֵ
void question::input(string code, string title, string m_A, string m_B, string m_C, string m_D, char answer)
{
	this->code = code;
	this->title = title;
	this->m_A = m_A;
	this->m_B = m_B;
	this->m_C = m_C;
	this->m_D = m_D;
	this->answer = answer;	
}


//չʾ��Ϣ
void question::show()
{
	cout << "��ţ�" << code << endl;
	cout << title << endl;
	cout << "A.   " << m_A << endl;
	cout << "B.   " << m_B << endl;
	cout << "C.   " << m_C << endl;
	cout << "D.   " << m_D << endl;
	cout << "�𰸣�" << answer << "\n\n";
}



void question::show1()
{
	cout << "��Ŀ��" << title << endl;
	cout << "A.   " << m_A << endl;
	cout << "B.   " << m_B << endl;
	cout << "C.   " << m_C << endl;
	cout << "D.   " << m_D << endl;
}



//map�����ĸ��²����
void question::m_map()
{
	map<string, question> map1;
	map<string, char> map2;
	question *qus1;
	qus1 = new question[500];
	string title, m_A, m_B, m_C, m_D, code;
	char answer;
	fstream file("���.txt", ios::in);
	int i = 0;
	while (!file.eof())
	{
		file >> code;
		file >> title;
		file >> m_A;
		file >> m_B;
		file >> m_C;
		file >> m_D;
		file >> answer;
		qus1->input(code, title, m_A, m_B, m_C, m_D, answer);
		map1.insert(make_pair(code, *qus1));
		map2.insert(make_pair(code, answer));
	}
	string code1; 
	cin >> code1;
	map<string, question> ::iterator pos = map1.find(code1);
	if (pos != map1.end())
	{
		(*pos).second.show();
	}
	else
	{
		cout << "δ�ҵ�����" << endl;
	}
}




//��ʾ���
void codeput()
{
	fstream file("��ż���.txt", ios::in);
	string str;
	while (!file.eof())
	{  
		file >> str;
		cout << str << "        ";
		getline(file, str);
	}
}


//ѡ������
void question::choose()
{
	question qus;
	cout << "��һ��Ҫѡ�񼸵��⣿" << endl;
	int num, num1;
	cin >> num;
	num1 = num;
	map<string, question> map1;
	map<string, char> map2;
	question* qus1;
	qus1 = new question[500];
	string title, m_A, m_B, m_C, m_D, code;
	char answer, ch[100];
	fstream file("���.txt", ios::in);
	int i = 0;
	while (!file.eof())
	{
		file >> code;
		file >> title;
		file >> m_A;
		file >> m_B;
		file >> m_C;
		file >> m_D;
		file >> answer;
		qus1->input(code, title, m_A, m_B, m_C, m_D, answer);
		map1.insert(make_pair(code, *qus1));
		map2.insert(make_pair(code, answer));
	}
	system("cls");
	
	cout << "���еı��Ϊ��" << endl;
	codeput();
	cout << "��ѡ��(��������ı���򲻻��з�Ӧ�����������)��" << endl;
	string str;
	while (num > 0)
	{
		cout << "��ţ�";
		cin >> str;
		for (map<string, question>::iterator pos = map1.begin(); pos != map1.end(); pos++)
		{
			if ((*pos).first == str)
			{
				(*pos).second.show1();
				cout << "\n";
				num--;
			}
		}
	}
	cout << "\n\n׼����ʼ����!" << endl;
	for (int i = 3; i > 0; i--)
	{
		cout << i << "��";
		Sleep(1000);
		cout << "\r";
	}

	cout << "����������𰸣�" << endl;
	for (int i = 0; i < num1; i++)
	{
		cout << i + 1 << "��";
		cin >> ch[i];
		cout << endl;
	}
	while (1)
	{
		int m, n;
		char ch1;
		cout << "������ϣ��Ƿ���Ĵ𰸣�   1����    2����";
		cin >> m;
		if (m == 1)
		{
			cout << "��Ҫ�޸ĵڼ����𰸣�" << endl;
			cin >> n;
			if (n > num1||n<=0)
			{
				cout << "��������\r" << endl;
				continue;
			}
			cout << "�޸�Ϊ��";
			cin >> ch1;
			ch[n - 1] = ch1;
		}
		if (m == 2)
			break;
	}

	system("pause");
}



//�������
void random()
{
	 
}