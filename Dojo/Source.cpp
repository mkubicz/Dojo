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
#include <fstream>
#include <sstream>
#include <random>

#include "DInt.h"
#include "Szablony.h"
#include "TestClass.h"
#include "move_semantics.h"
#include "uniref_tag_dispatch.h"
#include "stl_trening.h"
#include "stl_kontenery.h"

using namespace std;



void consty()
{
	cout << "test" << endl;

	int a = 5;
	int c = 6;
	const int *b = &a;

	//cout << a << endl;
	//b = &c;
	//cout << a << endl;
	//cout << *b << endl;
	//cout << c << endl;

	std::shared_ptr<int> p1();
	//shared_ptr<int> &p2 = p1; no can do, nie ma konstruktora kopiuj¹cego

	//cout << *p1 << endl;

	DInt d1, d2;
	d1.a = 5;
	d2.a = 6;

	/* CONST WSKANIKI */
	DInt *ptr1 = &d1;
	ptr1->a = 5;
	ptr1 = &d2;
	ptr1->Metoda();
	ptr1->MetodaZmieniaj¹ca(3);

	const DInt *ptr2 = &d1; //alternatywnie DInt const *ptr2;
	//ptr2->a = 4; //no can do, mamy wskaŸnik do const obiektu, a const obiektu nie mo¿na zmieniaæ
	ptr2 = &d2;
	//ptr2->Metoda(); //no can do, mamy wskaŸnik do const obiektu, a const obiektu nie mo¿na zmieniaæ
	//ptr2->MetodaZmieniaj¹ca(3); //no can do, mamy wskaŸnik do const obiektu, a const obiektu nie mo¿na zmieniaæ

	DInt * const ptr3 = &d1;
	ptr3->a = 4;
	//ptr3 = &d2; //no can do, mamy const wskaŸnik do obiektu, a const wskaŸnika nie mo¿na zmieniaæ
	ptr3->Metoda(); 
	ptr3->MetodaZmieniaj¹ca(3);

	/* CONST REFERENCJE */
	DInt &ref1 = d1;
	ref1.a = 10;
	ref1 = d2; //to siê kompiluje, ale to nie zmieni miejsca w które "wskazuje" referencja. To skopiuje wartoœæ d2 do miejsca które referencjuje ref1, czyli do d1.
	//ref1 = &d2; no can do, typy siê nie zgadzaj¹; referencjê inicjalizuje siê podaj¹c po prostu nazwê zmiennej
	ref1.Metoda(); 
	ref1.MetodaZmieniaj¹ca(3); 

	const DInt &ref2 = d1;
	//ref2.a = 15; no can do, mamy referencjê do const obiektu, a const obiektu nie mo¿na zmieniaæ
	//ref2 = d2; //no can do, sytuacja jak przy ref1 = d2; ale ref2 jest referencj¹ do const obiektu wiêc nie da siê go zmieniæ.
	//ref2 = &d2; //no can do, typy siê nie zgadzaj¹; referencjê inicjalizuje siê podaj¹c po prostu nazwê zmiennej
	//ref2.Metoda(); //no can do, mamy referencjê do const obiektu, a const obiektu nie mo¿na zmieniaæ
	//ref2.MetodaZmieniaj¹ca(3); //no can do, mamy referencjê do const obiektu, a const obiektu nie mo¿na zmieniaæ
	ref2.StalaMetodaZwracajacaInta(); //mogê wywo³aæ tê metodê bo jest sta³a

	DInt & const ref3 = d1; //redundancja; referencje domyœlnie s¹ const; czyli ten przypadek jest identyczny z ref1
	ref3.a = 10;
	ref3 = d2; //identycznie jak w przypadku ref1 = d2;
	//ref1 = &d2; //identycznie jak w przypadku ref1 = d2;
	ref3.Metoda(); 
	ref3.MetodaZmieniaj¹ca(3); 

	//czyli referencja to z definicji praktycznie to samo co const wskaŸnik 
	//którego nie mo¿na ustawiæ na nulla i trzeba od razu zainicjowaæ. 


	/* CONSTY W PO£¥CZENIU Z WEKTOREM */
	vector<DInt> v = { DInt(1), DInt(5) };
	const vector<DInt> vc = { DInt(1), DInt(5) }; //const vector to vector którego elementów nie mo¿na modyfikowaæ (czyli s¹ one const (czyli operator[] zwróci const referencjê))

	DInt ep1 = v[0];
	DInt *ep1ptr = &v[0];
	DInt ep2 = vc[0];
	//DInt *ep2ptr = &vc[0]; //no can do; vc to const wektor, co oznacza ¿e jego elementy s¹ niemodyfikowalne!
	const DInt *ep2cptr = &vc[0]; //teraz ok

	v[0] = DInt(11);

	//tak siê nie da:
	//vector<const DInt> vcd = { DInt(1), DInt(5) };
	//const vector<const DInt> vcdc = { DInt(1), DInt(5) };
	//bo "The C++ Standard forbids containers of const elements because allocator<const T> is ill-formed."

	//tak te¿ siê nie da, wyskakuj¹ okropne b³êdy:
	//vector<DInt&> vv;
	//mogê najwy¿ej zrobiæ wektor wskaŸników.
	vector<DInt*> vv;

	//DInt d3 = vcd[0]; //kopiujemy const element wektora vcd - kopia nie musi byæ cont!
	////DInt *d3ptr = &vcd[0]; //teraz ju¿ nie kopiujemy, wiêc musi byæ const
	//const DInt *d3ptr = &vcd[0]; //teraz ju¿ nie kopiujemy, wiêc musi byæ const
	//DInt b = vcdc[0];
	////DInt *bptr = &vcdc[0]; //no can do; vc to const wektor, co oznacza ¿e jego elementy s¹ niemodyfikowalne!
	//auto bcptr = &vcdc[0]; //teraz ok

}

