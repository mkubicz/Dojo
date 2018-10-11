#pragma once
#include <unordered_map>
#include <set>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace uniref_tag_dispatch
{

std::multiset<std::string> names;
std::unordered_map<int, std::string> namesDict{ { 1, "Mike" },{ 2, "Spike" },{ 3,"Stoo" },{ 4,"Jools" } };


//chcê mieæ funkcjê która bierze uniref i jakiœ overload tej funkcji
template<typename T>
void addname(T&& name)
{
	//assert bo kompilator robi niezbtyt pomocne komunikaty
	static_assert(is_constructible<std::string, T>::value, "Parameter name can't be used to construct a string.");
	std::cout << "Adding name \"" << name << "\"." << std::endl;
	names.emplace(std::forward<T>(name));
}

//template<typename T>
void addname(int namenr)
{
	std::cout << "Adding name nr. " << namenr << " (" << namesDict[namenr] << ")." << std::endl;
	names.emplace(namesDict[namenr]);
}

void start()
{
	short i = 5;
	addname("test");
	addname(1);
	//addname(i); //error, wiêc robimy tag dispatch
}


//no to robimy tag dispatch
template<typename T>
void addname2(T&& name)
{
	addnameImpl(std::forward<T>(name),
				std::is_integral<std::remove_reference_t<T>>());
	//std::is_integral zwróci coœ typu integral_constant<T1,T2> po którym dziedziczy true_type i false_type
}

template<typename T>
void addnameImpl(T&& name, std::false_type) //przyjmuje argument typu false_type (nienazwany)
{

	std::cout << "Adding name \"" << name << "\"." << std::endl;
	names.emplace(std::forward<T>(name));
}

//template<typename T>
void addnameImpl(int namenr, std::true_type) //przyjmuje argument typu true_type (nienazwany)
{
	std::cout << "Adding name nr. " << namenr << " (" << namesDict[namenr] << ")." << std::endl;
	names.emplace(namesDict[namenr]);
}

void start2()
{
	short i = 4;
	addname2("Jops");
	addname2(1);
	addname2(i); //ju¿ ok
}


//TODO: co jakby by³o wiêcej overloadów?




}