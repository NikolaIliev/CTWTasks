#include <mutex>
#include <iostream>
#include "JobQueue.h"
using namespace std;

void JobQueue::addJob(int job) {
	{
		lock_guard<mutex> lock(m);
		jobs.push(job);
	}
	cv.notify_one();
}

int JobQueue::getJob() {
	unique_lock<mutex> lock(m);

	if (jobs.empty()) {
		cv.wait(lock, [&] { return !jobs.empty(); });
	}

	int job = jobs.front();
	jobs.pop();

	return job;
}