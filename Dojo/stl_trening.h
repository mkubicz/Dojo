#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <cctype>
#include <exception>
#include "DInt.h"

namespace stl_trening
{

	bool compareInt(const int& n, const int& m)
	{
		return n > m;
	}

	bool compareInt2(int n, int m)
	{
		return n > m;
	}

	template <typename T>
	struct my_less : public std::less<T>
	{
		constexpr bool operator() (const T& param1, const T& param2) const
		{
			return param1 > param2;
		}
	};

	void start()
	{
		std::map<int, std::string> dict{ {2, "dwa"}, {3, "trzy"}, {4, "cztery"}, { 1, "jeden" }, {5, "pi��"} };

		std::map<int, std::string, bool(*)(int, int)> dict2( dict.begin(), dict.end(), compareInt2 );

		std::map<int, std::string> dict3(dict.begin(), dict.end(), my_less<int>()); 
		//i tak wywo�uje si� komparator ze zwyk�ego std::less, bo jego operator() nie jest zadeklarowany jako virtual

		std::vector<int> vect{ 11,2,23,4,35,15,6,7 };
		std::sort(vect.begin(), vect.end(), compareInt);

		system("PAUSE");
	}

	void start2()
	{
		std::vector<int> vect = { 11,2,23,4,2,2,5,6,10,15,7 };

		//usuwanie
		for (auto it = vect.begin(); it != vect.end(); )
			if (*it == 2) it = vect.erase(it);
			else ++it;

		//modyfikowanie
		{
			for (auto& el : vect)
				if (el % 2 == 0) el += 1;
		} //zeby breakpointy sie ustawialy lepiej


		std::vector<int> vect2 = { 1,3,7,2,3,4,4,4,8,9 };
		
		//usuwanie - remove/erase idiom
		vect2.erase(std::remove(vect2.begin(), vect2.end(), 4), vect2.end());
		//remove przesuwa elementy kt�re nie powinny zosta� usuni�te na pocz�tek, i zwraca iterator kt�ry wskazuje na pierwsze miejsce po tych dobrych elementach.
		//erase usuwa zakres od arg1 do arg2.

		//usuwamy parzyste
		vect2.erase(std::remove_if(vect2.begin(), vect2.end(), [](const int& el) {return el % 2 == 0; }), vect2.end());

		using IntVec = std::vector<int>;

		IntVec vect3 = {1,2,3,4,5,6,1,1,3,-1,-5,7};

		std::nth_element(vect3.begin(), vect3.begin() + 2, vect3.end(), std::greater<int>());

		system("PAUSE");
	}
	
	void start3()
	{
		std::vector<int> v;

		auto ins = std::back_insert_iterator<std::vector<int>>(v);

		ins = 1;
		ins = 2;

		auto ins2 = std::back_inserter(v);

		ins2 = 3;
		ins2 = 4;
		ins = 5;
	}

	void start4()
	{
		std::vector<int> vect = { 1,2,3,4,5,6 };
		std::vector<int> out;

		//2 razy to samo
		std::transform(vect.begin(), vect.end(), back_inserter(out), std::bind2nd(std::minus<int>(), 5));
		out.clear();
		std::transform(vect.begin(), vect.end(), back_inserter(out), [](int x) { return x - 5; });

		//vect = vect + vect2
		auto vect2 = vect;
		std::transform(vect.begin(), vect.end(), vect2.begin(), vect.begin(), [](int x, int y) { return x + y; });
	}

