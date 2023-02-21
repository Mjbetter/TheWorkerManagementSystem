#pragma once//防止头文件重复包含
#include <iostream>
#include <string>

using namespace std;

class Worker {
public:
	int worker_id=0;//职工id
	string worker_name;//职工姓名
	int worker_job=0;//部门编号
	//获得岗位职责
	virtual string get_job() = 0;
	//显示个人信息
	virtual void showInfo() = 0;
};