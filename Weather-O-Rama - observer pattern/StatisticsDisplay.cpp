#include "StatisticsDisplay.h"
#include <iostream>

StatisticsDisplay::StatisticsDisplay(std::weak_ptr<ISubject> subject)
	: IObserver(subject)
{
}

void StatisticsDisplay::Update(double temp, double humi, double pres)
{
	_temp = temp;
	_humi = humi;
	_pres = pres;

	if (_temp > _tempMax)
		_tempMax = _temp;

	Display();
}



void StatisticsDisplay::Display()
{
	std::cout << "Najwieksza odnotowana temperatura: " << _tempMax << " stopni Celsjusza." << std::endl;
}


