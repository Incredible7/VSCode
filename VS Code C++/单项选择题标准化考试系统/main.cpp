#include"realize.h"

void plugin();  //录入
void find();      //查看

int main() {
	menu:
	//界面的简单实现
	cout << "**************************************" << endl;
	cout << "*****欢迎使用单项选择题考试系统!******" << endl;
	cout << "**********  φ(>ω<*)    *************" << endl;
	cout << "**********  1、录入试题  *************" << endl;
	cout << "**********  2、查看试题  *************" << endl;
	cout << "**********  3、修改试题  *************" << endl;
	cout << "**********  4、开始考试  *************" << endl;
	cout << "**********  5、退出系统  *************" << endl;
	cout << "**********     Fight！   *************" << endl;
	cout << "**************************************" << endl;
	
    Tchoice:
	cout << "请选择：";
	int choice = 0; 
	cin >> choice;
	switch (choice)
	{
	case 1:                 //录入试题部分完成
		plugin();
		goto menu;
	case 2:
		find();
		goto menu;     //查找试题部分完成
	case 3:
		modification();
		goto menu;
	case 4:
		examine();
		goto menu;
	case 5:
		cout << "感谢您的使用！请多多支持哦！(￣▽￣)~*";
		return 0;
	default:
		cout << "输入有误！请重新输入";
		goto Tchoice;
	}
}