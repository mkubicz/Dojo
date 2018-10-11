#pragma once
#include "IDisplayElement.h"
#include "IObserver.h"

class ForecastDisplay : public IObserver, public IDisplayElement
{
public:
	ForecastDisplay(std::weak_ptr<ISubject> subject);

private:
	double _temp;
	double _humi;
	double _pres;

	void Update(double temp, double humi, double pres) override;
	void Display() override;
};