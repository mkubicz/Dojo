#include "ForecastDisplay.h"
#include <iostream>

ForecastDisplay::ForecastDisplay(std::weak_ptr<ISubject> subject)
	: IObserver(subject)
{
}

void ForecastDisplay::Update(double temp, double humi, double pres)
{
	_temp = temp;
	_humi = humi;
	_pres = pres;
	Display();
}

void ForecastDisplay::Display()
{
	std::cout << "Prognoza na dzi�: ";

	if (_pres > 1000) std::cout << "B�dzie �adnie.";
	else  std::cout << "B�dzie brzydko.";

	std::cout << std::endl;
}
