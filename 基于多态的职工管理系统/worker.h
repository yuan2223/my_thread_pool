#pragma once
#include<iostream>
#include<string>
using namespace std;

//职工抽象类  
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDepeName() = 0; //纯虚函数 不做实现 子类作实现

	int m_id;
	string m_name;
	int m_dept_id;
};
