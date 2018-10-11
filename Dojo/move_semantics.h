#pragma once
#include "TestClass.h"
#include <string>
#include <memory>

class DInt;

void move_ops_1()
{
	TestClass tc;
	TestClass tcCConstr(tc);
	TestClass tcCAss;
	tcCAss = tc;

	tcCAss._nr = 5;
	tcCConstr._nr = 6;
	tc._nr = 1;
	//all is well

	TestClass tcMConstr(std::move(tcCConstr));
	//tylko jak jest referencja to faktycznie zrobi siê move
	//chocia¿ to chyba nie o to chodzi, bo jak wstawiê referencjê przy tcConstr(tc) to siê robi podobna rzecz
	//idk, tak siê tego nie powinno u¿ywaæ, wiêc mo¿e nic dziwnego ¿e nie dzia³a tak jak mi siê wydaje ¿e ma?
	TestClass tcMAss;
	tcMAss = std::move(tcCAss);

	tcCAss._nr = 10;
	tcMAss._nr = 11;
	tcCConstr._nr = 12;
	tcMConstr._nr = 13;
	//hmm, zrobi³o siê move (odpali³y siê move konstruktory), 
	//ale wszystkie obiekty nadal ¿yj¹ jako niezale¿ne twory

	TestClass tcMConstr2(TestClass(100, 100, "test")); //to siê optymalizuje do jednego wywo³ania konstruktora!

	std::unique_ptr<DInt> pdint = std::make_unique<DInt>(5);
	std::unique_ptr<DInt> pdint2;
	pdint.swap(pdint2); //to robi move

	pdint = std::move(pdint2); //to te¿
}

void move_ops_2()
//lepszy przyk³ad z dynamicznym zasobem w klasie (jak nie ma dynamicznych 
//zasobów w klasie to definiowanie swoich moveopsów zwykle nie ma sensu!)
{
	TestClass tc;
	TestClass tcCConstr(tc);
	TestClass tcCAss;
	tcCAss = tc;

	*tcCAss._pnr = 5;
	*tcCConstr._pnr = 6;
	*tc._pnr = 1;
	//all is well

	TestClass tcMConstr(std::move(tcCConstr));
	TestClass tcMAss;
	tcMAss = std::move(tcCAss);

	*tcCAss._pnr = 10; //zadzia³a, tcCAss._pnr to wskaŸnik który wczeœniej mia³ tcMAss 
					   //(normalnie tcCAss zniszczy³by siê natychmiast po wywo³aniu move assignmentu - 
					   //w koñcu jest rvalue, tylko w tym przyk³adzie sztucznym, powsta³ym przez std::move)
	*tcMAss._pnr = 11; //ok
					   //*tcCConstr._pnr = 12; //error; move constr ustawi³ _pnr na nullptr
	*tcMConstr._pnr = 13; //ok
}


template<typename T>
void universalref(T&& param) {};

template<typename T>
void rvalueref(const T&& param) {}; //dodanie const ju¿ wystarczy ¿eby param nie by³ uniwersaln¹ referencj¹

template<typename T>
void lvalueref(T& param) {};

void universalRefVSrvalueRef()
{
	int a = 6;
	universalref(a);
	universalref(6);

	//rvalueref(a); no can do; a to lvalue
	rvalueref(6);

	lvalueref(a);
	//lvalueref(6); no can do; 6 to rvalue
}

class Widget2 {
public:
	template<typename T>
	void setName(T&& newName) // universal reference
	{
		name = std::move(newName);
	}
private:
	std::string name;
};
std::string GetName()
{
	return "test test";
}
void moveitd()
{
	Widget2 w;
	auto n = GetName();
	w.setName(n); //n staje siê pusty, setName ukrad³o zawartoœæ!
}
