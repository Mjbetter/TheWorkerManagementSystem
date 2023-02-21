#ifndef _xxxx_
#define _xxxx_
#include <iostream>
#include <string>

using namespace std;

class Worker {
public:
	int worker_id;//职工id
	string worker_name;//职工姓名
	int worker_job;//部门编号
	//获得岗位职责
	virtual string get_job() = 0;
	//显示个人信息
	virtual void showInfo() = 0;
};

class OrdinaryEmployees :public Worker{
public:
	OrdinaryEmployees(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "普通员工";
	}
	virtual void showInfo() {
		std::cout << "职工编号：" << this->worker_id
			<< "\t职工姓名：" << this->worker_name
			<< "\t岗位：" << this->get_job()
			<< "\t岗位职责：完成经理交给的任务" << std::endl;
	}
};
class Manager :public Worker {
public:
	Manager(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "经理";
	}
	virtual void showInfo() {
		std::cout << "职工编号：" << this->worker_id
			<< "\t职工姓名：" << this->worker_name
			<< "\t岗位：" << this->get_job()
			<< "\t岗位职责：完成老板交给的任务，并分发给员工" << std::endl;
	}
};
class Boss :public Worker {
public:
	Boss(int id, string name, int job) {
		worker_id = id;
		worker_name = name;
		worker_job = job;
	}
	virtual string get_job() {
		return "老板";
	}
	virtual void showInfo() {
		std::cout << "职工编号：" << this->worker_id
			<< "\t职工姓名：" << this->worker_name
			<< "\t岗位：" << this->get_job()
			<< "\t岗位职责：负责所有事务，分发任务" << std::endl;
	}
};
#endif // !1
