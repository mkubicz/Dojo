#include "CurrentConditionsDisplay.h"
#include "ISubject.h"
#include <iostream>

CurrentConditionsDisplay::CurrentConditionsDisplay(std::weak_ptr<ISubject> weatherData)
	: IObserver(weatherData)
{
	//TODO:
	//nie da siê, bo ten konstruktor zosta³ wywo³any podczas tworzenia shared pointera
	//gdybym chcia³ siê rejestrowaæ od razu, to musia³bym tworzyæ observery przez jakieœ factory method
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
	std::cout << "Temperatura: " << _temp << " stopni Celsjusza; Wilgotnoœæ: " << _humi << "%." << std::endl;
}


