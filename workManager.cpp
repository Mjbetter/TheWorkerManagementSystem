#include "workManager.h"

bool  cmp1(Worker* worker1, Worker* worker2) {
	return worker1->worker_id < worker2->worker_id;
}
bool  cmp2(Worker* worker1, Worker* worker2) {
	return worker1->worker_id > worker2->worker_id;
}

WorkManager::WorkManager() {
	//文件不存在时，初始化属性
	ifstream ifs(FILENAME, ios::in);
	if (!(ifs.is_open())) {
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在并且存在数据
	this->m_EmpNum = this->get_EmpNum();
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum*sizeof(Worker)];
	//将文件中的数据，存到数组中
	this->init_Emp();
}

void WorkManager::show_menu() {
	std::cout << "---------------------" << std::endl;
	std::cout << "0、退出管理程序" << std::endl;
	std::cout << "1、增加职工信息" << std::endl;
	std::cout << "2、显示职工信息" << std::endl;
	std::cout << "3、删除离职职工" << std::endl;
	std::cout << "4、修改职工信息" << std::endl;
	std::cout << "5、查找职工信息" << std::endl;
	std::cout << "6、按照编号排序" << std::endl;
	std::cout << "7、清空所有文档" << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;
	std::cout << "请输入需要使用的功能序号" << std::endl;
}

void WorkManager::Add_Workers() {
	system("cls");
	std::cout << "请输入需要增加的职工的数量:" << std::endl;
	int numbers = 0;//保存用户输入的数量
	while (std::cin >> numbers) {
		if (numbers < 0) {
			std::cout << "输入的数量必须为正数，请重新输入：" << endl;
		}
		else {
			//计算新添加空间大小
			int newSize = this->m_EmpNum + numbers;
			//开辟新空间
			Worker** newSpace = new Worker * [newSize*sizeof(Worker)];
			//将原来空间下的数据拷贝到新空间下
			if (this->m_EmpArray != NULL) {
				for (int i = 0; i < this->m_EmpNum; i++) {
					newSpace[i] = this->m_EmpArray[i];
				}
			}
			//添加新数据
			for (int i = 0; i < numbers; i++) {
				int id;//职工编号
				string name;//职工姓名
				int dSelect;//部门选择
				std::cout << "请输入第" << i + 1 << "个新职工的编号:" << std::endl;
				std::cin >> id;
				while (this->isExitEmp(id) == -1) {
					std::cout << "该职工编号已存在，请重新输入:" << std::endl;
					std::cin >> id;
				}
				std::cout << "请输入第" << i + 1 << "个新职工的姓名:" << std::endl;
				std::cin >> name;
				std::cout << "请选择第" << i + 1 << "个新职工的部门:" << std::endl;
				std::cout << "1、普通职工" << std::endl;
				std::cout << "2、经理" << std::endl;
				std::cout << "3、老板" << std::endl;
				std::cin >> dSelect;
				Worker* worker = NULL;
				switch (dSelect) {
				case 1:
					worker = new OrdinaryEmployees(id, name, dSelect);
					break;
				case 2:
					worker = new Manager(id, name, dSelect);
					break;
				case 3:
					worker = new Boss(id, name, dSelect);
					break;
				default:
					break;
				}
				//将创建职工职责，保存到数组中
				newSpace[this->m_EmpNum + i] = worker;
			}
			//释放原有空间
			delete[] this->m_EmpArray;
			//更改新空间的指向
			this->m_EmpArray = newSpace;
			//更新新的职工人数
			this->m_EmpNum = newSize;
			//更新文件不为空
			this->m_FileIsEmpty = false;
			//提示
			std::cout << "成功添加" << numbers << "名人员" << std::endl;
			this->save();
			break;
		}
	}
	system("pause");
	system("cls");
}

int WorkManager::get_EmpNum() {
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		//统计人数
		num++;
	}
	return num;
}

void WorkManager::init_Emp() {
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did == 1) {
			worker = new OrdinaryEmployees(id, name, did);
		}
		if (did == 2) {
			worker = new Manager(id, name, did);
		}
		if (did == 3) {
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index++] = worker;
	}
	ifs.close();
}

void WorkManager::save() {
	ofstream ofs(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->worker_id << " "
			<< this->m_EmpArray[i]->worker_name << " "
			<< this->m_EmpArray[i]->worker_job << " " << endl;
	}
	ofs.close();
}

