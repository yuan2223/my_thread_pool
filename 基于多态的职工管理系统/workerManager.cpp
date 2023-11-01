#include "workerManager.h"

//类外实现 WorkerManage 的构造函数和析构函数
WorkerManager::WorkerManager()
{
	// 文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // 读文件
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_Empnum = 0;
		this->EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
	}
	
	//文件存在 但是没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空 ！" << endl;
		this->m_Empnum = 0;
		this->EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}	

	//文件存在，并记录数据
	int num = this->get_EmpNum();
	//cout << "职工人数为: " << num << endl;
	this->m_Empnum = num;

	//开辟空间
	this->EmpArray = new Worker * [this->m_Empnum];
	//将文件中的数据存到数组中
	this->init_Emp();
	
}

//读取文件中职工人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件  读
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) //ifs读每一行的数据
	{
		num++;
	}
	return num;
}

//保存数据
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);  //用输出的方式打开文件 写文件
	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->EmpArray[i]->m_id << " "
			<< this->EmpArray[i]->m_name << " "
			<< this->EmpArray[i]->m_dept_id << endl;
	}
	//关闭文件
	ofs.close();
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "****************************************" << endl;
	cout << "**********欢迎使用职工管理系统**********" << endl;
	cout << "************ 0 退出管理程序 ************" << endl;
	cout << "************ 1 增加职工信息 ************" << endl;
	cout << "************ 2 显示职工信息 ************" << endl;
	cout << "************ 3 删除离职信息 ************" << endl;
	cout << "************ 4 修改职工信息 ************" << endl;
	cout << "************ 5 查找职工信息 ************" << endl;
	cout << "************ 6 清空所有文档 ************" << endl;
	cout << "****************************************" << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkerManager::AddEmp()
{
	cout << "请输入添加职工的数量" << endl;
	int add_num = 0;
	cin >> add_num;
	if (add_num > 0)
	{
		//计算添加新空间的大小
		int NewSize = this->m_Empnum + add_num; //新空间人数 = 原来的人数 + 新增人数
		
		//开辟空间
		Worker** newSpace = new Worker * [NewSize]; //每个数据的类型是 Worker*  

		//将原来空间下的数据拷贝到新空间下
		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newSpace[i] = this->EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < add_num; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新员工的编号: " << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新员工的姓名: " << endl;
			cin >> name;

			cout << "请选择该职工的岗位 " << endl;
			cin >> dSelect;  //1 2 3

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//新员工的指针需要保存到数组里面
			newSpace[this->m_Empnum + i] = worker;
		}

		//释放原来的空间
		delete[] this->EmpArray;//释放数组需要加上[]\

		//更改新空间的指向
		this->EmpArray = newSpace;

		//更新职工人数
		this->m_Empnum = NewSize;

		this->m_FileIsEmpty = false;
		cout << "成功添加" << add_num << "名新员工" << endl;

		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}
	//按任意键后，清屏按任意键回到上级目录
	system("pause");
	system("cls");
}

void WorkerManager:: init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else 
		{
			worker = new Boss(id, name, dId);
		}
		this->EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_Empnum; i++)
		{
			//利用多态调用程序接口
			this->EmpArray[i]->showInfo(); //在Boss Employee Manager 中都有 showInfo()函数
		}
	}
	system("pause");
	system("cls");
}

//删除员工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;;
	}
	else
	{
		cout << "请输入要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret == -1)
		{
			cout << "职工不存在" << endl;
		}
		else
		{
			for (int i = ret; i < this->m_Empnum - 1; i++)
			{
				this->EmpArray[i] = this->EmpArray[i + 1];
			}
			//更新数组中人员个数
			this->m_Empnum--;
			//数据更新到文件
			this->save();
			cout << "删除成功!" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (id == this->EmpArray[i]->m_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//修改信息
void WorkerManager::Mod_Emp()
{
	//直接覆盖m_dept_id不会变 员工还是员工
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入要修改职工的编号" << endl;
		int ret = 0;
		cin >> ret;
		int index = this->IsExit(ret);
		if (index == -1)
		{
			cout << "该职工不存在" << endl;
		}
		else
		{
			delete this->EmpArray[index];
			int id;
			string name;
			int dSelect;
			cout << "请输入新的id" << endl;
			cin >> id;
			cout << "请输入新的姓名" << endl;
			cin >> name;
			cout << "请输入新的的岗位" << endl;
			cin >> dSelect;

			Worker* worker = NULL; //创建父类指针

			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			}
				
			//更新数据到数组中
			this->EmpArray[index] = worker;
			this->save();
			
			cout << "修改成功" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		int id = 0;
		cout << "请输入要查找的编号" << endl;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret == -1)
		{
			cout << "查无此人" << endl;
		}
		else
		{
			this->EmpArray[ret]->showInfo();
		}
	} 
	system("pause");
	system("cls");
}

//清空文件
void WorkerManager::Clea_File()
{
	cout << "确认清空 " << endl;
	cout << "1 确认" << endl;
	cout << " 2 返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//如果存在 删除文件并重新创建
		ofs.close();

		if (this->EmpArray != NULL)
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->EmpArray[i] != NULL)
				{
					delete this->EmpArray[i];
				}
			}
			this->m_Empnum = 0;
			delete[] this->EmpArray;
			this->EmpArray = NULL;
			this->m_FileIsEmpty = true;

		}
		cout << "清除成功" << endl;

	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()
{
	//手动释放堆区的数据
	if (this->EmpArray != NULL)
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			if (this->EmpArray[i] != NULL)
			{
				delete this->EmpArray[i];
			}
		}
		delete[] this->EmpArray;
		this->EmpArray = NULL;
	}
}
