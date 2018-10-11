#pragma once

//template<typename T>
//void foo(ParamType param)
//{ }
//ArgType arg;
//foo(arg);

//szablon z argumentem kopiowanym by-value:
//1. Argument jest obierany z referencji i constów (bo przekazujemy go by-value, wiêc kopiujemy - ten skopiowany obiekt nie jest referencj¹ ani nie musi byæ const)
//2. ParamType jest pattern-matchowany z ArgType ¿eby wyznaczyæ T
//tutaj ParamType to T
template<typename T>
T fooByValue(T param)
{
	return param;
}

//szablon z argumentem kopiowanym by-reference i by-const-reference:
//1. Argument jest obierany z referencji (bo i tak typ do którego siê zmatchuje jest referencj¹)
//2. ParamType jest pattern-matchowany z ArgType ¿eby wyznaczyæ T
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

//Szablon z parametrem który jest wskaŸnikiem (T* param) zachowuje siê tak jak w przypadku 
//argumentu by-reference.

//szablony z argumentem który jest uniwersaln¹ referencj¹ (&&) (czy tam referencj¹ na rvalue)
//prerobiê w itemie 24 podobno. 


//mo¿na te¿ dedukowaæ typ zwracany przez auto albo decltype(auto)

//konstrukcja "auto Name(args) -> Typ" trailing return type, w miejsce "auto" wstawi siê "Typ"
//to po to ¿eby mo¿na by³o uzale¿niæ typ zwracany od typu argumentów
template<typename T, typename I>
auto take(T &container, I index)
-> decltype(container[index])
{
	return container[index];
}

//decltype(auto) - wydedukuj typ zwracany ale za pomoc¹ regu³ decltype, a nie szablonowych
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