void sprytŸniki()
{
	shared_ptr<DInt> ptr1 = make_shared<DInt>(15);
	auto ptr2 = ptr1;

	weak_ptr<DInt> ptr3 = ptr1;

	cout << (*ptr1).a << endl;

	{
		auto ep = ptr3.lock();
		if (ep)
		{
			cout << (*ep).a << endl;
		}
	}

	ptr1.reset();

	{
		auto ep = ptr3.lock();
		if (ep)
		{
			cout << (*ep).a << endl;
		}
		else
			cout << "ptr1 ju¿ nie ma! Ale ptr2 wskazuj¹cy na ten sam zasób jeszcze jest, wiêc ta wiadomoœæ siê nie wypisze!";
	}

	ptr2.reset();

	{
		auto ep = ptr3.lock();
		if (ep)
		{
			cout << (*ep).a << endl;
		}
		else
			cout << "ptr1 ani ptr2 ju¿ nie ma, wiêc nie mo¿emy zalockowaæ ptr3.";
	}

}

void troche_lambdy()
{
	std::vector<int> nums1{ 9, 8, 7, 6, 5, 4, 3 };
	std::vector<int> nums2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> wynik;

	int a = 0;
	auto fun = [&a](int &n) { n++; a += n; };
	//auto fun = [&a](int &n) -> int { n++; a += n; }; mo¿na tak œmiesznie wpisaæ typ po strza³ce

	//std::for_each(nums1.begin(), nums1.end(), fun);
	//cout << a << endl; //wyliczona suma

	auto fun2 = [](const int &n, const int &m) { return n + m; };
	std::transform(nums1.begin(), nums1.end(), nums2.begin(),
		std::back_inserter(wynik), fun2);

	std::vector<string> strs1{ "ep", "op", "hep", "hop" };
	auto fun3 = [](const string& acc, const string& arg) { return acc + arg; };
	auto left_fold = accumulate(strs1.begin(), strs1.end(), string(), fun3);
	auto right_fold = accumulate(strs1.rbegin(), strs1.rend(), string(), fun3);

	//to teraz one-liner który zrobi left-folda na strs1 ale odwróci 3-znakowe stringi
	auto fun4 = [](const string& acc, string arg)
	{ return acc + (arg.length() == 3 ? [](string a) {reverse(a.begin(), a.end()); return a; } (arg) : arg); }; // i po co ci ta lambda w œrodku? --bo wtedy nie by³by one-liner, reverse nie zwraca wartoœci
	auto wtf = accumulate(strs1.begin(), strs1.end(), string(), fun4);

}

