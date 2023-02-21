#include "manager.h"


Manager::Manager(int id, string name, int job) {
	this->worker_id = id;
	this->worker_name = name;
	this->worker_job = job;
}
string Manager::get_job() {
	return "经理";
}
void Manager::showInfo() {
	std::cout << "职工编号：" << this->worker_id
		<< "\t职工姓名：" << this->worker_name
		<< "\t岗位：" << this->get_job()
		<< "\t岗位职责：完成老板交给的任务，并分发给员工" << std::endl;
}