void WorkManager::Show_Emp() {
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		std::cout << "文件不存在或者记录为空" << std::endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Delete_Emp() {
	if (this->m_FileIsEmpty) {
		return;
	}
	else {
		//输入想要删除的职工的编号
		int id;
		std::cout << "输入想要删除的职工的编号:" << std::endl;
		std::cin >> id;
		int judge = this->isExitEmp(id);
		if (judge == 0) {
			std::cout << "删除失败，没有找到这个职工" << std::endl;
			return;
		}
		else {
			for (int i = 0; i < this->m_EmpNum-1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			std::cout << "删除成功" << std::endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkManager::isExitEmp(int id) {
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->worker_id == id) {
			return 1;
		}
	}
	return 0;
}

void WorkManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "文件不存在或为空！" << std::endl;
	}
	else {
		int id=-1;
		std::cout << "请输入要修改的职工的ID" << std::endl;
		std::cin >> id;
		int ret = this->isExitEmp(id);
		if (ret != -1) {
			//删除原来职工的信息
			delete this->m_EmpArray[ret];
			//录入该职工新的信息
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			std::cout << "查到：" << id << "号职工,请输入新的职工编号：" << std::endl;
			std::cin >> newId;
			while (this->isExitEmp(newId) == 1) {
				std::cout << "该员工编号已存在，重新输入编号:" << std::endl;
				std::cin >> newId;
			}
			std::cout << "查到：" << id << "号职工，请输入新的职工姓名:" << std::endl;
			std::cin >> newName;
			std::cout << "查到：" << id << "号职工，请输入新的职工岗位:" << std::endl;
			std::cout << "1、普通员工" << std::endl;
			std::cout << "2、经理" << std::endl;
			std::cout << "3、老板" << std::endl;
			std::cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new OrdinaryEmployees(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数据到数组中
			this->m_EmpArray[ret] = worker;
			std::cout << "修改成功" << std::endl;
			//保存到文件中
			this->save();
		}
		else {
			std::cout << "查无此人" << std::endl;		
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "文件不存在或者为空!" << endl;
	}
	else {
		std::cout << "请输入查找的方法或者方式" << std::endl;
		std::cout << "1.按照职工的编号查找" << std::endl;
		std::cout << "2.按照职工的姓名查找" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "输入的序号错误，请重新输入编号:" << std::endl;
		}
		if (dSelect == 1) {
			//按照编号查找
			std::cout << "请输入要查询的编号:" << std::endl;
			int id = -1;
			std::cin >> id;
			while (this->isExitEmp(id)==0) {
				std::cout << "该编号不存在，请重新输入编号:" << std::endl;
				std::cin >> id;
			}
			std::cout << "查找成功，该职工的信息如下:" << std::endl;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->worker_id == id) {
					this->m_EmpArray[i]->showInfo();
				}
			}

		}
		else if (dSelect == 2) {
			//按照职工的姓名来查找
			string name;
			int judge = 0;
			std::cout << "请输入要查找的姓名" << std::endl;
			std::cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++) {
				std::cout << "查找结果如下:" << std::endl;
				if (this->m_EmpArray[i]->worker_name == name) {
					judge++;
					std::cout << "找到编号为" << this->m_EmpArray[i]->worker_id << "的职工信息如下:" << std::endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (judge == 0) {
				std::cout << "未找到任何相关姓名职工" << std::endl;
			}
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		std::cout << "文件不存在或者为空!" << endl;
	}
	else {
		std::cout << "请选择排序类型:" << std::endl;
		std::cout << "1.序号从大到小排序" << std::endl;
		std::cout << "2.序号从小到大排序" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "输入的序号不正确，请重新输入序号:" << std::endl;
		}
		//复制一份目前的数据
		Worker** temp = this->m_EmpArray;
		if (dSelect == 1) {
			sort(temp, temp + this->m_EmpNum, cmp2);
		}
		else if(dSelect == 2) {
			sort(temp, temp + this->m_EmpNum, cmp1);
		}
		std::cout << "排序成功，结果如下:" << std::endl;
		for (int i = 0; i < this->m_EmpNum; i++) {
			temp[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Clean_File() {
	if (this->m_FileIsEmpty) {
		std::cout << "文件不存在或者为空!" << endl;
	}
	else {
		std::cout << "确定清空吗?" << std::endl;
		std::cout << "1.确定" << std::endl;
		std::cout << "2.返回" << std::endl;
		int dSelect = 0;
		while (1) {
			std::cin >> dSelect;
			if (dSelect == 1 || dSelect == 2) break;
			std::cout << "输入的序号不正确，请重新输入序号:" << std::endl;
		}
		if (dSelect == 1) {
			ofstream ofs(FILENAME, ios::trunc);//删除文件再重新创建
			ofs.close();
			if (this->m_EmpArray != NULL) {
				//删除堆区的每个职工对象
				for (int i = 0; i < this->m_EmpNum; i++) {
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;
			}
			std::cout << "清空成功" << std::endl;
			system("pause");
			system("cls");
		}
	}
}

WorkManager::~WorkManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}