void random()
{
	std::random_device rd; //bierze "handle" czy coœtam do losowego urz¹dzenia
	std::mt19937 gen(rd()); //tworzy jakiœ mieszacz kogoœtam zainicjowany seedem 19937 (jakiœ Dobry Algorytm Do Generowania Liczb Losowych)

	//pewnie s¹ te¿ inne rozk³ady oprócz uniform
	std::uniform_real_distribution<> dis(-2, 2); //uwaga! ujemne liczby siê nie generuj¹!
	std::uniform_int_distribution<> dis2(0, 10);

	for (int i = 0; i < 100; i++)
	{
		cout << dis(gen) << endl;
	}

}

class JakisSingleton
{
private:
	JakisSingleton()
	{
		std::cout << "konstruktor";
	}
	ofstream _plik;

public:
	static JakisSingleton & GetInstance()
	{
		static JakisSingleton js;
		return js;
	}

	void ZapiszLog(string log)
	{
		_plik.open("logi.txt", std::ofstream::app);
		_plik << log << endl;
		_plik.close();
	}
/*
	JakisSingleton::GetInstance().ZapiszLog("pierwszy log");
	JakisSingleton::GetInstance().ZapiszLog("drugi log log");
	auto a = 4;
	return 0;*/
};



//std::ifstream file("plik.txt");
//
//std::string line;
//while (std::getline(file, line))
//{
//	if (line == "") continue;
//	else if (line.size() > 2 && line[0] == '/' && line[1] == '/') continue;
//	else
//	{
//		std::istringstream iss(line);
//		int height;
//		char delimiter;
//
//		while (!iss.eof())
//		{
//			if (!(iss >> height))
//			{
//				break; //error
//			}
//			if (iss.eof())
//				break; //end of line;
//			if (!(iss >> delimiter) && (delimiter == ',' || delimiter == ' ' || delimiter == ';'))
//			{
//				break; //error
//			}
//		}
//
//	}
//}

void SzablonyIDedukcja()
{
	int a = 1;
	const int ac = a;
	int &ar = a;
	const int& acr = a;

	fooByValue(a); //T = int; ParamType = int
	fooByValue(ac); //T = int; ParamType = int
	fooByValue(ar); //T = int; ParamType = int
	fooByValue(acr); //T = int; ParamType = int

	fooByRef(a); //T = int; ParamType = int&
	fooByRef(ac); //T = const int; ParamType = const int&
	fooByRef(ar); //T = int; ParamType = int&
	fooByRef(acr); //T = const int; ParamType = const int&

	fooByConstRef(a); //T = int; ParamType = const int&
	fooByConstRef(ac); //T = int; ParamType = const int&
	fooByConstRef(ar); //T = int; ParamType = const int&
	fooByConstRef(acr); //T = int; ParamType = const int&

	vector<int> ep = { 1,2,3,4 };

	//operator [] na kontenerach najczêœciej zwraca referencê na przechowywany typ (np. vector<int>)
	//take i take2 faktycznie zwróc¹ int&.
	//za to take3 zwróci int, bo u¿ywa szablonowej dedukcji, czyli: 
	//1. returnType przyrówna siê do typu zwracanego przez container[index], czyli do int&
	//2. referencje s¹ opuszczane (wg. Zasad), czyli returnType = int.
	take(ep, 1);
	take2(ep, 2);
	take3(ep, 3);
}


