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
	//shared_ptr<int> &p2 = p1; no can do, nie ma konstruktora kopiuj�cego

	//cout << *p1 << endl;

	DInt d1, d2;
	d1.a = 5;
	d2.a = 6;

	/* CONST WSKA�NIKI */
	DInt *ptr1 = &d1;
	ptr1->a = 5;
	ptr1 = &d2;
	ptr1->Metoda();
	ptr1->MetodaZmieniaj�ca(3);

	const DInt *ptr2 = &d1; //alternatywnie DInt const *ptr2;
	//ptr2->a = 4; //no can do, mamy wska�nik do const obiektu, a const obiektu nie mo�na zmienia�
	ptr2 = &d2;
	//ptr2->Metoda(); //no can do, mamy wska�nik do const obiektu, a const obiektu nie mo�na zmienia�
	//ptr2->MetodaZmieniaj�ca(3); //no can do, mamy wska�nik do const obiektu, a const obiektu nie mo�na zmienia�

	DInt * const ptr3 = &d1;
	ptr3->a = 4;
	//ptr3 = &d2; //no can do, mamy const wska�nik do obiektu, a const wska�nika nie mo�na zmienia�
	ptr3->Metoda(); 
	ptr3->MetodaZmieniaj�ca(3);

	/* CONST REFERENCJE */
	DInt &ref1 = d1;
	ref1.a = 10;
	ref1 = d2; //to si� kompiluje, ale to nie zmieni miejsca w kt�re "wskazuje" referencja. To skopiuje warto�� d2 do miejsca kt�re referencjuje ref1, czyli do d1.
	//ref1 = &d2; no can do, typy si� nie zgadzaj�; referencj� inicjalizuje si� podaj�c po prostu nazw� zmiennej
	ref1.Metoda(); 
	ref1.MetodaZmieniaj�ca(3); 

	const DInt &ref2 = d1;
	//ref2.a = 15; no can do, mamy referencj� do const obiektu, a const obiektu nie mo�na zmienia�
	//ref2 = d2; //no can do, sytuacja jak przy ref1 = d2; ale ref2 jest referencj� do const obiektu wi�c nie da si� go zmieni�.
	//ref2 = &d2; //no can do, typy si� nie zgadzaj�; referencj� inicjalizuje si� podaj�c po prostu nazw� zmiennej
	//ref2.Metoda(); //no can do, mamy referencj� do const obiektu, a const obiektu nie mo�na zmienia�
	//ref2.MetodaZmieniaj�ca(3); //no can do, mamy referencj� do const obiektu, a const obiektu nie mo�na zmienia�
	ref2.StalaMetodaZwracajacaInta(); //mog� wywo�a� t� metod� bo jest sta�a

	DInt & const ref3 = d1; //redundancja; referencje domy�lnie s� const; czyli ten przypadek jest identyczny z ref1
	ref3.a = 10;
	ref3 = d2; //identycznie jak w przypadku ref1 = d2;
	//ref1 = &d2; //identycznie jak w przypadku ref1 = d2;
	ref3.Metoda(); 
	ref3.MetodaZmieniaj�ca(3); 

	//czyli referencja to z definicji praktycznie to samo co const wska�nik 
	//kt�rego nie mo�na ustawi� na nulla i trzeba od razu zainicjowa�. 


	/* CONSTY W PO��CZENIU Z WEKTOREM */
	vector<DInt> v = { DInt(1), DInt(5) };
	const vector<DInt> vc = { DInt(1), DInt(5) }; //const vector to vector kt�rego element�w nie mo�na modyfikowa� (czyli s� one const (czyli operator[] zwr�ci const referencj�))

	DInt ep1 = v[0];
	DInt *ep1ptr = &v[0];
	DInt ep2 = vc[0];
	//DInt *ep2ptr = &vc[0]; //no can do; vc to const wektor, co oznacza �e jego elementy s� niemodyfikowalne!
	const DInt *ep2cptr = &vc[0]; //teraz ok

	v[0] = DInt(11);

	//tak si� nie da:
	//vector<const DInt> vcd = { DInt(1), DInt(5) };
	//const vector<const DInt> vcdc = { DInt(1), DInt(5) };
	//bo "The C++ Standard forbids containers of const elements because allocator<const T> is ill-formed."

	//tak te� si� nie da, wyskakuj� okropne b��dy:
	//vector<DInt&> vv;
	//mog� najwy�ej zrobi� wektor wska�nik�w.
	vector<DInt*> vv;

	//DInt d3 = vcd[0]; //kopiujemy const element wektora vcd - kopia nie musi by� cont!
	////DInt *d3ptr = &vcd[0]; //teraz ju� nie kopiujemy, wi�c musi by� const
	//const DInt *d3ptr = &vcd[0]; //teraz ju� nie kopiujemy, wi�c musi by� const
	//DInt b = vcdc[0];
	////DInt *bptr = &vcdc[0]; //no can do; vc to const wektor, co oznacza �e jego elementy s� niemodyfikowalne!
	//auto bcptr = &vcdc[0]; //teraz ok

}

