#include"realize.h"

void plugin();  //¼��
void find();      //�鿴

int main() {
	menu:
	//����ļ�ʵ��
	cout << "**************************************" << endl;
	cout << "*****��ӭʹ�õ���ѡ���⿼��ϵͳ!******" << endl;
	cout << "**********  ��(>��<*)    *************" << endl;
	cout << "**********  1��¼������  *************" << endl;
	cout << "**********  2���鿴����  *************" << endl;
	cout << "**********  3���޸�����  *************" << endl;
	cout << "**********  4����ʼ����  *************" << endl;
	cout << "**********  5���˳�ϵͳ  *************" << endl;
	cout << "**********     Fight��   *************" << endl;
	cout << "**************************************" << endl;
	
    Tchoice:
	cout << "��ѡ��";
	int choice = 0; 
	cin >> choice;
	switch (choice)
	{
	case 1:                 //¼�����ⲿ�����
		plugin();
		goto menu;
	case 2:
		find();
		goto menu;     //�������ⲿ�����
	case 3:
		modification();
		goto menu;
	case 4:
		examine();
		goto menu;
	case 5:
		cout << "��л����ʹ�ã�����֧��Ŷ��(������)~*";
		return 0;
	default:
		cout << "������������������";
		goto Tchoice;
	}
}