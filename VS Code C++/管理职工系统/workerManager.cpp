#include"workerManager.h"
#include"worker.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if ( ! ifs.is_open()) {
		cout << "文件不存在！" << endl;
		this->m_EmpNum = 0;        //初始化人数
		this->m_FileIsEmpty = 1;     //初始化文件为空标志
		this->m_EmpArray = NULL;     //初始化数组
		ifs.close();
		return;
	}

	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//统计人数
	int num = this->get_EmpNum();
	cout << "职工个数为：" << num << endl;   //测试代码
	this->m_EmpNum = num;     //更新成员属性

	//根据职工数创建数组
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//初始化员工
	init_Emp();
	//测试代码
	for (int i = 0; i < m_EmpNum; i++) {
		cout << "职工号：" << this->m_EmpArray[i]->m_ID
			<< "  职工姓名：" << this->m_EmpArray[i]->m_name
			<< "  职工类型编号：" << this->m_EmpArray[i]->m_DeptID << endl;
	}

}


WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL) {
		delete[]this->m_EmpArray;
	}
}


void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统! **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}


//员工创建
Employee::Employee(int ID, string name, int DID) {
	this->m_ID = ID;
	this->m_name = name;
	this->m_DeptID = DID;
}

void Employee::showInfo() {
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成任务交给经理" << endl;
}

string Employee::getDeptName() {
	return string("员工");
}


//经理创建
Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = dId;

}


void Manager::showInfo()
{
	cout << "职工编号： " << this->m_ID
		<< " \t职工姓名： " << this->m_name
		<< " \t岗位：" << this->getDeptName()
		<< " \t岗位职责：完成老板交给的任务,并下发任务给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}


//老板创建
Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = dId;

}

void Boss::showInfo()
{
	cout << "职工编号： " << this->m_ID
		<< " \t职工姓名： " << this->m_name
		<< " \t岗位：" << this->getDeptName()
		<< " \t岗位职责：管理公司所有事务" << endl;
}


string Boss::getDeptName()
{
	return string("总裁");
}


//增加职工
void WorkerManager::Add_Emp() {
	cout << "请输入增加职工数量：" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下内容存放到新空间内
		if (this->m_EmpNum != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++) {
			int ID;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个职工编号：" << endl;
			cin >> ID;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;


			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1://普通员工
				worker = new Employee(ID, name, 1);
				break;
			case 2://经理
				worker = new Manager(ID, name, 2);
				break;
			case 3://老板
				worker = new Boss(ID, name, 3);
				break;
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[]this->m_EmpArray;

		//更新新空间的指向
		this->m_EmpArray = newSpace;
		
		//更新新的个数
		this->m_EmpNum = newSize;
		
		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//提示信息
		cout << "成功添加！" << addNum << "名新职工" << endl;
		
		//保存到文件中
		this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}


//统计人数
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}


//初始化员工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		//根据不同部门ID创建不同对象
		if (did == 1)//普通员工
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)//经理
		{
			worker = new Manager(id, name, did);
		}
		else  //总裁
		{
			worker = new Boss(id, name, did);
		}
		//存放在数组里
		this->m_EmpArray[index] = worker;
		index++;
	}
}


//显示职工
void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态性调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}


//判断职工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;	
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_ID == id ) {
			index = 1;
			break;
		}
	}
	return index;
}


//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
			cout << "请输入想删除的职工编号：" << endl;
			int id = 0;
			cin >> id;

			int index = this->IsExist(id);
			if (index != -1)//说明index上位置数据需要删除
			{
				for (int i = (int)index; i < this->m_EmpNum; i++) {
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;

				this->save();//删除后数据同步到文件中
				cout << "删除成功！" << endl;
			}
			else
			{
				cout << "删除失败，未找到该名职工，请重新输入！" << endl;
				system("pause");
				system("cls");
			}
	}

	system("pause");
	system("cls");
}



//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入需要更改的职工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];

			int newID;
			string newName = " ";
			int dSelect = 0;

			cout << "查到：" << id << " 号职工，请输入新职工号：" << endl;
			cin >> newID;

			cout << "请输入新职工名字：" << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newID, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newID, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newID, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
			cout << "查无此人，修改失败！" << endl;
	}

	system("pause");
	system("cls");
}


//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_ID
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}


	system("pause");
	system("cls");
}


//职工排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号升序" << endl;
		cout << "2、按职工号降序" << endl;

		int Select = 0;
		cin >> Select;

		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + i; j < m_EmpNum; j++) {
				if (Select == 1) //升序
				{
					if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else //降序
				{
					if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}

}


//清空职工
void WorkerManager::Clean_Emp()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;

	int select = 0;
	cin >> select;

	if (select = 1)
	{
		//打开模式 ios::trunc 如果存在文件则删除文件并重新创造
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "成功清空文档！" << endl;
	}

	system("pause");
	system("cls");
}


//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_ID << "  "
			<< this->m_EmpArray[i]->m_name << "  "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}

	ofs.close();
}

