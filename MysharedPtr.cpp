#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Myshared {
public:
	Myshared():count(new int(0)),ptr(nullptr) {
		cout << "create ptr" << endl;
	};

	Myshared(T *p) {
		cout << "create T type ptr" << endl;
		count = new int(1);
		ptr = p;
	}

	Myshared(Myshared<T>& other):ptr(other.ptr),count(other.count) {
		cout << "copy ptr" << endl;
		(*this->count)++;
	}

	Myshared<T>& operator = (Myshared<T>& other) {
		cout << "copy ptr" << endl;
		if (&other == this) {
			return *this;
		}
		++*other.count;
		//cout << *other.count << endl;
		if (this->ptr && -- *this->count == 0) {
			delete this->count;
			delete this->ptr;
			ptr = nullptr;
			count = nullptr;
			cout << "delete ptr" << endl;
		}
		this->count = other.count;
		this->ptr = other.ptr;
		return *this;
	}
	int getCnt() {
		return *count;
	}

	T* operator ->() {
		return ptr;
	}

	T& operator *() {
		return *ptr;
	}

	~Myshared() {
		cout << "cur count " << *count << endl;
		if (ptr && --(*count) == 0) {
			delete ptr;
			delete count;
			ptr = nullptr;
			count = nullptr;
			cout << "delete ptr" << endl;
		}
	}
private:
	T* ptr;
	int* count;
};

int main(void) {
	Myshared<string>foo(new string("this is a test"));
	cout << foo.getCnt() << endl;
	Myshared<string>foo1 = foo;
	cout << foo1.getCnt() << endl;
	cout << foo.getCnt() << endl;
	cout << *foo<< endl;
	Myshared<string>foo2(foo);
	cout << foo1.getCnt() << endl;
	cout << foo2.getCnt() << endl;
	return 0;
}