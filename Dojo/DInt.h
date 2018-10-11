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
	mutable int m; //ten int jest mutable, czyli nawet sta�e metody mog� go zmienia�

	void Metoda()
	{
		//ta metoda nic nie robi.
	}
	void MetodaZmieniaj�ca(int arg)
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
		//a = arg; //no can do; metoda jest sta�a, czyli nie mo�e zmienia� member�w
		m = arg;
	}

};