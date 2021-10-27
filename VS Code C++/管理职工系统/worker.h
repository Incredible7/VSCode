#pragma once
#include<iostream>
#include<string>
using namespace std;

//ְ���������
class Worker {
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	int m_ID;
	string m_name;
	int m_DeptID;
};

//����Ա����
class Employee :public Worker {
public:
	//���캯��
	Employee(int ID, string name, int dID);
	//չʾ������Ϣ
	virtual void showInfo();
	//��ȡְ����λ����
	virtual string getDeptName();
};

//����������
class Manager :public Worker {
public:
	Manager(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡְ����λ����
	virtual string getDeptName();
};

//�����ϰ���
class Boss :public Worker
{
public:

	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡְ����λ����
	virtual string getDeptName();
};