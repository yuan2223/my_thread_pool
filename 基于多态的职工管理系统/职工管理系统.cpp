#include<iostream>
using namespace std;

#include"workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include "worker.h"
void test_show()
{
	//ʵ��������
	WorkerManager wm;
	int chioce = -1;
	while (true)
	{
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> chioce;
		switch (chioce)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://���ְ��
			wm.AddEmp();
			break;
		case 2://��ʾְ��
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4://�޸�ְ��
			wm.Mod_Emp();     //����ͬ�ı�� �ĸ���ǰ�޸��ĸ���
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����ļ�
			wm.Clea_File();
			break;
		default:
			system("cls");
			break;
		}

	}
}
//���Դ���
void test()
{
	Worker* worker = NULL;
	worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;

	
	worker = new Manager(2, "����", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "����", 3);
	worker->showInfo();
	delete worker;


}
int main()
{
	test_show();
	system("pause");
	return 0;
}