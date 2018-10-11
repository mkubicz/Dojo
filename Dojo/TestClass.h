#pragma once
#include <string>

class TestClass
{
private:


	

public:
	int _nr;
	int* _pnr;
	std::string _str;

	TestClass();
	TestClass(int nr, int pnr, std::string str);
	~TestClass();

	//copy ops
	TestClass(const TestClass& rhs);
	TestClass& operator=(const TestClass& rhs);

	//move ops
	TestClass(TestClass&& rhs);
	TestClass& operator=(TestClass&& rhs);
};

