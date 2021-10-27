#pragma once
#include"entrybank.h"


//录入试题的实现   必须让 map 容器从文档里读取数据，否则无法保存旧数据
void plugin()
{
	system("cls");
	int i = 0;
	cout << "您一共要录入几道题？";
	cin >> i;
	while (i > 0)
	{
		cout << "已有的试题编号：" << endl;
		codeput();
		cout << endl;
		question qus;             //创建类对象
		qus.Question();
		qus.output();              //信息存入文档
		i--;
	}

	cout << "题库更新成功！即将返回菜单界面" << endl;
	system("pause");
	system("cls");
}



//查看函数
void find()
{
	choice2:
	system("cls");
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;
	cout << "**********               *************" << endl;
	cout << "**********  1、全部试题  *************" << endl;
	cout << "**********  2、查找试题  *************" << endl;
	cout << "**********               *************" << endl;
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;

	string title, m_A, m_B, m_C, m_D, code;
	char answer = ' ';
	int i = 0;
	cin >> i;
	if (i == 1)
	{
		fstream file("题库.txt", ios::in);
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
			cout << "答案：" << answer;
			cout << "\n\n";
		}
	}

	if (i == 2)     //利用map容器做到快速利用编号查找
	{
		cout << "试题的编号有：" << endl;
		codeput();
		cout << "\n请输入所查找的试题编号：";
		question qus;
		qus.m_map();
	}
	cout << "是否继续查看？   1、是   2、否";
	int j = 0;
	while (1)
	{
		cin >> j;
		if (j == 1)
			goto choice2;
		if (j == 2)
		{
			cout << "即将返回主菜单……" << endl;
			system("pause");
			system("cls");
			break;
		}
		else
			cout << "输入有误！请重新输入";
	}
}



//删除试题
void modification()
{
	system("cls");
	cout << "请直接修改您要修改的试题(注意保存,注意将一行完全删除)" << endl;
	system("start \"\" \"C:\\工程\\单项选择题标准化考试系统\\题库.txt\"");
	system("pause");
	cout << "请再次修改编号及答案(注意保存，注意将一行完全删除)" << endl;
	system("start \"\" \"C:\\工程\\单项选择题标准化考试系统\\编号及答案.txt\"");
	cout << "即将返回主菜单……" << endl;
	system("pause");
	system("cls");
}


//考试喽！
void examine()
{
	system("cls");
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;
	cout << "**********               *************" << endl;
	cout << "**********  1、选择试题  *************" << endl;
	cout << "**********  2、随机试题  *************" << endl;
	cout << "**********               *************" << endl;
	cout << "**************************************" << endl;
	cout << "**************************************" << endl;

	int cho = 0;
	question qus;
	cout << "请选择：" << endl;
	cin >> cho;
	if (cho == 1)
		qus.choose();
	if (cho == 2)
		random();
}