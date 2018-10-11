#pragma once
#include "IDisplayElement.h"
#include "IObserver.h"

class StatisticsDisplay : public IObserver, public IDisplayElement
{
public:
	StatisticsDisplay(std::weak_ptr<ISubject> subject);
private:
	double _temp;
	double _humi;
	double _pres;
	double _tempMax;

	void Display() override;
	void Update(double temp, double humi, double pres) override;
};