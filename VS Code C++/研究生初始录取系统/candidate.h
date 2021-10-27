#pragma once
#include<fstream>
#include"pass.h"
using namespace std;

class candidate        //输入：考生姓名，准考证号，报考专业，是否应届生，4门课程（政治、数学、外语、专业基础课）成绩。
{
public:
	candidate() {}
	void input(string name, string code, string profession, string current, int Politic, int Math, int English, int Pro,int sum);
	void call(candidate& can);
private:
	string name, code, profession, current;            //code变量要求可以有字母，应使用string类型,，强烈建议初始化。。。
	int Politic = 0, Math = 0, English = 0, Pro = 0;
	int sum = 0;
};

//打印信息
void print()
{
	cout << "姓名" << setw(10) << "准考证号" << setw(10) << "专业" << setw(10) << "是否应届" << setw(10) 
		<< "政治" << setw(10) << "数学" << setw(10) << "英语" << setw(10) << "专业分" << setw(10) << "总分" << setw(10)<<endl;
	fstream file;
	file.open("考生信息.txt", ios::in);
	string buf;
	while (getline(file, buf)) {
		cout << buf << endl;
	}
}

//输入信息
void candidate::call(candidate & can)
{
	candidate* network;
	network = new candidate[20];
	int choice = 1;
	int i = 0;
	while (1) {
		cout << "请输入考生姓名：";
		cin >> can.name;
		cout << "\n请输入准考证号：";
		cin >> can.code;
		cout << "\n请输入报考专业：";
		cin >> can.profession;
		cout << "\n是否是应届生：";
		cin >> can.current;
		cout << "请依次输入政治、数学、外语以及专业课的成绩：";
		cin >> can.Politic >> can.Math >> can.English >> can.Pro;
		can.sum = can.Politic + can.Math + can.English + can.Pro;
		network[i].input(can.name, can.code, can.profession, can.current, can.Politic, can.Math, can.English, can.Pro,can.sum);

		//控制循环是否继续
		cout << "是否继续输入？(每次最多输入30个学生信息)：1、是   2、否" << endl;
		cin >> choice;
		i++;
		system("cls");
		if (choice == 2)
			break;
	}
}

//考生信息存入文档
void candidate::input(string name, string code, string profession, string current, int Politic, int Math, int English, int Pro,int sum)
{
		ofstream file;                                //创建文件，录入信息
		file.open("考生信息.txt", ios::app);
		file << "\n" << name << setw(10);
		file << code << setw(10);
		file << profession << setw(8);
		file << current << setw(10);
		file << Politic << setw(10)
			<< Math << setw(10)
			<< English << setw(10)
			<< Pro << setw(10)
			<< sum;
}


//判断并输出
void output()
{
	int m_sum, P_line, M_line, E_line, Pro_line;
	string name, code, profession, current;
	int politic, math, english, pro, sum;
	cout << "请输入被录取的最低分数线" << endl;
	cout << "政治：";
	cin >> P_line;
	cout << "\n数学：";
	cin >> M_line;
	cout << "\n英语：";
	cin >> E_line;
	cout << "\n专业：";
	cin >> Pro_line;
	cout << "\n总分：";
	cin >> m_sum;

	fstream is("考生信息.txt",  ios::in);
	pass a;
	string buf;
	while (getline(is,buf))
	{
		is >> name;
		a.name = name;
		is >> code;
		a.code = code;
		is >> profession;
		a.profession = profession;
		is >> current;
		a.current = current;
		is >> politic;
		a.politic = politic;
		is >> math;
		a.math = math;
		is >> english;
		a.english = english;
		is >> pro;
		a.pro = pro;
		is >> sum;
		a.sum = sum;
		if (a.judge(P_line, M_line, E_line, Pro_line, m_sum))
			a.infile2();
		else {
			a.infile3();
		}
	}
}
