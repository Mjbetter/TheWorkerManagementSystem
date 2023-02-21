#include "boss.h"


Boss::Boss(int id, string name, int job) {
	this->worker_id = id;
	this->worker_name = name;
	this->worker_job = job;
}
string Boss::get_job() {
	return "老板";
}
void Boss::showInfo() {
	std::cout << "职工编号：" << this->worker_id
		<< "\t职工姓名：" << this->worker_name
		<< "\t岗位：" << this->get_job()
		<< "\t岗位职责：负责所有事务，分发任务" << std::endl;
}
