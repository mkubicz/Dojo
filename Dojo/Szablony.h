#pragma once

//template<typename T>
//void foo(ParamType param)
//{ }
//ArgType arg;
//foo(arg);

//szablon z argumentem kopiowanym by-value:
//1. Argument jest obierany z referencji i const�w (bo przekazujemy go by-value, wi�c kopiujemy - ten skopiowany obiekt nie jest referencj� ani nie musi by� const)
//2. ParamType jest pattern-matchowany z ArgType �eby wyznaczy� T
//tutaj ParamType to T
template<typename T>
T fooByValue(T param)
{
	return param;
}

//szablon z argumentem kopiowanym by-reference i by-const-reference:
//1. Argument jest obierany z referencji (bo i tak typ do kt�rego si� zmatchuje jest referencj�)
//2. ParamType jest pattern-matchowany z ArgType �eby wyznaczy� T
//tutaj ParamType to T&
template<typename T>
T fooByRef(T& param)
{
	return param;
}

//tutaj ParamType to const T&
template<typename T>
T fooByConstRef(const T &param)
{
	return param;
}

//Szablon z parametrem kt�ry jest wska�nikiem (T* param) zachowuje si� tak jak w przypadku 
//argumentu by-reference.

//szablony z argumentem kt�ry jest uniwersaln� referencj� (&&) (czy tam referencj� na rvalue)
//prerobi� w itemie 24 podobno. 


//mo�na te� dedukowa� typ zwracany przez auto albo decltype(auto)

//konstrukcja "auto Name(args) -> Typ" trailing return type, w miejsce "auto" wstawi si� "Typ"
//to po to �eby mo�na by�o uzale�ni� typ zwracany od typu argument�w
template<typename T, typename I>
auto take(T &container, I index)
-> decltype(container[index])
{
	return container[index];
}

//decltype(auto) - wydedukuj typ zwracany ale za pomoc� regu� decltype, a nie szablonowych
template<typename T, typename I>
decltype(auto) take2(T &container, I index)
{
	return container[index];
}

template<typename T, typename I>
auto take3(T &container, I index)
{
	return container[index];
}