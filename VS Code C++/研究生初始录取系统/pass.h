#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class pass
{
public:
	string name, code, profession, current;
	int politic, math, english, pro, sum;

	bool judge(int P_line, int M_line, int E_line, int Pro_line, int m_sum);
	void infile2();
	void infile3();
};

bool pass::judge(int P_line, int M_line, int E_line, int Pro_line, int m_sum)
{
	if (politic >= P_line
		&& math >= M_line
		&& english >= E_line
		&& pro >= Pro_line
		&& sum >= m_sum)
		return 1;
	else {
		return 0;
	}
}

void pass::infile2()
{
	ofstream out;//文件输出流对象，用于写文件
	out.open("过线考生.txt", ios::app);//打开文件，每次写入前寻位到流结尾
	out << "姓名：" << name;
	out << "  准考证号：" << code;
	out << "  专业：" << profession;
	out << "  是否应届生：" << current;
	out << "  政治：" << politic;
	out << "  数学：" << math;
	out << "  英语：" << english;
	out << "  专业：" << pro;
	out << "  总分：" << sum << endl;
	out.close();
}


void pass::infile3()
{
	ofstream out;//文件输出流对象，用于写文件
	out.open("未过线考生.txt", ios::app);//打开文件，每次写入前寻位到流结尾
	out << "姓名：" << name;
	out << "  准考证号：" << code;
	out << "  专业：" << profession;
	out << "  是否应届生：" << current;
	out << "  政治：" << politic;
	out << "  数学：" << math;
	out << "  英语：" << english;
	out << "  专业：" << pro;
	out << "  总分：" << sum << endl;
	out.close();
}