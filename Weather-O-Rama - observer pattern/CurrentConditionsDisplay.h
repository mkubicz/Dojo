#pragma once
#include "IDisplayElement.h"
#include "IObserver.h"

class CurrentConditionsDisplay : public IObserver, public IDisplayElement
{
public:
	CurrentConditionsDisplay(std::weak_ptr<ISubject> subject);
private:
	double _temp;
	double _humi;
	double _pres;

	void Display() override;
	void Update(double temp, double humi, double pres) override;
};