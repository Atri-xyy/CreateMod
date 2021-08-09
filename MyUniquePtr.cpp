#include <iostream>

using namespace std;


template <typename T>
class UniquePtr {
public:
	UniquePtr();
	UniquePtr(T* ptr);
	~UniquePtr();
	UniquePtr(UniquePtr<T>&) = delete;
	UniquePtr<T>& operator = (UniquePtr<T>&) = delete;//ɾ���������캯��
	UniquePtr(UniquePtr<T>&&);//����ʹ���ƶ����캯��
	UniquePtr<T>& operator = (UniquePtr<T>&& p);
	void swap(UniquePtr<T>& p);
	
	T* operator->() {
		return ptr;
	}
	T& operator*() {
		return *ptr;
	}
	T* get()const {//����ԭʼָ��
		return ptr;
	}

	T* release() {
		T* t = this->ptr;
		this->ptr = nullptr;
		return t;
	}

private:
	T* ptr;
};
template <typename T>
UniquePtr<T>::UniquePtr():ptr(nullptr) {

}

template <typename T>
UniquePtr<T>::UniquePtr(T* p) {
	this->ptr = p;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
	if (ptr) {
		delete ptr;
		cout << "delete ptr" << endl;
	}
}

//�ƽ�����Ȩ
template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& p):ptr(p.ptr) {
	 cout << "move ptr" << endl;
	 p.ptr = nullptr;
}

//�ƶ���ֵ
template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& p)
{
	this->swap(p.ptr);
	return *this;
}

template <typename T>
void UniquePtr<T>::swap(UniquePtr<T>& p) {	
	T* t = p.ptr;
	p.ptr = this->ptr;
	this->ptr = t;
}

int main(void){
	UniquePtr<string>test(new string("Hello world"));
	cout << *test << endl;
	UniquePtr<string>test1(new string("World hello"));
	test.swap(test1);
	cout << *test << endl;
	cout << *test1 << endl;
	UniquePtr<string>test2 = move(test1);
	cout << *test2 << endl;
	string *str = test2.release();
	cout << *str << endl;
	delete str;
	return 0;
}