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
	ofstream out;//�ļ��������������д�ļ�
	out.open("���߿���.txt", ios::app);//���ļ���ÿ��д��ǰѰλ������β
	out << "������" << name;
	out << "  ׼��֤�ţ�" << code;
	out << "  רҵ��" << profession;
	out << "  �Ƿ�Ӧ������" << current;
	out << "  ���Σ�" << politic;
	out << "  ��ѧ��" << math;
	out << "  Ӣ�" << english;
	out << "  רҵ��" << pro;
	out << "  �ܷ֣�" << sum << endl;
	out.close();
}


void pass::infile3()
{
	ofstream out;//�ļ��������������д�ļ�
	out.open("δ���߿���.txt", ios::app);//���ļ���ÿ��д��ǰѰλ������β
	out << "������" << name;
	out << "  ׼��֤�ţ�" << code;
	out << "  רҵ��" << profession;
	out << "  �Ƿ�Ӧ������" << current;
	out << "  ���Σ�" << politic;
	out << "  ��ѧ��" << math;
	out << "  Ӣ�" << english;
	out << "  רҵ��" << pro;
	out << "  �ܷ֣�" << sum << endl;
	out.close();
}