template<typename T>// template function to
void f(const T& param) {};


std::vector<DInt> createVec()
{
	auto a = std::vector<DInt>();
	a.push_back(DInt(4));
	return a;
}

void bierzeBoola(bool b)
{
	b;
}

//szablon który zsumuje ileœ rzeczy
template<typename T, typename... Ts>
T sum(T acc, Ts... args)
{
	return acc + sum(args...);
}

template<typename T>
T sum(T arg)
{
	return arg;
}

void rozne()
{
	const auto vw = createVec();
	//vw - const vector<DInt>

	auto b = &vw[0];
	//b - const DInt*


	f(&vw[0]);
	//w szablonie ParamType to const referencja na "const DInt*"
	//czyli const DInt* const&


	std::vector<bool> bvect = { true, false, true };
	auto nibyBool = bvect[1];
	bierzeBoola(nibyBool);

	int ep = 5.0; //przypisanie za pomoc¹ "=" odpala narrowing conversion
				  //int op{ 5.0 }; //error, przypisanie za pomoc¹ {} nie odpala narrowing conversion
	DInt hep(); //most vexing parse (jeœli jest dwuznacznoœæ, to coœ co jest deklaracj¹ wygrywa); deklaruje siê funkcja hep zwracaj¹ca DInt i nie bior¹ca ¿adnych argumentów
	DInt hep2; //deklaruje siê obiekt DInt
			   //hep.a = 4; error
	hep2.a = 4;
	//T = Widget const*
	//param = Widget const* const&
	//param = const Widget *&    (?) 

	auto a = sum(1.1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	auto s = sum(string("test"), string("kupa"), string("zupa"));
}

DInt* ZwrocDIntPtr()
{
	//nullptr jest lepszy, bo tak
	//nullptr mo¿e niejawnie konwertowaæ siê na wszystkie typy wskaŸnikowe
	//jak bêdziesz chcia³ mieæ typ wskaŸnikowy w szablonie, to mo¿esz wsadziæ tam nullptr i wszystko bêdzie dzia³aæ
	//a jak wsadzisz tam 0 albo NULL to typ wydedukuje siê jako int
	return nullptr;
}

typedef void(*FP)(int, const std::string&); 
											
using FP2 = int(*) (int, const std::string&); 

typedef int(intfp)(int); //to chyba nawet nie jest funkcja (musi byæ gwiazdka przed nazw¹)

using intfp2 = int(*) (int);


enum class Rzeczy: std::uint8_t { Kapsel, Kubek, Kostka };

//c++14 pozwala na szablony aliasów, wiêc mo¿emy znacznie uproœciæ syntax z c++11
//w c++11 ¿eby zrobiæ szablon aliasu trzeba by³o wsadzaæ go w strukturê
template<typename E>
using underlying_type_wut = typename std::underlying_type<E>::type;

//szablon funkcji który weŸmie jakiœ enumerator (czyli np. Kapsel) i zwróci jego wartoœæ
template<typename E>
constexpr typename std::underlying_type<E>::type wartoscEnumeratora(E enumerator)
{
	return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

template<typename E>
constexpr std::underlying_type_t<E> wartoscEnumeratora2(E enumerator)
{
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

template<typename E>
constexpr auto wartoscEnumeratora3(E enumerator)
{
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

//constexpr - w c++11 jeden statement, w c++14 wiêcej ni¿ jeden, i mo¿na nawet deklarowaæ zmienne, wiêc mo¿na to zrobiæ iteracj¹
constexpr int potenga(int base, int exp) noexcept
{
	return exp == 0 ? 1 : base * potenga(base, exp - 1);
}
int tablica[potenga(3, 5)];

//co dok³adnie robi virtual? jak dzia³a dziedziczenie konstruktorów, destruktorów?
class Bzint : public DInt
{
	int a;
};

class Widget
{
public:
	Widget() {}; //default constructor
	~Widget() {}; //destructor

	Widget(const Widget& rhs) { cout << "copyc" << endl; }; //copy constructor
	Widget& operator=(const Widget& rhs) { cout << "copyass" << endl; return *this; }; //copy assignment operator

	Widget(Widget&& rhs) {}; //move constructor
	Widget& operator=(Widget&& rhs) {}; //move assignmet operator
};


class Base
{
public:
	void Method() { cout << "base class method" << endl; };
	virtual void VMethod() { cout << "base class vmethod" << endl; };
};

class Derived : public Base
{
	void Method() { cout << "derived class method" << endl; };
	void VMethod() { cout << "derived class vmethod" << endl; };
};

void virtualexapmle()
{
	Base *pbase = new Derived();
	pbase->Method(); //base class method
	pbase->VMethod(); //derived class method
}

void wektorwskaznikowVSwskazniknawektor()
{
	vector<unique_ptr<DInt>> v1;
	unique_ptr<vector<DInt>> v2;

	v1.push_back(make_unique<DInt>(1));
	v1.push_back(make_unique<DInt>(2));
	v1.push_back(make_unique<DInt>(3));

	v2 = make_unique<vector<DInt>>();
	v2->push_back(DInt(1));
	v2->push_back(DInt(2));
	v2->push_back(DInt(3));

	//koniec
	v1.clear();
	v2->clear();

	//generalnie mo¿na i tak, i tak, ale trzymanie vektora wskaŸników jest lepsze, bo
	//mo¿esz trzymaæ wskaŸniki jakiegoœ typu bazowego, które bêd¹ wskazywaæ na ró¿ne typy pochodne

	//i w sumie to jest trochê moo point, bo nic mnie nie powstrzymuje przed zrobieniem wskaŸnika na wektor wskaŸników
	//to ju¿ kwestia dizajnu
}

void shenanigans()
{
	Widget w;

	Widget z(w); //copyc

	Widget x = z; //also copyc!

	Widget y;
	y = z; //copyass
}

int dupaaa(int) { return 1; };//hmm, mogê mieæ funkcje z nienazwanymi parametrami

class Person
{
public:
	template<
		typename T,
		typename = std::enable_if_t<
			!std::is_same<
				Person, 
				std::decay_t<T>
			>
		>
	>
	explicit Person(T&& n);
};


void getPermutations(int n, int k)
{
	string str = "";

	//fill string with numbers <= n
	for (int i = 0; i < n; i++)
	{
		str += to_string(i);  //convert numbers to string
	}

	string tempStr = "";
	string outputStr = "";

	do {
		tempStr = str.substr(0, k);
		int compareResult = tempStr.compare(0, k, outputStr, 0, k);

		if (compareResult == 0)
		{
			cout << "| same | ";
			tempStr.erase(0, k);

		}

		outputStr = tempStr;
		cout << outputStr << " ";
	} while (next_permutation(str.begin(), str.end()));
}

void zalety_make_shared()
{
	//niby ok
	std::shared_ptr<std::string> sptr = std::shared_ptr<std::string>(new std::string("test"));
	//ale mogê te¿ zrobiæ tak:
	std::string* str = new string("test");
	std::string* str2 = str;
	std::shared_ptr<std::string> sptr2 = std::shared_ptr<std::string>(str);
	delete str2;
	//i teraz sptr2 zawiera wskaŸnik na œmieci. Trochê lipa.

	//W tym przypadku nie mam mo¿liwoœci zrobienia czegoœ takiego, bo do make_shared podajê argumenty konstruktora,
	//czyli w ogóle nie u¿ywam new, wiêc nie ods³aniam go³ego wskaŸnika, wiêc nie mam nawet mo¿liwoœci go skaszaniæ.
	std::shared_ptr<std::string> sptr3 = std::make_shared<std::string>("test");
}


int main()
{
	struct Rzal {};

	Rzal rz1;
	Rzal rz2;

	Rzal* rzp1 = &rz1;
	Rzal* rzp2 = &rz1;

	rzp1 == rzp2;



	system("PAUSE");
}