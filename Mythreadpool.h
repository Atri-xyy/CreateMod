#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include <functional>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
using namespace std;

class Mythreadpool
{
public:
	
	using Task = function<void()>;
	void taskAppend(const Task& task) {
		if (is_running) {
			unique_lock<mutex>m_lock(m_mutex);
			tasks.push_back(task);
			m_cond.notify_one();
		}
	}

	void start() {
		is_running = true;
		for (int i = 0; i < thread_nums; i++) {
			threads.emplace_back(thread(bind(&Mythreadpool::work, this)));
		}
	}

	void stop() {
		{
			unique_lock<mutex>m_lock(m_mutex);
			m_cond.notify_all();
			is_running = false;
		}
		for (auto& i : threads) {
			if (i.joinable()) {
				i.join();
			}
		}
	}

	~Mythreadpool() {
		if (is_running) {
			stop();
		}
	}
	static Mythreadpool* Getinstance() {
		if (instance == nullptr) {
			unique_lock<mutex>m_lock(m_mutex);
			if (instance == nullptr) {
				instance = new Mythreadpool;
			}
		}
		return  instance;
	}

	Mythreadpool(const Mythreadpool&) = delete;
	Mythreadpool& operator = (const Mythreadpool&) = delete;
private:
	Mythreadpool():is_running(false) {};
	void work() {
		cout << "begin work.id:" << this_thread::get_id() << endl;
		while (is_running)
		{
			Task task;
			{
				unique_lock<mutex>m_lock(m_mutex);
				if (!tasks.empty() && is_running) {
					task = tasks.front();
					tasks.pop_front();
				}
				else if (tasks.empty()&& is_running) {
					m_cond.wait(m_lock);
				}
				
			}
			if (task)task();
		}
		cout<<"end work.id:"<< this_thread::get_id() << endl;
	}

private:
	static const int thread_nums = 8;
	atomic_bool is_running;
	static Mythreadpool* instance;
	static mutex m_mutex;
	static condition_variable m_cond;
	vector<thread>threads;
	list<Task>tasks;
};
Mythreadpool* Mythreadpool::instance = nullptr;
mutex Mythreadpool::m_mutex;
condition_variable Mythreadpool::m_cond;

#endif // !_THREADPOOL_H



