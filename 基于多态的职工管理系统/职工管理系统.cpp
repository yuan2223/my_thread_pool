#include<iostream>
using namespace std;

#include"workerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"
#include "worker.h"
void test_show()
{
	//实例化对象
	WorkerManager wm;
	int chioce = -1;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入您的选择" << endl;
		cin >> chioce;
		switch (chioce)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://添加职工
			wm.AddEmp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();     //有相同的编号 哪个在前修改哪个的
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://清空文件
			wm.Clea_File();
			break;
		default:
			system("cls");
			break;
		}

	}
}
//测试代码
void test()
{
	Worker* worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	
	worker = new Manager(2, "李四", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "王五", 3);
	worker->showInfo();
	delete worker;


}
int main()
{
	test_show();
	system("pause");
	return 0;
}