void spryt�niki()
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
			cout << "ptr1 ju� nie ma! Ale ptr2 wskazuj�cy na ten sam zas�b jeszcze jest, wi�c ta wiadomo�� si� nie wypisze!";
	}

	ptr2.reset();

	{
		auto ep = ptr3.lock();
		if (ep)
		{
			cout << (*ep).a << endl;
		}
		else
			cout << "ptr1 ani ptr2 ju� nie ma, wi�c nie mo�emy zalockowa� ptr3.";
	}

}

void troche_lambdy()
{
	std::vector<int> nums1{ 9, 8, 7, 6, 5, 4, 3 };
	std::vector<int> nums2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> wynik;

	int a = 0;
	auto fun = [&a](int &n) { n++; a += n; };
	//auto fun = [&a](int &n) -> int { n++; a += n; }; mo�na tak �miesznie wpisa� typ po strza�ce

	//std::for_each(nums1.begin(), nums1.end(), fun);
	//cout << a << endl; //wyliczona suma

	auto fun2 = [](const int &n, const int &m) { return n + m; };
	std::transform(nums1.begin(), nums1.end(), nums2.begin(),
		std::back_inserter(wynik), fun2);

	std::vector<string> strs1{ "ep", "op", "hep", "hop" };
	auto fun3 = [](const string& acc, const string& arg) { return acc + arg; };
	auto left_fold = accumulate(strs1.begin(), strs1.end(), string(), fun3);
	auto right_fold = accumulate(strs1.rbegin(), strs1.rend(), string(), fun3);

	//to teraz one-liner kt�ry zrobi left-folda na strs1 ale odwr�ci 3-znakowe stringi
	auto fun4 = [](const string& acc, string arg)
	{ return acc + (arg.length() == 3 ? [](string a) {reverse(a.begin(), a.end()); return a; } (arg) : arg); }; // i po co ci ta lambda w �rodku? --bo wtedy nie by�by one-liner, reverse nie zwraca warto�ci
	auto wtf = accumulate(strs1.begin(), strs1.end(), string(), fun4);

}

