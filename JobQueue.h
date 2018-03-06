#pragma once
#define JOB_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class JobQueue {
	queue<int> jobs;
	mutex m;
	condition_variable cv;
public:
	void addJob(int);
	int getJob();
};
