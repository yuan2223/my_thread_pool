#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = dId;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDepeName()
		<< "\t��λְ������ϰ彻��������" << endl;
}

string Manager::getDepeName()
{
	return string("����");
}