void random()
{
	std::random_device rd; //bierze "handle" czy co�tam do losowego urz�dzenia
	std::mt19937 gen(rd()); //tworzy jaki� mieszacz kogo�tam zainicjowany seedem 19937 (jaki� Dobry Algorytm Do Generowania Liczb Losowych)

	//pewnie s� te� inne rozk�ady opr�cz uniform
	std::uniform_real_distribution<> dis(-2, 2); //uwaga! ujemne liczby si� nie generuj�!
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

	//operator [] na kontenerach najcz�ciej zwraca referenc� na przechowywany typ (np. vector<int>)
	//take i take2 faktycznie zwr�c� int&.
	//za to take3 zwr�ci int, bo u�ywa szablonowej dedukcji, czyli: 
	//1. returnType przyr�wna si� do typu zwracanego przez container[index], czyli do int&
	//2. referencje s� opuszczane (wg. Zasad), czyli returnType = int.
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

//szablon kt�ry zsumuje ile� rzeczy
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

	int ep = 5.0; //przypisanie za pomoc� "=" odpala narrowing conversion
				  //int op{ 5.0 }; //error, przypisanie za pomoc� {} nie odpala narrowing conversion
	DInt hep(); //most vexing parse (je�li jest dwuznaczno��, to co� co jest deklaracj� wygrywa); deklaruje si� funkcja hep zwracaj�ca DInt i nie bior�ca �adnych argument�w
	DInt hep2; //deklaruje si� obiekt DInt
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
	//nullptr mo�e niejawnie konwertowa� si� na wszystkie typy wska�nikowe
	//jak b�dziesz chcia� mie� typ wska�nikowy w szablonie, to mo�esz wsadzi� tam nullptr i wszystko b�dzie dzia�a�
	//a jak wsadzisz tam 0 albo NULL to typ wydedukuje si� jako int
	return nullptr;
}

typedef void(*FP)(int, const std::string&); 
											
using FP2 = int(*) (int, const std::string&); 

typedef int(intfp)(int); //to chyba nawet nie jest funkcja (musi by� gwiazdka przed nazw�)

using intfp2 = int(*) (int);


enum class Rzeczy: std::uint8_t { Kapsel, Kubek, Kostka };

//c++14 pozwala na szablony alias�w, wi�c mo�emy znacznie upro�ci� syntax z c++11
//w c++11 �eby zrobi� szablon aliasu trzeba by�o wsadza� go w struktur�
template<typename E>
using underlying_type_wut = typename std::underlying_type<E>::type;

//szablon funkcji kt�ry we�mie jaki� enumerator (czyli np. Kapsel) i zwr�ci jego warto��
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

//constexpr - w c++11 jeden statement, w c++14 wi�cej ni� jeden, i mo�na nawet deklarowa� zmienne, wi�c mo�na to zrobi� iteracj�
constexpr int potenga(int base, int exp) noexcept
{
	return exp == 0 ? 1 : base * potenga(base, exp - 1);
}
int tablica[potenga(3, 5)];

//co dok�adnie robi virtual? jak dzia�a dziedziczenie konstruktor�w, destruktor�w?
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

	//generalnie mo�na i tak, i tak, ale trzymanie vektora wska�nik�w jest lepsze, bo
	//mo�esz trzyma� wska�niki jakiego� typu bazowego, kt�re b�d� wskazywa� na r�ne typy pochodne

	//i w sumie to jest troch� moo point, bo nic mnie nie powstrzymuje przed zrobieniem wska�nika na wektor wska�nik�w
	//to ju� kwestia dizajnu
}

void shenanigans()
{
	Widget w;

	Widget z(w); //copyc

	Widget x = z; //also copyc!

	Widget y;
	y = z; //copyass
}

int dupaaa(int) { return 1; };//hmm, mog� mie� funkcje z nienazwanymi parametrami

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
	//ale mog� te� zrobi� tak:
	std::string* str = new string("test");
	std::string* str2 = str;
	std::shared_ptr<std::string> sptr2 = std::shared_ptr<std::string>(str);
	delete str2;
	//i teraz sptr2 zawiera wska�nik na �mieci. Troch� lipa.

	//W tym przypadku nie mam mo�liwo�ci zrobienia czego� takiego, bo do make_shared podaj� argumenty konstruktora,
	//czyli w og�le nie u�ywam new, wi�c nie ods�aniam go�ego wska�nika, wi�c nie mam nawet mo�liwo�ci go skaszani�.
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