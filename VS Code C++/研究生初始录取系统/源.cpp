#include"candidate.h"
using namespace std;


void see1()
{
	fstream file("���߿���.txt", ios::in);
	string buf;
	while (getline(file,buf)) {
		cout << buf << endl;
	}
	cout << endl;
}

void see2()
{
	fstream file("δ���߿���.txt", ios::in);
	string buf;
	while (getline(file, buf)) {
		cout << buf << endl;
	}
	cout << endl;
}


int main() {
	cout << "��ӭʹ���о���¼ȡϵͳ������������Ϣ:" << endl;
	cout << "�Ƿ�Ҫ���뿼����Ϣ��  1����    2����";
	int i = 0, j = 1;
	cin >> i;
	if (i == 1) {
		candidate can;
		can.call(can);
	}
	print();
	fstream file02("���߿���.txt", ios::trunc | ios::out);
	file02.close();
	fstream file03("δ���߿���.txt", ios::trunc | ios::out);
	file03.close();
	output();
	while (j == 1) {
		cout << "��������Ҫ�鿴���ļ���1�����߿���   2��δ���߿���" << endl;
		cin >> i;
		if (i == 1)
			see1();
		if (i == 2)
			see2();
		cout << "�Ƿ�����鿴��   1����    2����";
		cin >> j;
		system("cls");
	}
	return 0;
}
