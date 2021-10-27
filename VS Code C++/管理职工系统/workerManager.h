#pragma once
#include"worker.h"
#include<iostream>
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager {
public:
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void exitSystem() {
		cout << "��ӭ�´�ʹ�ã�" << endl;
		system("pause");
		exit(0);
	}

	//��¼�ļ��е���������
	int m_EmpNum;

	//Ա�������ָ��
	Worker** m_EmpArray;

	//����ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void	init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//���ְ��
	void Clean_Emp();

	//��������
	~WorkerManager();

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
	int IsExist(int id);
};