	void start5()
	{
		int x = 4;
		//auto fun = [x](int n) { x = n; }; //error; nie mo�na zmodyfikowa� x, bo jest wi�ty przez warto�� i sta� si� rvalue
		auto fun2 = [x](int n) mutable { x = n; }; //teraz mog� modyfikowa� x, ale oczywi�cie nie wida� tego na zewn�trz (czyli teraz wzi��em przez warto�� jako lvalue)
		auto fun = [&x](int n) { x = n; }; //x normalnie si� zmodyfikuje

		std::vector<std::function<int(int)>> funs;

		{
			std::vector<int> e = { 1,2,3 };
			int var = e.size();
			funs.push_back([&](int n) { var++;  return n + var; });
		}

		int n = funs[0](5); //runtime error! var ju� nie �yje, wi�c var to dangling reference
		//a przynajmniej powinien by�. Nani? Wygl�da na to �e tak czy tak przekazuje si� przez warto��
		int n2 = funs[0](5);
		//mo�e w C++14 to jest jako� poprawione? Mo�e Visual Studio sobie z tym radzi?



		{
			struct Rzecz
			{
				std::unique_ptr<std::string> moj_tajny_napisek;
				Rzecz(std::string napis)
				{
					moj_tajny_napisek = std::make_unique<std::string>(napis);
				}
			};
			auto rzecz = Rzecz("test");
			funs.push_back([&](int n) { return n + rzecz.moj_tajny_napisek->size(); });

			auto rzecz2 = Rzecz("test2");
			//funs.push_back([=](int n) { return n + rzecz.moj_tajny_napisek->size(); }); //error! 
			//kompilator krzyczy �e Rzecz nie ma konstruktora kopiuj�cego (no bo w sumie powinna mie�, jakbym jej napisa� to �apanie przez warto�� by dzia�a�o normalnie)
			//ale wychodzi na to, �e w momencie jak dodamy do klasy jakie� dynamiczne zasoby, to kompilator ju� wtedy przestaje generowa� operacje kopiowania
			//ciekawe czy to jest w standardzie
		}

		int icoteraz = funs[1](1); //i teraz do icoteraz wpisa�y si� �mieci - rzecz przesta�a istnie� po wyj�ciu z tych w�satych nawias�w,
		//wi�c odpali� si� jej domy�lny destruktor kt�ry zniszczy� tajny napisek.
	}

	void start6()
	{
		auto x = std::make_unique<int>(5);
		int y = 10, z = 16;
		auto lambda = [x = std::move(x), y2 = y, &x2 = x] () 
		{
			//x = unique_ptr<int>(5), y2 = 10, x2 = empty unique_ptr
			//x2 to wzi�ty przez referencj� pusty wska�nik, bo bierze x kt�ry chwil� wcze�niej dprzeniesion
			return y2 + *x2;
		};

		lambda();
	}

	//ignores case
	int nrOfSubWords(std::string napis, std::string subword)
	{
		int cnt = 0;
		std::transform(napis.begin(), napis.end(), napis.begin(),
			[](const unsigned char& znak) { return std::tolower(znak); });
		std::transform(subword.begin(), subword.end(), subword.begin(),
			[](const unsigned char& znak) { return std::tolower(znak); });

		std::string::size_type pos = 0;

		while (true)
		{
			pos = napis.find(subword, pos);
			if (pos == std::string::npos) break;
			
			pos++;
			cnt++;
		}

		return cnt;
	}

	void start7()
	{
		int nr = nrOfSubWords("Slowo to jest bardzoslowo dziwny slowoslowo napis", "slowo");
	}


	//zwraca palindromy w podanym stringu
	//auto pali = palindroms("abcdefghfe"); --zwraca {"ef", "fe"}
	std::vector<std::string> palindroms(const std::string& input)
	{
		std::vector<std::string> result;
		auto rinput = input;
		std::reverse(rinput.begin(), rinput.end());

		//drugi spos�b
		std::string rinput2;
		rinput2.resize(input.size());
		std::reverse_copy(input.begin(), input.end(), rinput2.begin());

		for (int i = 2; i < input.size(); i++)
			for (auto it = input.begin(); it < input.end() - (i - 1); ++it)
				for (auto rit = rinput.begin(); rit < rinput.end() - (i - 1); ++rit)
					if (std::string(it, it + i) == std::string(rit, rit + i)) //kopiowanie, tak troch� s�abo
						result.push_back(std::string(it, it + i));

		return result;
	}

	//Napisz funkcje kt�ra zwraca true je�li w podanym ci�gu wyst�puj� dwa r�ne wyrazy kt�re po po��czeniu daj� palindrom.
	//Ciag zawiera slowa oddzielone spacjami.
	//cout << palindroms2("to s� du s�owa oddzielone paapud spacjami") << endl; //true
	//cout << palindroms2("to s� s�owa oddzielone paapud spacjami") << endl; //false
	bool palindroms2(const std::string& input)
	{
		std::vector<std::string> split;

		int offset = 0;
		size_t space_pos = 0;

		while (space_pos < input.size())
		{
			space_pos = input.find(' ', offset);
			if (space_pos == std::string::npos) space_pos = input.size();

			split.push_back(std::string(input.begin() + offset, input.begin() + space_pos));

			offset = space_pos + 1;
		}

		std::string w;
		for (auto word : split)
			for (auto word2 : split)
			{
				if (word != word2)
				{
					w = word;
					w.append(word2);

					auto it = w.begin();
					auto rit = w.rbegin();

					int i = 0;
					while (i < w.size() / 2)
					{
						if (*it != *rit) break;
						it++; rit++;
						i++;
					}

					if (i >= w.size() / 2)
						return true;
				}
			}


		return false;
	}


