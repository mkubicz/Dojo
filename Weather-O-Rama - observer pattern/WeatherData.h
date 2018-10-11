#pragma once
#include "ISubject.h"
#include <list>
#include <memory>


class WeatherData : public ISubject
{
public:
	void RegisterObserver(std::weak_ptr<IObserver> ob) override;
	void RemoveObserver(std::weak_ptr<IObserver> ob) override;

	//methods to get the newest measurements
	double GetTemperature();
	double GetHumidity();
	double GetPressure();

	//method to simulate sensors in the weather station
	void SetMeasurements(double temp, double humi, double pres);

private:
	std::list<std::weak_ptr<IObserver>> _observers;
	double _temp;
	double _humi;
	double _pres;

	void MeasurementsChanged();
	void NotifyObservers() override;
};