#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = dId;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_id
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDepeName()
		<< "\t��λְ�𣺹�����������" << endl;
}

string Boss::getDepeName()
{
	return string("�ϰ�");
}
