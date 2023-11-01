#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = dId;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getDepeName()
		<< "\t岗位职责：完成老板交给的任务" << endl;
}

string Manager::getDepeName()
{
	return string("经理");
}


