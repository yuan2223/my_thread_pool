#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = dId;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getDepeName()
		<< "\t岗位职责：管理所有事务" << endl;
}

string Boss::getDepeName()
{
	return string("老板");
}
