#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include "CombinationGenerator.h"
#include "JobQueue.h"
using namespace std;

mutex m;

void printVector(vector<int>& v) {
    cout << "{ ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << "}";
}

void printSubsets(vector<vector<int>> subsets) {
    cout << "{";
    for (int i = 0; i < subsets.size(); i++) {
        printVector(subsets[i]);
    }
    cout << "}" << endl;
}

void testCombinationGenerator() {
    vector<vector<int>> sets{
        vector<int>(),
        vector<int>{ 1 },
        vector<int>{ 1, 2, 3, 4, 5, 6 },
        vector<int>{ 1, 3, 5, 7, 9, 11 }
    };
    vector<int> cases{ 0, 1, 2, 3, 6, 7 };

    for (vector<int> set : sets) {
        cout << "set: ";
        printVector(set);
        cout << endl;
        CombinationGenerator generator(set);

        for (int k : cases) {
            cout << "k = " << k << ": ";
            printSubsets(generator.generate(k));
        }
        cout << endl;
    }
}

void jobProducer(JobQueue* q) {
    q->addJob(5);
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1500));
        {
            lock_guard<mutex> lock(m);
            cout << "(" << this_thread::get_id() << ") Generated job: " << 1 << endl;
        }
        q->addJob(1);
    }
}

void jobConsumer(JobQueue* q) {
    this_thread::sleep_for(chrono::milliseconds(500));
    while (true) {
        int job = q->getJob();
        {
            lock_guard<mutex> lock(m);
            cout << "(" << this_thread::get_id() << ") Consumed job: " << job << endl;
        }
    }
}

void testJobQueue() {
    JobQueue q;
    thread p1(&jobProducer, &q);
    thread p2(&jobProducer, &q);
    thread c1(&jobConsumer, &q);
    thread c2(&jobConsumer, &q);
    thread c3(&jobConsumer, &q);
    thread c4(&jobConsumer, &q);

    p1.join();
    p2.join();
    c1.join();
    c2.join();
    c3.join();
    c4.join();
}

int main() {
    testCombinationGenerator();
    //testJobQueue();

    int a;
    cin >> a;

    return 0;
}