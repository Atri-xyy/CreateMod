template <class T>
class MsgQueue {
public:
	MsgQueue() :queue_(), mutex_(), cond_() {};
	MsgQueue& operator = (const MsgQueue&) = delete;
	MsgQueue(const  MsgQueue&) = delete;
	void push(T msg) {
		unique_lock<mutex>lcok(mutex_);
		queue_.push(msg);
		cond_.notify_one();
	}

	bool pop(T& msg, bool isBlock = true) {
		if (isBlock) {
			unique_lock<mutex>lock(mutex_);
			while (queue_.empty()) {
				cond_.wait(lock);
			}
		}
		else {
			unique_lock<mutex>lock(mutex);
			if (queue_.empty()) {
				return false;
			}
		}
		msg = move(queue_.front());
		queue_.pop();
		
		return false;
	}

	bool empty() {
		unique_lock<mutex>lock(mutex);
		return queue_.empty();
	}

private:
	queue<T>queue_;
	mutex mutex_;
	condition_variable cond_;
};