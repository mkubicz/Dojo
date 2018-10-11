#pragma once

class DInt
{
public:
	DInt() : DInt(0) {}
	DInt(int a)
	{
		this->a = a;
	}
	int a;
	mutable int m; //ten int jest mutable, czyli nawet sta³e metody mog¹ go zmieniaæ

	void Metoda()
	{
		//ta metoda nic nie robi.
	}
	void MetodaZmieniaj¹ca(int arg)
	{
		a = arg;
	}

	const int MetodaZwracajacaStalegoInta()
	{
		return 1;
	}
	int StalaMetodaZwracajacaInta() const
	{
		return 1;
	}
	void StalaMetodaZmieniajaca(int arg) const
	{
		//a = arg; //no can do; metoda jest sta³a, czyli nie mo¿e zmieniaæ memberów
		m = arg;
	}

};