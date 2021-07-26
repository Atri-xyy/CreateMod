#include <iostream>

using namespace std;

template<typename T>
class MyVector {
public:
	MyVector() :data(nullptr), size(0), capacity(0) {};
	MyVector(int _size) :data(nullptr), size(_size), capacity(_size * 1.5) {
		assert(size > 0);
		data = new T[capacity];
		memset(data, 0, size * sizeof(T));
	};
	int getSize() {
		return size;
	}
	int getCapacity() {
		return capacity;
	}
	T& operator [](int index) {
		return data[index];
	}

	void push_back(T value) {
		if (capacity == 0 || size == capacity) {
			resize();
		}
		data[size++] = value;
	}
	void resize() {
		if (size == 0) {
			capacity = 1;
			data = new T[capacity];
		}
		else {
			capacity = capacity * 2;
			T* newT = new T[capacity];
			for (int i = 0; i < size; i++) {
				newT[i] = t[i];
			}
			delete[]t;
			t = newT;
		}
	}

	void pop_back() {
		data[size--] = 0;
	}

	MyVector& operator = (MyVector<T>& other) {
		if (this == &other) {
			return *this;
		}
		else {
			if (data)
				delete[]data;
			this->capacity = other.capacity;
			this->size = other.size;
			data = new T[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = other.data[i];
			}
			return *this;
		}
	}

	MyVector(MyVector<T>& other) :data(nullptr), size(0), capacity(0) {
		*this = other;
	}

	void show() {
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}
	~MyVector() {
		delete[]data;
	}
private:
	T* data;
	int size;
	int capacity;
};
int main() {
	MyVector<int>t(3);
	t.push_back(1);
	t[2] = 2;
	t.push_back(3);
	MyVector<int>q;
	q = t;
	q.show();
	MyVector<int>s(q);
	s.show();
	s.pop_back();
	s.show();
	cout << s.getSize() << " " << s.getCapacity() << endl;
	s.push_back(4);
	s.show();
	return 0;
}
