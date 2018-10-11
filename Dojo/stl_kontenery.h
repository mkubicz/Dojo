#pragma once
#include <vector>
#include <type_traits>

namespace stl_kontenery
{


void start_vector()
{
	std::vector<std::string> vect{ "zero", "one", "two", "three" };
	vect.push_back("four");

	if (vect.at(2) == vect[2]) std::cout << "No raczej kurcze blade nie inaczej" << std::endl;

	auto &ostatniref = vect.back();
	ostatniref.append("r"); //vect[4] == fourr

	auto ostatnikopia = vect.back();
	ostatnikopia.append("k"); //vect[4] == fourr, k doda�o si� tylko do kopii

	vect.size(); //m�wi ile jest element�w --5
	vect.capacity(); //m�wi ile jest miejsca w wektorze --5

	vect.pop_back();

	vect.size(); //4
	vect.capacity(); //5

	std::vector<std::string> vect2{ "ep", "op", "hep" };

	vect.insert(vect.begin() + 1, { "lala", "lalala", "uhuhu" });

	vect2.insert(vect2.begin(), 3, "t");
	//vect2 == { "t", "t", "t", "ep", "op", "hep" }

	vect2.insert(vect2.end(), vect.begin(), vect.end());
	//vect2 = vect2 + vect;

	std::vector<std::string> vect3{ "aa", "bb", "cc" };

	vect3.emplace(vect3.begin(), size_t(5), 'd'); 
	//konstruuje element "in place", w li�cie argument�w podajesz argumenty konstruktora wybranego typu, one wchodz� do uniwersalnej referencji czyli mo�na je przenie��
	//vect3 = { "ddddd", "aa", "bb", "cc" }

	vect.erase(vect.begin() + 2, vect.end() - 2);

	vect3.erase(std::remove_if(vect3.begin(), vect3.end(), [](const std::string& s) { return s.length() == 2; }), vect3.end());
	//vect3 == { "ddddd" }

	vect3.max_size();

	system("PAUSE");
}

//template<typename Container>
//typename enable_if< CallableWithBeginAndEnd<Container>::value, void >::type
//sortuj(Container &container)
//{ //je�li wywo�amy z czym� innym ni� kontener kt�ry ma iteratory to b�d� dziwne b��dy
//	std::sort(container.begin(), container.end());
//}
//musia�bym chyba napisa� to CallableWithBeginAndEnd jako struktur�
//albo mo�na zrobi� co� w stylu enable_if is_type vector lub list lub ...
//ale mo�e nie ma sie co z tym m�czy�

void start_array()
{
	std::array<int, 5> arr{ 1,2,4,5,3 };
	
	std::array<int, 5> arr2;
	arr2.fill(0);

	arr2.swap(arr);

	std::sort(arr2.begin(), arr2.end());

}

void rozne()
{
	std::set<int, bool(*)(int, int)> zbior([](int i, int j) { return i < j; });

	auto cmp = [](int i, int j) { return i < j; };

	std::set<int, decltype(cmp)> zbior2(cmp);

	zbior.insert(1);
	zbior.insert(4);
	zbior.insert(3);
	zbior.insert(10);
	zbior.insert(6);
	zbior.insert(15);
	zbior.insert(2);

	auto ep = zbior.equal_range(3);

	auto myeq = [](int i, int j) { std::cout << "powrownuje " << i << " i " << j << std::endl; return i == j; };

	std::unordered_map<int, std::string> sl1{ {5, "five"}, {6, "six"}, {4, "four"} };


	std::unordered_map<int, std::string, std::hash<int>, decltype(myeq)> slownik(sl1.begin(), sl1.end(), 5, std::hash<int>(), myeq);

	slownik[2] = "change";
	slownik[6] = "change";
}


}