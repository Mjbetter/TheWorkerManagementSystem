#pragma
#include <iostream>
#include <fstream>
#include "worker.h"
#include "manager.h"
#include "employee.h"
#include "boss.h"
#include <algorithm>

#define FILENAME "information.txt"
using namespace std;

class WorkManager {
public:
	//构造函数
	WorkManager();
	//展示菜单
	void show_menu();
	//添加职工功能
	void Add_Workers();
	//保存文件
	void save();
	//统计人数
	int get_EmpNum();
	//初始化
	void init_Emp();
	//展示职工信息
	void Show_Emp();
	//删除职工
	void Delete_Emp();
	//判断职工是否存在
	int isExitEmp(int id);
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//按职工序号进行排序展示
	void Sort_Emp();
	//清空文件
	void Clean_File();

	//记录职工人数
	int m_EmpNum;
	//标志文件是否为空
	bool m_FileIsEmpty;
	//职工指针数组的指针
	Worker** m_EmpArray;
	//析构函数
	~WorkManager();
};