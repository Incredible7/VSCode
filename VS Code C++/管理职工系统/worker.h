#pragma once
#include<iostream>
#include<string>
using namespace std;

//职工抽象基类
class Worker {
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_ID;
	string m_name;
	int m_DeptID;
};

//创建员工类
class Employee :public Worker {
public:
	//构造函数
	Employee(int ID, string name, int dID);
	//展示个人信息
	virtual void showInfo();
	//获取职工岗位名称
	virtual string getDeptName();
};

//创建经理类
class Manager :public Worker {
public:
	Manager(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取职工岗位名称
	virtual string getDeptName();
};

//创建老板类
class Boss :public Worker
{
public:

	Boss(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取职工岗位名称
	virtual string getDeptName();
};