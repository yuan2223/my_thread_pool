#pragma once //防止头文件重复包含
#include<iostream>
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();//构造函数初始化属性

	//展示菜单
	void Show_Menu();
	//退出系统
	void ExitSystem();
	
	//记录职工人数
	int m_Empnum;

	//职工数组指针
	Worker** EmpArray;

	//添加职工
	void AddEmp();
	//保存文件
	void save();

	//判断文件是否为空的标志'
	bool m_FileIsEmpty;

	//统计文件中的人员个数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();
	//判断职工是否存在 存在返回职工所在数组的下标 不存在返回-1
	int IsExit(int id);

	//修改职工
	void Mod_Emp();

	//查找员工
	void Find_Emp();

	//清空文件
	void Clea_File();


	~WorkerManager();

};