	std::vector<char> getUniqueLetters(const std::string& sentence)
	{
		auto result = std::vector<char>(sentence.begin(), sentence.end());

		//std::sort(result.begin(), result.end());

		//std::erase(std::uniqe(sentence.begin(), sentence.end()), sentence.end());
		result.erase(std::unique(result.begin(), result.end()), result.end());

		return result;
	}

	void remove_nieparzyste(std::vector<int>& vect)
	{
		vect.erase(std::remove_if(vect.begin(), vect.end(), [](const int& l) { return l % 2 == 1; }), vect.end());
	}


	//wymy�l jak�� struktur�, w kt�rej przechowujesz foldery i pliki. 
	//Zaimplementuj wyszukiwanie po nazwie pliku/katalogu oraz funkcj�, 
	//kt�ra zwraca dla zadanego pliku pe�n� �cie�k� do niego.
	struct plik
	{
		std::string nazwa;
	};

	struct folder
	{
		std::string nazwa;
		std::vector<folder*> foldery;
		std::vector<plik> pliki;

		void AddFolder(folder* f_)
		{
			foldery.push_back(f_);
		}
	};

	//�le; powinno by� wyszukaj i wyszukajImpl na wz�r Sciezka
	plik Wyszukaj(std::string nazwa, folder* f_)
	{
		for (plik p : f_->pliki)
			if (p.nazwa == nazwa)
				return p;

		for (folder* f : f_->foldery)
			Wyszukaj(nazwa, f);

		throw std::exception("Plik not found.");
	}

	std::string toStringSciezka(std::vector<std::string>& sciezka)
	{
		std::string s = "";

		for (auto pom : sciezka)
			s += pom + "\\";

		s.erase(s.end() - 1, s.end());

		return s;
	}

	bool Sciezka_impl(plik p_, folder *f_, std::vector<std::string>& sciezka)
	{
		sciezka.push_back(f_->nazwa);

		for (plik p : f_->pliki)
			if (p_.nazwa == p.nazwa)
			{
				sciezka.push_back(p.nazwa);
				return true;
			}

		for (folder* f : f_->foldery)
			if (Sciezka_impl(p_, f, sciezka))
				return true;

		sciezka.pop_back();
		return false;
	}

	std::string Sciezka(plik p_, folder* f_)
	{
		std::vector<std::string> sciezka;

		if (Sciezka_impl(p_, f_, sciezka))
			return toStringSciezka(sciezka);
		else
			throw std::exception("File not found.");
	}


	void start8()
	{
		folder f1;
		f1.nazwa = "Folder1";
		f1.pliki = std::vector<plik>{ plik{"pliczek"}, plik{"plikunio"}, plik{"plike�ek"} };
		folder f2;
		f2.nazwa = "Folder2";
		f2.pliki = std::vector<plik>{ plik{ "f2p1" }, plik{ "f2p2" } };
		folder f3;
		f3.nazwa = "Folder3";
		f3.pliki = std::vector<plik>{ plik{ "f3p1" }, plik{ "f3p2" } };
		folder f4;
		f4.nazwa = "Folder4";
		f4.pliki = std::vector<plik>{ plik{ "f4p1" }, plik{ "f4p2" } };

//		f1.foldery = std::vector<folder&>{ f2, f3 };
//		f2.foldery = std::vector<folder&>();
//		f3.foldery = std::vector<folder&>{ f4 };
//		f4.foldery = std::vector<folder&>();
		f1.AddFolder(&f2);
		f1.AddFolder(&f3);
		f3.AddFolder(&f4);

		try
		{
			std::cout << Sciezka(plik{ "f2p3" }, &f1) << std::endl;
		}
		catch (std::exception ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}