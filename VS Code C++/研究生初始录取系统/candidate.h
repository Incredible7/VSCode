#pragma once
#include<fstream>
#include"pass.h"
using namespace std;

class candidate        //���룺����������׼��֤�ţ�����רҵ���Ƿ�Ӧ������4�ſγ̣����Ρ���ѧ�����רҵ�����Σ��ɼ���
{
public:
	candidate() {}
	void input(string name, string code, string profession, string current, int Politic, int Math, int English, int Pro,int sum);
	void call(candidate& can);
private:
	string name, code, profession, current;            //code����Ҫ���������ĸ��Ӧʹ��string����,��ǿ�ҽ����ʼ��������
	int Politic = 0, Math = 0, English = 0, Pro = 0;
	int sum = 0;
};

//��ӡ��Ϣ
void print()
{
	cout << "����" << setw(10) << "׼��֤��" << setw(10) << "רҵ" << setw(10) << "�Ƿ�Ӧ��" << setw(10) 
		<< "����" << setw(10) << "��ѧ" << setw(10) << "Ӣ��" << setw(10) << "רҵ��" << setw(10) << "�ܷ�" << setw(10)<<endl;
	fstream file;
	file.open("������Ϣ.txt", ios::in);
	string buf;
	while (getline(file, buf)) {
		cout << buf << endl;
	}
}

//������Ϣ
void candidate::call(candidate & can)
{
	candidate* network;
	network = new candidate[20];
	int choice = 1;
	int i = 0;
	while (1) {
		cout << "�����뿼��������";
		cin >> can.name;
		cout << "\n������׼��֤�ţ�";
		cin >> can.code;
		cout << "\n�����뱨��רҵ��";
		cin >> can.profession;
		cout << "\n�Ƿ���Ӧ������";
		cin >> can.current;
		cout << "�������������Ρ���ѧ�������Լ�רҵ�εĳɼ���";
		cin >> can.Politic >> can.Math >> can.English >> can.Pro;
		can.sum = can.Politic + can.Math + can.English + can.Pro;
		network[i].input(can.name, can.code, can.profession, can.current, can.Politic, can.Math, can.English, can.Pro,can.sum);

		//����ѭ���Ƿ����
		cout << "�Ƿ�������룿(ÿ���������30��ѧ����Ϣ)��1����   2����" << endl;
		cin >> choice;
		i++;
		system("cls");
		if (choice == 2)
			break;
	}
}

//������Ϣ�����ĵ�
void candidate::input(string name, string code, string profession, string current, int Politic, int Math, int English, int Pro,int sum)
{
		ofstream file;                                //�����ļ���¼����Ϣ
		file.open("������Ϣ.txt", ios::app);
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


//�жϲ����
void output()
{
	int m_sum, P_line, M_line, E_line, Pro_line;
	string name, code, profession, current;
	int politic, math, english, pro, sum;
	cout << "�����뱻¼ȡ����ͷ�����" << endl;
	cout << "���Σ�";
	cin >> P_line;
	cout << "\n��ѧ��";
	cin >> M_line;
	cout << "\nӢ�";
	cin >> E_line;
	cout << "\nרҵ��";
	cin >> Pro_line;
	cout << "\n�ܷ֣�";
	cin >> m_sum;

	fstream is("������Ϣ.txt",  ios::in);
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
