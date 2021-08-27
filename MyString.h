#include <iostream>

using namespace std;

class String {
public:
	String(const char* str = nullptr);
	String(const String& str);
	String& operator = (const String& str);
	String &operator += (const String& str);
	String operator + (const String& str);
	char& operator[](int index)const;
	bool operator==(const String& str)const;
	int size()const;
	const char* c_str()const;
private:
	char* data;
	int length;
};

String::String(const char* str) {
	if (str == nullptr) {
		length = 0;
		data = new char[1];
		data[0] = '\0';
	}
	else {
		length = strlen(str);
		data = new char[length + 1];
		strcpy(data, str);
	}
}

String::String(const String& str) {
	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());
}

const char* String::c_str()const {
	return data;
}

int String::size()const {
	return length;
}

bool String::operator==(const String& str)const {
	if (length != str.size())return false;
	return strcmp(data, str.c_str()) == 0 ? true : false;
}

char& String::operator[](int index)const {
	if (index >= length)return data[length - 1];
	return data[index];
}

String String::operator + (const String& str) {
	String newStr;
	newStr.length = length + str.size();
	newStr.data = new char[newStr.length + 1];
	strcpy(newStr.data, data);
	strcat(newStr.data, str.c_str());
	return newStr;
}

String& String::operator = (const String& str) {
	if (this == &str)return *this;
	delete[]data;
	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());
	return *this;
}

String& String::operator += (const String& str) {
	length += str.size();
	char* newData = new char[length + 1];
	strcpy(newData, data);
	strcat(newData, str.c_str());
	delete[]data;
	data = newData;
	return *this;
}