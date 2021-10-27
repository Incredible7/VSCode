#include"candidate.h"
using namespace std;


void see1()
{
	fstream file("过线考生.txt", ios::in);
	string buf;
	while (getline(file,buf)) {
		cout << buf << endl;
	}
	cout << endl;
}

void see2()
{
	fstream file("未过线考生.txt", ios::in);
	string buf;
	while (getline(file, buf)) {
		cout << buf << endl;
	}
	cout << endl;
}


int main() {
	cout << "欢迎使用研究生录取系统！请您键入信息:" << endl;
	cout << "是否要输入考生信息？  1、是    2、否";
	int i = 0, j = 1;
	cin >> i;
	if (i == 1) {
		candidate can;
		can.call(can);
	}
	print();
	fstream file02("过线考生.txt", ios::trunc | ios::out);
	file02.close();
	fstream file03("未过线考生.txt", ios::trunc | ios::out);
	file03.close();
	output();
	while (j == 1) {
		cout << "请输入您要查看的文件：1、过线考生   2、未过线考生" << endl;
		cin >> i;
		if (i == 1)
			see1();
		if (i == 2)
			see2();
		cout << "是否继续查看？   1、是    2、否";
		cin >> j;
		system("cls");
	}
	return 0;
}
