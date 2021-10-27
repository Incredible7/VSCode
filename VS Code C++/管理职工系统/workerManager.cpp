#include"workerManager.h"
#include"worker.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if ( ! ifs.is_open()) {
		cout << "�ļ������ڣ�" << endl;
		this->m_EmpNum = 0;        //��ʼ������
		this->m_FileIsEmpty = 1;     //��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;     //��ʼ������
		ifs.close();
		return;
	}

	//�ļ����ڣ�����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}

	//ͳ������
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;   //���Դ���
	this->m_EmpNum = num;     //���³�Ա����

	//����ְ������������
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//��ʼ��Ա��
	init_Emp();
	//���Դ���
	for (int i = 0; i < m_EmpNum; i++) {
		cout << "ְ���ţ�" << this->m_EmpArray[i]->m_ID
			<< "  ְ��������" << this->m_EmpArray[i]->m_name
			<< "  ְ�����ͱ�ţ�" << this->m_EmpArray[i]->m_DeptID << endl;
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
	cout << "*********  ��ӭʹ��ְ������ϵͳ! **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}


//Ա������
Employee::Employee(int ID, string name, int DID) {
	this->m_ID = ID;
	this->m_name = name;
	this->m_DeptID = DID;
}

void Employee::showInfo() {
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ��������񽻸�����" << endl;
}

string Employee::getDeptName() {
	return string("Ա��");
}


//������
Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = dId;

}


void Manager::showInfo()
{
	cout << "ְ����ţ� " << this->m_ID
		<< " \tְ�������� " << this->m_name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ������ϰ彻��������,���·������Ա��" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}


//�ϰ崴��
Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = dId;

}

void Boss::showInfo()
{
	cout << "ְ����ţ� " << this->m_ID
		<< " \tְ�������� " << this->m_name
		<< " \t��λ��" << this->getDeptName()
		<< " \t��λְ�𣺹���˾��������" << endl;
}


string Boss::getDeptName()
{
	return string("�ܲ�");
}


//����ְ��
void WorkerManager::Add_Emp() {
	cout << "����������ְ��������" << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if (this->m_EmpNum != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++) {
			int ID;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "��ְ����ţ�" << endl;
			cin >> ID;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;


			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1://��ͨԱ��
				worker = new Employee(ID, name, 1);
				break;
			case 2://����
				worker = new Manager(ID, name, 2);
				break;
			case 3://�ϰ�
				worker = new Boss(ID, name, 3);
				break;
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[]this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		
		//�����µĸ���
		this->m_EmpNum = newSize;
		
		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ��Ϣ
		cout << "�ɹ���ӣ�" << addNum << "����ְ��" << endl;
		
		//���浽�ļ���
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}


//ͳ������
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		//��¼����
		num++;
	}
	ifs.close();

	return num;
}


//��ʼ��Ա��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		//���ݲ�ͬ����ID������ͬ����
		if (did == 1)//��ͨԱ��
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)//����
		{
			worker = new Manager(id, name, did);
		}
		else  //�ܲ�
		{
			worker = new Boss(id, name, did);
		}
		//�����������
		this->m_EmpArray[index] = worker;
		index++;
	}
}


//��ʾְ��
void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++) {
			//���ö�̬�Ե��ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}


//�ж�ְ���Ƿ����
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


//ɾ��ְ��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//��ְ�����ɾ��
			cout << "��������ɾ����ְ����ţ�" << endl;
			int id = 0;
			cin >> id;

			int index = this->IsExist(id);
			if (index != -1)//˵��index��λ��������Ҫɾ��
			{
				for (int i = (int)index; i < this->m_EmpNum; i++) {
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
				this->m_EmpNum--;

				this->save();//ɾ��������ͬ�����ļ���
				cout << "ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "ɾ��ʧ�ܣ�δ�ҵ�����ְ�������������룡" << endl;
				system("pause");
				system("cls");
			}
	}

	system("pause");
	system("cls");
}



//�޸�ְ��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫ���ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newID;
			string newName = " ";
			int dSelect = 0;

			cout << "�鵽��" << id << " ��ְ������������ְ���ţ�" << endl;
			cin >> newID;

			cout << "��������ְ�����֣�" << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			//�������ݵ�������
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->save();
		}
		else
			cout << "���޴��ˣ��޸�ʧ�ܣ�" << endl;
	}

	system("pause");
	system("cls");
}


//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //��ְ���Ų���
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) //����������
		{
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_ID
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}


	system("pause");
	system("cls");
}


//ְ������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ��������" << endl;
		cout << "2����ְ���Ž���" << endl;

		int Select = 0;
		cin >> Select;

		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + i; j < m_EmpNum; j++) {
				if (Select == 1) //����
				{
					if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else //����
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

		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}

}


//���ְ��
void WorkerManager::Clean_Emp()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;

	int select = 0;
	cin >> select;

	if (select = 1)
	{
		//��ģʽ ios::trunc ��������ļ���ɾ���ļ������´���
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
		cout << "�ɹ�����ĵ���" << endl;
	}

	system("pause");
	system("cls");
}


//�����ļ�
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

