#include "CurrentConditionsDisplay.h"
#include "ISubject.h"
#include <iostream>

CurrentConditionsDisplay::CurrentConditionsDisplay(std::weak_ptr<ISubject> weatherData)
	: IObserver(weatherData)
{
	//TODO:
	//nie da si�, bo ten konstruktor zosta� wywo�any podczas tworzenia shared pointera
	//gdybym chcia� si� rejestrowa� od razu, to musia�bym tworzy� observery przez jakie� factory method
	//na razie to zostawiam
	//weatherData->RegisterObserver(std::shared_ptr<IObserver>(this));
}

void CurrentConditionsDisplay::Update(double temp, double humi, double pres)
{
	_temp = temp;
	_humi = humi;
	_pres = pres;
	Display();
}

void CurrentConditionsDisplay::Display()
{
	std::cout << "Temperatura: " << _temp << " stopni Celsjusza; Wilgotno��: " << _humi << "%." << std::endl;
}


