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


//构建一个题库类
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


//键入信息
void question::Question()
{
	cout << "请键入您要添加的试题题目" << endl;
	fstream file("编号及答案.txt", ios::in);
	string code1;
	cout << "题目编号：";
	vector<string> vec;      //创建vector容器来存放编号
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
				cout << "输入编号重复！请重新输入：";
				i = 0;
				break;
			}
		}
		if (i)
			break;
	}
	cout << "题目：";
	cin >> title;
	cout << "接下来请输入各个选项" << endl;
	cout << "A：";
	cin >> m_A;
	cout << "B：";
	cin >> m_B;
	cout << "C：";
	cin >> m_C;
	cout << "D：";
	cin >> m_D;
	cout << "请输入答案：";
	cin >> answer;
}


//将信息存入文档，试题编号存入两个文档中
void question::output()
{
	cout << "试题正在保存中……" << endl;

	fstream output("题库.txt", ios::app);
	if (!output.is_open())
		cout << "文件未打开或文件已损坏！" << endl;
	output << "\n" << this->code << "\t"
		<< this->title << "\t"
		<< this->m_A << "\t"
		<< this->m_B << "\t"
		<< this->m_C << "\t"
		<< this->m_D << "\t"
		<< this->answer;

	fstream output1("编号及答案.txt", ios::app);
	if (!output.is_open())
		cout << "文件未打开或文件已损坏！" << endl;
	output1 << "\n"<< code << "\t"<< answer;

	cout << "试题已保存！" << endl;
}


//类的赋值
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


//展示信息
void question::show()
{
	cout << "编号：" << code << endl;
	cout << title << endl;
	cout << "A.   " << m_A << endl;
	cout << "B.   " << m_B << endl;
	cout << "C.   " << m_C << endl;
	cout << "D.   " << m_D << endl;
	cout << "答案：" << answer << "\n\n";
}



void question::show1()
{
	cout << "题目：" << title << endl;
	cout << "A.   " << m_A << endl;
	cout << "B.   " << m_B << endl;
	cout << "C.   " << m_C << endl;
	cout << "D.   " << m_D << endl;
}



//map容器的更新并输出
void question::m_map()
{
	map<string, question> map1;
	map<string, char> map2;
	question *qus1;
	qus1 = new question[500];
	string title, m_A, m_B, m_C, m_D, code;
	char answer;
	fstream file("题库.txt", ios::in);
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
		cout << "未找到试题" << endl;
	}
}




//显示编号
void codeput()
{
	fstream file("编号及答案.txt", ios::in);
	string str;
	while (!file.eof())
	{  
		file >> str;
		cout << str << "        ";
		getline(file, str);
	}
}


//选择试题
void question::choose()
{
	question qus;
	cout << "您一共要选择几道题？" << endl;
	int num, num1;
	cin >> num;
	num1 = num;
	map<string, question> map1;
	map<string, char> map2;
	question* qus1;
	qus1 = new question[500];
	string title, m_A, m_B, m_C, m_D, code;
	char answer, ch[100];
	fstream file("题库.txt", ios::in);
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
	
	cout << "已有的编号为：" << endl;
	codeput();
	cout << "请选择(若无输入的编号则不会有反应，请继续输入)：" << endl;
	string str;
	while (num > 0)
	{
		cout << "编号：";
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
	cout << "\n\n准备开始考试!" << endl;
	for (int i = 3; i > 0; i--)
	{
		cout << i << "！";
		Sleep(1000);
		cout << "\r";
	}

	cout << "请依次输入答案：" << endl;
	for (int i = 0; i < num1; i++)
	{
		cout << i + 1 << "、";
		cin >> ch[i];
		cout << endl;
	}
	while (1)
	{
		int m, n;
		char ch1;
		cout << "作答完毕，是否更改答案？   1、是    2、否";
		cin >> m;
		if (m == 1)
		{
			cout << "需要修改第几个答案：" << endl;
			cin >> n;
			if (n > num1||n<=0)
			{
				cout << "输入有误！\r" << endl;
				continue;
			}
			cout << "修改为：";
			cin >> ch1;
			ch[n - 1] = ch1;
		}
		if (m == 2)
			break;
	}

	system("pause");
}



//随机试题
void random()
{
	 
}