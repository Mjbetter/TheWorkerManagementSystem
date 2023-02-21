#pragma once
#include "worker.h"

using namespace std;

class Boss :public Worker {
public:
	Boss(int id, string name, int job);
	virtual string get_job();
	virtual void showInfo();
};