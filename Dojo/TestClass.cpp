#include "TestClass.h"
#include <iostream>


TestClass::TestClass()
	: TestClass(0, 0, "")
{
}

TestClass::TestClass(int nr, int pnr, std::string str)
	: _nr(nr), _str(str)
{
	_pnr = new int(pnr);
}


TestClass::~TestClass()
{
	delete _pnr;
}

TestClass::TestClass(const TestClass & rhs)
	: _nr(rhs._nr), _str(rhs._str)
{
	_pnr = new int(*rhs._pnr);
	std::cout << "copy constructor" << std::endl;
}

TestClass & TestClass::operator=(const TestClass & rhs)
{
	std::cout << "copy assignment" << std::endl;

	//cz�sto u�ywany wzorzec do pisania operatora przypisania
	auto temp = TestClass(rhs);
	std::swap(_nr, temp._nr);
	std::swap(_pnr, temp._pnr);
	std::swap(_str, temp._str);

	//r�wnie dobrze mo�e by� tak
	//_nr = rhs._nr;
	//_str = rhs._str;
	//_pnr = new int(*rhs._pnr);
	return *this;
}

TestClass::TestClass(TestClass && rhs)
	: _nr(rhs._nr), _str(rhs._str), _pnr(rhs._pnr)
{
	rhs._pnr = nullptr; //ukrad�em pami�� rhs
	std::cout << "move constructor" << std::endl;
}

TestClass & TestClass::operator=(TestClass && rhs)
{
	std::cout << "move assignment" << std::endl;

	//nie musimy czy�ci� sk�adowych this, bo swapujemy je do obiektu kt�ry i tak zostanie zniszczony 
	//(chyba �e operator= by� wywo�any z argumentem z std::move, tak �e nie wiem czy to jest dobry dizajn)
	std::swap(_nr, rhs._nr);
	std::swap(_pnr, rhs._pnr);
	std::swap(_str, rhs._str);
	//by� mo�e rzeczy z rhs powinny by� obj�te przez std::move, w sumie nie wiem jak to dzia�a na bazowych typach

	//_nr = std::move(rhs._nr);
	//_str = std::move(rhs._str);
	return *this;
}
